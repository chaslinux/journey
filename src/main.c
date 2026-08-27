#include <stdbool.h>
#include <SDL3/SDL.h>

#include "input.h"
#include "map.h"
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

    JourneyInput input = {0};
    journey_input_init(&input);

    JourneyMap map = {0};
    journey_map_init(&map);

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

        if (input.move_up)
        {
            SDL_Log("Action: MOVE UP");
        }

        if (input.move_down)
        {
            SDL_Log("Action: MOVE DOWN");
        }

        if (input.move_left)
        {
            SDL_Log("Action: MOVE LEFT");
        }

        if (input.move_right)
        {
            SDL_Log("Action: MOVE RIGHT");
        }

        if (input.confirm)
        {
            SDL_Log("Action: CONFIRM");
        }

        if (input.cancel)
        {
            SDL_Log("Action: CANCEL");
        }

        if (input.menu)
        {
            SDL_Log("Action: MENU");
        }

        journey_input_init(&input);

        journey_renderer_begin(&renderer);

        journey_renderer_draw_map(&renderer, &map);

        journey_renderer_present(&renderer);
    }

    journey_renderer_shutdown(&renderer);
    SDL_Quit();

    return 0;
}

