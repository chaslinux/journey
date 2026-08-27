#include "renderer.h"

static void journey_renderer_update_destination(
    JourneyRenderer *renderer
)
{
    const int scale_x =
        renderer->window_width / JOURNEY_LOGICAL_WIDTH;

    const int scale_y =
        renderer->window_height / JOURNEY_LOGICAL_HEIGHT;

    int scale = scale_x < scale_y ? scale_x : scale_y;

    if (scale < 1)
    {
        scale = 1;
    }

    const float width =
        (float)(JOURNEY_LOGICAL_WIDTH * scale);

    const float height =
        (float)(JOURNEY_LOGICAL_HEIGHT * scale);

    renderer->destination.w = width;
    renderer->destination.h = height;

    renderer->destination.x =
        ((float)renderer->window_width - width) / 2.0f;

    renderer->destination.y =
        ((float)renderer->window_height - height) / 2.0f;
}

bool journey_renderer_init(JourneyRenderer *renderer)
{
    if (renderer == NULL)
    {
        return false;
    }

    renderer->window = SDL_CreateWindow(
        "Journey - Land of the Undead",
        1280,
        720,
        SDL_WINDOW_RESIZABLE
    );

    if (renderer->window == NULL)
    {
        SDL_Log(
            "Failed to create window: %s",
            SDL_GetError()
        );

        return false;
    }

    renderer->renderer = SDL_CreateRenderer(
        renderer->window,
        NULL
    );

    if (renderer->renderer == NULL)
    {
        SDL_Log(
            "Failed to create renderer: %s",
            SDL_GetError()
        );

        journey_renderer_shutdown(renderer);
        return false;
    }

    renderer->render_target = SDL_CreateTexture(
        renderer->renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        JOURNEY_LOGICAL_WIDTH,
        JOURNEY_LOGICAL_HEIGHT
    );

    if (renderer->render_target == NULL)
    {
        SDL_Log(
            "Failed to create render target: %s",
            SDL_GetError()
        );

        journey_renderer_shutdown(renderer);
        return false;
    }

    SDL_SetTextureScaleMode(
        renderer->render_target,
        SDL_SCALEMODE_NEAREST
    );

    journey_renderer_resize(renderer);

    return true;
}

void journey_renderer_resize(JourneyRenderer *renderer)
{
    if (renderer == NULL ||
        renderer->renderer == NULL)
    {
        return;
    }

    int width = 0;
    int height = 0;

    if (!SDL_GetCurrentRenderOutputSize(
            renderer->renderer,
            &width,
            &height))
    {
        SDL_Log(
            "Failed to get render output size: %s",
            SDL_GetError()
        );

        return;
    }

    renderer->window_width = width;
    renderer->window_height = height;

    journey_renderer_update_destination(renderer);
}

void journey_renderer_shutdown(JourneyRenderer *renderer)
{
    if (renderer == NULL)
    {
        return;
    }

    if (renderer->render_target != NULL)
    {
        SDL_DestroyTexture(renderer->render_target);
        renderer->render_target = NULL;
    }

    if (renderer->renderer != NULL)
    {
        SDL_DestroyRenderer(renderer->renderer);
        renderer->renderer = NULL;
    }

    if (renderer->window != NULL)
    {
        SDL_DestroyWindow(renderer->window);
        renderer->window = NULL;
    }
}

void journey_renderer_draw_map(
    JourneyRenderer *renderer,
    const JourneyMap *map,
    const JourneyCamera *camera
)
{
    if (renderer == NULL ||
        renderer->renderer == NULL ||
        map == NULL ||
        camera == NULL)
    {
        return;
    }

    /*
     * The entire map is 64 x 36 tiles.
     *
     * Our logical screen is 320 x 180 pixels,
     * so each tile is exactly 5 x 5 logical pixels.
     */

    /*
     * Map tiles are 10 x 10 logical pixels.
     *
     * The 64 x 36 map is therefore 640 x 360
     * logical pixels, while the viewport is 320 x 180.
     */
    const float tile_width = 10.0f;
    const float tile_height = 10.0f;

    for (int y = 0; y < map->height; ++y)
    {
        for (int x = 0; x < map->width; ++x)
        {
            const JourneyTile *tile =
                journey_map_get_tile(map, x, y);

            if (tile == NULL)
            {
                continue;
            }

            switch (tile->type)
            {
                case JOURNEY_TILE_GRASS:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        70,
                        140,
                        70,
                        255
                    );
                    break;

                case JOURNEY_TILE_WATER:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        50,
                        100,
                        180,
                        255
                    );
                    break;

                case JOURNEY_TILE_FOREST:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        35,
                        80,
                        45,
                        255
                    );
                    break;

                case JOURNEY_TILE_STONE:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        130,
                        130,
                        130,
                        255
                    );
                    break;

                case JOURNEY_TILE_GRAVE:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        100,
                        70,
                        100,
                        255
                    );
                    break;

                default:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        255,
                        0,
                        255,
                        255
                    );
                    break;
            }

            /*
             * Convert map coordinates to logical screen
             * coordinates, then subtract the camera position.
             */
            const float world_x =
                (float)x * tile_width;

            const float world_y =
                (float)y * tile_height;

            SDL_FRect destination = {
                world_x - camera->x,
                world_y - camera->y,
                tile_width,
                tile_height
            };

            SDL_RenderFillRect(
                renderer->renderer,
                &destination
            );
        }
    }
}

void journey_renderer_draw_player(
    JourneyRenderer *renderer,
    const JourneyPlayer *player,
    const JourneyCamera *camera
)
{
    if (renderer == NULL ||
        renderer->renderer == NULL ||
        player == NULL ||
        camera == NULL)
    {
        return;
    }

    /*
     * Keep player coordinates consistent with the map.
     */
    const float tile_width = 10.0f;
    const float tile_height = 10.0f;

    /*
     * Original player proportions.
     */
    const float player_width = 6.0f;
    const float player_height = 10.0f;

    const float tile_x =
        (float)player->x * tile_width -
        camera->x;

    const float tile_y =
        (float)player->y * tile_height -
        camera->y;

    const float player_x =
        tile_x +
        (tile_width - player_width) / 2.0f;

    const float player_y =
        tile_y +
        (tile_height - player_height) / 2.0f;

    /*
     * Dark outline.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        20,
        20,
        25,
        255
    );

    SDL_FRect outline = {
        player_x - 1.0f,
        player_y - 1.0f,
        player_width + 2.0f,
        player_height + 2.0f
    };

    SDL_RenderFillRect(
        renderer->renderer,
        &outline
    );

    /*
     * Pale character body.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        220,
        210,
        180,
        255
    );

    SDL_FRect body = {
        player_x,
        player_y,
        player_width,
        player_height
    };

    SDL_RenderFillRect(
        renderer->renderer,
        &body
    );

    /*
     * Dark head / face detail.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        40,
        35,
        35,
        255
    );

    SDL_FRect face = {
        player_x + 1.0f,
        player_y + 1.0f,
        player_width - 2.0f,
        3.0f
    };

    SDL_RenderFillRect(
        renderer->renderer,
        &face
    );
}

void journey_renderer_begin(JourneyRenderer *renderer)
{
    if (renderer == NULL ||
        renderer->renderer == NULL ||
        renderer->render_target == NULL)
    {
        return;
    }

    SDL_SetRenderTarget(
        renderer->renderer,
        renderer->render_target
    );

    SDL_SetRenderDrawColor(
        renderer->renderer,
        20,
        20,
        24,
        255
    );

    SDL_RenderClear(renderer->renderer);
}

void journey_renderer_present(JourneyRenderer *renderer)
{
    if (renderer == NULL ||
        renderer->renderer == NULL ||
        renderer->render_target == NULL)
    {
        return;
    }

    SDL_SetRenderTarget(
        renderer->renderer,
        NULL
    );

    SDL_SetRenderDrawColor(
        renderer->renderer,
        0,
        0,
        0,
        255
    );

    SDL_RenderClear(renderer->renderer);

    SDL_RenderTexture(
        renderer->renderer,
        renderer->render_target,
        NULL,
        &renderer->destination
    );

    SDL_RenderPresent(renderer->renderer);
}

