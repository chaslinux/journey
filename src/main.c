#include <SDL3/SDL.h>

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Log("Journey started.");
    SDL_Log("SDL version: %d.%d.%d",
            SDL_MAJOR_VERSION,
            SDL_MINOR_VERSION,
            SDL_MICRO_VERSION);

    SDL_Quit();

    return 0;
}

