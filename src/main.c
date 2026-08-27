#include <stdbool.h>

#include <SDL3/SDL.h>

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

    JourneyInput input = {0};
    journey_input_init(&input);

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

        /*
         * Remember where the player was before movement.
         */
        const int old_x = player.x;
        const int old_y = player.y;

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

        /*
         * Trigger an interaction only when the player
         * actually enters an interactive tile.
         */
        if (player.x != old_x || player.y != old_y)
        {
            if (journey_map_has_interaction(
                    &map,
                    player.x,
                    player.y))
            {
                SDL_Log("You discovered an ancient grave.");
            }
        }

        journey_input_init(&input);

        journey_renderer_begin(&renderer);

        journey_renderer_draw_map(
            &renderer,
            &map
        );

        journey_renderer_draw_player(
            &renderer,
            &player
        );

        journey_renderer_present(&renderer);
    }

    journey_renderer_shutdown(&renderer);
    SDL_Quit();

    return 0;
}

