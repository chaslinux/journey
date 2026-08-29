#ifndef JOURNEY_RENDERER_H
#define JOURNEY_RENDERER_H

#include <stdbool.h>
#include <SDL3/SDL.h>

#include "map.h"
#include "dungeon.h"
#include "player.h"
#include "camera.h"
#include "character.h"

#define JOURNEY_LOGICAL_WIDTH  320
#define JOURNEY_LOGICAL_HEIGHT 180

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *render_target;

    int window_width;
    int window_height;

    SDL_FRect destination;
} JourneyRenderer;

bool journey_renderer_init(JourneyRenderer *renderer);
void journey_renderer_shutdown(JourneyRenderer *renderer);

void journey_renderer_resize(JourneyRenderer *renderer);

void journey_renderer_begin(JourneyRenderer *renderer);
void journey_renderer_present(JourneyRenderer *renderer);

void journey_renderer_draw_map(
    JourneyRenderer *renderer,
    const JourneyMap *map,
    const JourneyCamera *camera
);

void journey_renderer_draw_dungeon(
    JourneyRenderer *renderer,
    const JourneyDungeon *dungeon,
    const JourneyCamera *camera
);

void journey_renderer_draw_player(
    JourneyRenderer *renderer,
    const JourneyPlayer *player,
    const JourneyCamera *camera
);

void journey_renderer_draw_character_creation(
    JourneyRenderer *renderer,
    JourneyClass selected_class
);

#endif

