#include <stdbool.h>

#include <SDL3/SDL.h>

#include "camera.h"
#include "dungeon.h"
#include "game.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "renderer.h"

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log(
            "SDL initialization failed: %s",
            SDL_GetError()
        );
        return 1;
    }

    SDL_Log("Journey started.");
    SDL_Log(
        "SDL version: %d.%d.%d",
        SDL_MAJOR_VERSION,
        SDL_MINOR_VERSION,
        SDL_MICRO_VERSION
    );

    JourneyRenderer renderer = {0};

    if (!journey_renderer_init(&renderer))
    {
        SDL_Quit();
        return 1;
    }

    JourneyMap map = {0};
    journey_map_init(&map);

    JourneyPlayer player = {0};
    journey_player_init(&player, &map);

    JourneyDungeon dungeon = {0};
    journey_dungeon_init(&dungeon);

    JourneyCamera camera = {0};
    journey_camera_init(&camera, &player);

    JourneyInput input = {0};
    journey_input_init(&input);

    JourneyLocation location =
        JOURNEY_LOCATION_OVERWORLD;

    bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            journey_input_process_event(&input, &event);

            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                journey_renderer_resize(&renderer);
            }
        }

        if (input.quit)
        {
            running = false;
        }

        const int old_x = player.x;
        const int old_y = player.y;

        /*
         * Movement depends on the current location.
         */
        if (location == JOURNEY_LOCATION_OVERWORLD)
        {
            if (input.move_up)
            {
                journey_player_move_up(
                    &player,
                    &map
                );
            }

            if (input.move_down)
            {
                journey_player_move_down(
                    &player,
                    &map
                );
            }

            if (input.move_left)
            {
                journey_player_move_left(
                    &player,
                    &map
                );
            }

            if (input.move_right)
            {
                journey_player_move_right(
                    &player,
                    &map
                );
            }
        }
        else if (location == JOURNEY_LOCATION_DUNGEON)
        {
            if (input.move_up)
            {
                journey_player_move_dungeon_up(
                    &player,
                    &dungeon
                );
            }

            if (input.move_down)
            {
                journey_player_move_dungeon_down(
                    &player,
                    &dungeon
                );
            }

            if (input.move_left)
            {
                journey_player_move_dungeon_left(
                    &player,
                    &dungeon
                );
            }

            if (input.move_right)
            {
                journey_player_move_dungeon_right(
                    &player,
                    &dungeon
                );
            }
        }

        /*
         * Enter the dungeon when E is pressed
         * while standing on the dungeon entrance.
         */
        if (location == JOURNEY_LOCATION_OVERWORLD &&
            input.interact)
        {
            const JourneyTile *tile =
                journey_map_get_tile(
                    &map,
                    player.x,
                    player.y
                );

            if (tile != NULL &&
                tile->type == JOURNEY_TILE_DUNGEON)
            {
                location = JOURNEY_LOCATION_DUNGEON;

                player.x = 16;
                player.y = 21;

                SDL_Log(
                    "You enter the ancient dungeon."
                );
            }
        }

        /*
         * Interact with the dungeon exit or an
         * adjacent chest when E is pressed.
         */
        if (location == JOURNEY_LOCATION_DUNGEON &&
            input.interact)
        {
            const JourneyDungeonTile *tile =
                journey_dungeon_get_interaction(
                    &dungeon,
                    player.x,
                    player.y
                );

            if (tile != NULL)
            {
                if (tile->type == JOURNEY_DUNGEON_EXIT)
                {
                    location = JOURNEY_LOCATION_OVERWORLD;

                    player.x = 102;
                    player.y = 49;

                    SDL_Log(
                        "You exit the ancient dungeon."
                    );
                }
                else if (tile->type == JOURNEY_DUNGEON_CHEST)
                {
                    SDL_Log(
                        "You discover an ancient chest."
                    );
                }
            }
        }

        /*
         * Trigger the grave interaction when the player
         * enters a grave tile.
         */
        if (location == JOURNEY_LOCATION_OVERWORLD &&
            (player.x != old_x || player.y != old_y))
        {
            const JourneyTile *tile =
                journey_map_get_tile(
                    &map,
                    player.x,
                    player.y
                );

            if (tile != NULL &&
                tile->type == JOURNEY_TILE_GRAVE)
            {
                SDL_Log(
                    "You discovered an ancient grave."
                );
            }
        }

        if (location == JOURNEY_LOCATION_OVERWORLD)
        {
            journey_camera_follow(
                &camera,
                &player,
                map.width,
                map.height
            );
        }
        else if (location == JOURNEY_LOCATION_DUNGEON)
        {
            journey_camera_follow(
                &camera,
                &player,
                dungeon.width,
                dungeon.height
            );
        }

        journey_input_init(&input);
        journey_renderer_begin(&renderer);

        if (location == JOURNEY_LOCATION_OVERWORLD)
        {
            journey_renderer_draw_map(
                &renderer,
                &map,
                &camera
            );
        }
        else if (location == JOURNEY_LOCATION_DUNGEON)
        {
            journey_renderer_draw_dungeon(
                &renderer,
                &dungeon,
                &camera
            );
        }

        journey_renderer_draw_player(
            &renderer,
            &player,
            &camera
        );

        journey_renderer_present(&renderer);
    }

    journey_renderer_shutdown(&renderer);
    SDL_Quit();

    return 0;
}

