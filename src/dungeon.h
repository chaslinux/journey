#ifndef JOURNEY_DUNGEON_H
#define JOURNEY_DUNGEON_H

#include <stdbool.h>

#define JOURNEY_DUNGEON_WIDTH  32
#define JOURNEY_DUNGEON_HEIGHT 24

typedef enum
{
    JOURNEY_DUNGEON_FLOOR = 0,
    JOURNEY_DUNGEON_WALL,
    JOURNEY_DUNGEON_EXIT,
    JOURNEY_DUNGEON_CHEST,
    JOURNEY_DUNGEON_CHEST_OPEN
} JourneyDungeonTileType;

typedef struct
{
    JourneyDungeonTileType type;
    bool walkable;
} JourneyDungeonTile;

typedef struct
{
    int width;
    int height;
    JourneyDungeonTile tiles[
        JOURNEY_DUNGEON_WIDTH
    ][
        JOURNEY_DUNGEON_HEIGHT
    ];
} JourneyDungeon;

void journey_dungeon_init(
    JourneyDungeon *dungeon
);

const JourneyDungeonTile *journey_dungeon_get_tile(
    const JourneyDungeon *dungeon,
    int x,
    int y
);

bool journey_dungeon_is_walkable(
    const JourneyDungeon *dungeon,
    int x,
    int y
);

bool journey_dungeon_has_interaction(
    const JourneyDungeon *dungeon,
    int x,
    int y
);

const JourneyDungeonTile *journey_dungeon_get_interaction(
    const JourneyDungeon *dungeon,
    int x,
    int y
);

#endif

