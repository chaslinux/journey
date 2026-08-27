#include "renderer.h"

static void journey_renderer_update_destination(JourneyRenderer *renderer)
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
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer->renderer = SDL_CreateRenderer(
        renderer->window,
        NULL
    );

    if (renderer->renderer == NULL)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
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
        SDL_Log("Failed to create render target: %s", SDL_GetError());
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
    if (renderer == NULL || renderer->renderer == NULL)
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

void journey_renderer_draw_test_pattern(JourneyRenderer *renderer)
{
    SDL_SetRenderDrawColor(
        renderer->renderer,
        40,
        40,
        48,
        255
    );
    SDL_RenderClear(renderer->renderer);

    /* Outer logical-resolution border. */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        180,
        180,
        180,
        255
    );

    SDL_FRect border = {
        0.0f,
        0.0f,
        (float)JOURNEY_LOGICAL_WIDTH,
        (float)JOURNEY_LOGICAL_HEIGHT
    };

    SDL_RenderRect(renderer->renderer, &border);

    /* Four corner markers. */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        220,
        60,
        60,
        255
    );

    SDL_FRect top_left = { 5.0f, 5.0f, 20.0f, 20.0f };
    SDL_RenderFillRect(renderer->renderer, &top_left);

    SDL_SetRenderDrawColor(
        renderer->renderer,
        60,
        220,
        60,
        255
    );

    SDL_FRect top_right = {
        295.0f,
        5.0f,
        20.0f,
        20.0f
    };

    SDL_RenderFillRect(renderer->renderer, &top_right);

    SDL_SetRenderDrawColor(
        renderer->renderer,
        60,
        120,
        220,
        255
    );

    SDL_FRect bottom_left = {
        5.0f,
        155.0f,
        20.0f,
        20.0f
    };

    SDL_RenderFillRect(renderer->renderer, &bottom_left);

    SDL_SetRenderDrawColor(
        renderer->renderer,
        220,
        200,
        60,
        255
    );

    SDL_FRect bottom_right = {
        295.0f,
        155.0f,
        20.0f,
        20.0f
    };

    SDL_RenderFillRect(renderer->renderer, &bottom_right);

    /* Center marker. */
    SDL_SetRenderDrawColor(
        renderer->renderer,
        220,
        80,
        220,
        255
    );

    SDL_FRect center = {
        155.0f,
        85.0f,
        10.0f,
        10.0f
    };

    SDL_RenderFillRect(renderer->renderer, &center);
}

void journey_renderer_begin(JourneyRenderer *renderer)
{
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
    SDL_SetRenderTarget(renderer->renderer, NULL);

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

