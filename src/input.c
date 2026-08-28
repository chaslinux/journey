#include <stddef.h>

#include "input.h"

void journey_input_init(JourneyInput *input)
{
    if (input == NULL)
    {
        return;
    }

    input->quit = false;
    input->move_up = false;
    input->move_down = false;
    input->move_left = false;
    input->move_right = false;
    input->interact = false;
}

void journey_input_process_event(
    JourneyInput *input,
    const SDL_Event *event
)
{
    if (input == NULL || event == NULL)
    {
        return;
    }

    if (event->type == SDL_EVENT_QUIT)
    {
        input->quit = true;
        return;
    }

    if (event->type != SDL_EVENT_KEY_DOWN)
    {
        return;
    }

    if (event->key.repeat)
    {
        return;
    }

    switch (event->key.scancode)
    {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            input->move_up = true;
            break;

        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            input->move_down = true;
            break;

        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            input->move_left = true;
            break;

        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            input->move_right = true;
            break;

        case SDL_SCANCODE_E:
            input->interact = true;
            break;

        case SDL_SCANCODE_ESCAPE:
            input->quit = true;
            break;

        default:
            break;
    }
}

