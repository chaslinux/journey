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

                case JOURNEY_TILE_DUNGEON:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        80,
                        45,
                        45,
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

void journey_renderer_draw_dungeon(
    JourneyRenderer *renderer,
    const JourneyDungeon *dungeon,
    const JourneyCamera *camera
)
{
    if (renderer == NULL ||
        renderer->renderer == NULL ||
        dungeon == NULL ||
        camera == NULL)
    {
        return;
    }

    const float tile_width = 10.0f;
    const float tile_height = 10.0f;

    for (int y = 0; y < dungeon->height; ++y)
    {
        for (int x = 0; x < dungeon->width; ++x)
        {
            const JourneyDungeonTile *tile =
                journey_dungeon_get_tile(
                    dungeon,
                    x,
                    y
                );

            if (tile == NULL)
            {
                continue;
            }

            switch (tile->type)
            {
                case JOURNEY_DUNGEON_FLOOR:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        90,
                        75,
                        65,
                        255
                    );
                    break;

                case JOURNEY_DUNGEON_WALL:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        45,
                        35,
                        35,
                        255
                    );
                    break;

                case JOURNEY_DUNGEON_EXIT:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        120,
                        80,
                        45,
                        255
                    );
                    break;

                case JOURNEY_DUNGEON_CHEST:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        160,
                        70,
                        190,
                        255
                    );
                    break;

                case JOURNEY_DUNGEON_CHEST_OPEN:
                    SDL_SetRenderDrawColor(
                        renderer->renderer,
                        90,
                        75,
                        65,
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

    const float tile_width = 10.0f;
    const float tile_height = 10.0f;

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

void journey_renderer_draw_monster(
    JourneyRenderer *renderer,
    const JourneyMonster *monster,
    const JourneyCamera *camera
)
{
    if (renderer == NULL ||
        renderer->renderer == NULL ||
        monster == NULL ||
        monster->definition == NULL ||
        camera == NULL)
    {
        return;
    }

    const float tile_width = 10.0f;
    const float tile_height = 10.0f;

    const float monster_width = 8.0f;
    const float monster_height = 8.0f;

    const float tile_x =
        (float)monster->x * tile_width -
        camera->x;

    const float tile_y =
        (float)monster->y * tile_height -
        camera->y;

    const float monster_x =
        tile_x +
        (tile_width - monster_width) / 2.0f;

    const float monster_y =
        tile_y +
        (tile_height - monster_height) / 2.0f;

    /*
     * Dark outline.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        15,
        15,
        18,
        255
    );

    SDL_FRect outline = {
        monster_x - 1.0f,
        monster_y - 1.0f,
        monster_width + 2.0f,
        monster_height + 2.0f
    };

    SDL_RenderFillRect(
        renderer->renderer,
        &outline
    );

    /*
     * Bone-colored body.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        190,
        185,
        160,
        255
    );

    SDL_FRect body = {
        monster_x,
        monster_y,
        monster_width,
        monster_height
    };

    SDL_RenderFillRect(
        renderer->renderer,
        &body
    );

    /*
     * Red eyes.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        180,
        35,
        35,
        255
    );

    SDL_FRect left_eye = {
        monster_x + 2.0f,
        monster_y + 2.0f,
        1.0f,
        1.0f
    };

    SDL_FRect right_eye = {
        monster_x + 5.0f,
        monster_y + 2.0f,
        1.0f,
        1.0f
    };

    SDL_RenderFillRect(
        renderer->renderer,
        &left_eye
    );

    SDL_RenderFillRect(
        renderer->renderer,
        &right_eye
    );
}

void journey_renderer_draw_character_creation(
    JourneyRenderer *renderer,
    JourneyClass selected_class
)
{
    if (renderer == NULL ||
        renderer->renderer == NULL)
    {
        return;
    }

    /*
     * Background.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        12,
        12,
        18,
        255
    );

    SDL_RenderClear(renderer->renderer);

    /*
     * Title.
     *
     * JOURNEY is 7 characters at the debug font's
     * approximately 8-pixel character width.
     * 320 - 56 = 264 / 2 = 132.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        230,
        220,
        180,
        255
    );

    SDL_RenderDebugText(
        renderer->renderer,
        132.0f,
        18.0f,
        "JOURNEY"
    );

    SDL_RenderDebugText(
        renderer->renderer,
        94.0f,
        34.0f,
        "CHOOSE YOUR CLASS"
    );

    /*
     * Class list.
     */
    const float class_x = 70.0f;
    const float class_y = 60.0f;
    const float class_spacing = 18.0f;

    for (int i = 0; i < 3; ++i)
    {
        JourneyClass class =
            (JourneyClass)i;

        const bool selected =
            class == selected_class;

        if (selected)
        {
            SDL_SetRenderDrawColor(
                renderer->renderer,
                70,
                70,
                100,
                255
            );

            SDL_FRect highlight = {
                class_x - 8.0f,
                class_y +
                    ((float)i * class_spacing) - 2.0f,
                80.0f,
                12.0f
            };

            SDL_RenderFillRect(
                renderer->renderer,
                &highlight
            );

            SDL_SetRenderDrawColor(
                renderer->renderer,
                255,
                230,
                120,
                255
            );

            SDL_RenderDebugText(
                renderer->renderer,
                class_x,
                class_y +
                    ((float)i * class_spacing),
                ">"
            );
        }

        if (selected)
        {
            SDL_SetRenderDrawColor(
                renderer->renderer,
                255,
                230,
                120,
                255
            );
        }
        else
        {
            SDL_SetRenderDrawColor(
                renderer->renderer,
                180,
                180,
                190,
                255
            );
        }

        SDL_RenderDebugText(
            renderer->renderer,
            class_x + 10.0f,
            class_y +
                ((float)i * class_spacing),
            journey_character_get_class_name(class)
        );
    }

    /*
     * Preview the selected class's starting stats.
     */
    JourneyCharacter preview = {0};

    journey_character_init(
        &preview,
        selected_class
    );

    /*
     * Stats panel.
     *
     * Values are deliberately kept in one column.
     * COPPER is longer than the other labels, so
     * the value column is farther right.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        180,
        180,
        190,
        255
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        55.0f,
        "STATS"
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        69.0f,
        "STR:"
    );

    SDL_RenderDebugTextFormat(
        renderer->renderer,
        242.0f,
        69.0f,
        "%d",
        preview.strength
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        81.0f,
        "AGI:"
    );

    SDL_RenderDebugTextFormat(
        renderer->renderer,
        242.0f,
        81.0f,
        "%d",
        preview.agility
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        93.0f,
        "INT:"
    );

    SDL_RenderDebugTextFormat(
        renderer->renderer,
        242.0f,
        93.0f,
        "%d",
        preview.intelligence
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        105.0f,
        "HP:"
    );

    SDL_RenderDebugTextFormat(
        renderer->renderer,
        242.0f,
        105.0f,
        "%d/%d",
        preview.health,
        preview.max_health
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        117.0f,
        "LVL:"
    );

    SDL_RenderDebugTextFormat(
        renderer->renderer,
        242.0f,
        117.0f,
        "%d",
        preview.level
    );

    SDL_RenderDebugText(
        renderer->renderer,
        178.0f,
        129.0f,
        "COPPER:"
    );

    SDL_RenderDebugTextFormat(
        renderer->renderer,
        242.0f,
        129.0f,
        "%d",
        preview.copper
    );

    /*
     * Controls.
     *
     * There is now a deliberate gap between
     * the COPPER row and these instructions.
     */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        150,
        150,
        160,
        255
    );

    SDL_RenderDebugText(
        renderer->renderer,
        62.0f,
        148.0f,
        "W/S or UP/DOWN: SELECT"
    );

    SDL_SetRenderDrawColor(
        renderer->renderer,
        255,
        230,
        120,
        255
    );

    SDL_RenderDebugText(
        renderer->renderer,
        91.0f,
        162.0f,
        "E: BEGIN JOURNEY"
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

