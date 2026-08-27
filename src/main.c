#include <stdbool.h>
#include <SDL3/SDL.h>

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

    bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                journey_renderer_resize(&renderer);
            }
        }

        journey_renderer_begin(&renderer);

        journey_renderer_draw_test_pattern(&renderer);

        journey_renderer_present(&renderer);
    }

    journey_renderer_shutdown(&renderer);
    SDL_Quit();

    return 0;
}

