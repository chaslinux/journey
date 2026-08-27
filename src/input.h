#ifndef JOURNEY_INPUT_H
#define JOURNEY_INPUT_H

#include <stdbool.h>
#include <SDL3/SDL.h>

typedef enum
{
    JOURNEY_ACTION_NONE = 0,

    JOURNEY_ACTION_MOVE_UP,
    JOURNEY_ACTION_MOVE_DOWN,
    JOURNEY_ACTION_MOVE_LEFT,
    JOURNEY_ACTION_MOVE_RIGHT,

    JOURNEY_ACTION_CONFIRM,
    JOURNEY_ACTION_CANCEL,
    JOURNEY_ACTION_MENU
} JourneyAction;

typedef struct
{
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;

    bool confirm;
    bool cancel;
    bool menu;

    bool quit;
} JourneyInput;

void journey_input_init(JourneyInput *input);

void journey_input_process_event(
    JourneyInput *input,
    const SDL_Event *event
);

#endif

