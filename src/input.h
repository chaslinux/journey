#ifndef JOURNEY_INPUT_H
#define JOURNEY_INPUT_H

#include <stdbool.h>

#include <SDL3/SDL.h>

typedef struct
{
    bool quit;

    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;

    bool interact;
} JourneyInput;

void journey_input_init(JourneyInput *input);

void journey_input_process_event(
    JourneyInput *input,
    const SDL_Event *event
);

#endif

