#ifndef JOURNEY_PLAYER_H
#define JOURNEY_PLAYER_H

#include <stdbool.h>

#include "dungeon.h"
#include "map.h"

typedef struct
{
    int x;
    int y;
} JourneyPlayer;

void journey_player_init(
    JourneyPlayer *player,
    const JourneyMap *map
);

void journey_player_move_up(
    JourneyPlayer *player,
    const JourneyMap *map
);

void journey_player_move_down(
    JourneyPlayer *player,
    const JourneyMap *map
);

void journey_player_move_left(
    JourneyPlayer *player,
    const JourneyMap *map
);

void journey_player_move_right(
    JourneyPlayer *player,
    const JourneyMap *map
);

void journey_player_move_dungeon_up(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
);

void journey_player_move_dungeon_down(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
);

void journey_player_move_dungeon_left(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
);

void journey_player_move_dungeon_right(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
);

#endif

