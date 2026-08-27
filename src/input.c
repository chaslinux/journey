#include "input.h"

void journey_input_init(JourneyInput *input)
{
    if (input == NULL)
    {
        return;
    }

    input->move_up = false;
    input->move_down = false;
    input->move_left = false;
    input->move_right = false;

    input->confirm = false;
    input->cancel = false;
    input->menu = false;

    input->quit = false;
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

    switch (event->key.key)
    {
        case SDLK_UP:
        case SDLK_W:
            input->move_up = true;
            break;

        case SDLK_DOWN:
        case SDLK_S:
            input->move_down = true;
            break;

        case SDLK_LEFT:
        case SDLK_A:
            input->move_left = true;
            break;

        case SDLK_RIGHT:
        case SDLK_D:
            input->move_right = true;
            break;

        case SDLK_RETURN:
        case SDLK_SPACE:
            input->confirm = true;
            break;

        case SDLK_ESCAPE:
            input->cancel = true;
            break;

        case SDLK_TAB:
            input->menu = true;
            break;

        default:
            break;
    }
}

