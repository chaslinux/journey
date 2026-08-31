#ifndef JOURNEY_PLAYER_H
#define JOURNEY_PLAYER_H

#include <stdbool.h>

#include "dungeon.h"
#include "map.h"
#include "monster.h"

typedef struct
{
    int x;
    int y;
} JourneyPlayer;

void journey_player_init(
    JourneyPlayer *player,
    const JourneyMap *map
);

bool journey_player_move_up(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster *monster
);

bool journey_player_move_down(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster *monster
);

bool journey_player_move_left(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster *monster
);

bool journey_player_move_right(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster *monster
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

void journey_player_attack_monster(
    JourneyPlayer *player,
    JourneyMonster *monster
);

bool journey_player_is_adjacent_to_monster(
    const JourneyPlayer *player,
    const JourneyMonster *monster
);

#endif

