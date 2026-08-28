#include <stddef.h>

#include "dungeon.h"

void journey_dungeon_init(
    JourneyDungeon *dungeon
)
{
    if (dungeon == NULL)
    {
        return;
    }

    dungeon->width = JOURNEY_DUNGEON_WIDTH;
    dungeon->height = JOURNEY_DUNGEON_HEIGHT;

    /*
     * Start with floor throughout the dungeon.
     */
    for (int y = 0; y < JOURNEY_DUNGEON_HEIGHT; ++y)
    {
        for (int x = 0; x < JOURNEY_DUNGEON_WIDTH; ++x)
        {
            dungeon->tiles[x][y].type =
                JOURNEY_DUNGEON_FLOOR;

            dungeon->tiles[x][y].walkable = true;
        }
    }

    /*
     * Solid outer walls.
     */
    for (int x = 0; x < JOURNEY_DUNGEON_WIDTH; ++x)
    {
        dungeon->tiles[x][0].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][0].walkable = false;

        dungeon->tiles[x][JOURNEY_DUNGEON_HEIGHT - 1].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][JOURNEY_DUNGEON_HEIGHT - 1].walkable =
            false;
    }

    for (int y = 0; y < JOURNEY_DUNGEON_HEIGHT; ++y)
    {
        dungeon->tiles[0][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[0][y].walkable = false;

        dungeon->tiles[JOURNEY_DUNGEON_WIDTH - 1][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[JOURNEY_DUNGEON_WIDTH - 1][y].walkable =
            false;
    }

    /*
     * Central wall.
     *
     * This divides the dungeon into western and
     * eastern sections, with a passage near the middle.
     */
    for (int y = 2; y <= 20; ++y)
    {
        if (y == 11 || y == 12)
        {
            continue;
        }

        dungeon->tiles[16][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[16][y].walkable = false;
    }

    /*
     * Western room.
     *
     * Add a smaller enclosed room in the northwest.
     */
    for (int x = 3; x <= 11; ++x)
    {
        dungeon->tiles[x][5].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][5].walkable = false;

        dungeon->tiles[x][10].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][10].walkable = false;
    }

    for (int y = 5; y <= 10; ++y)
    {
        dungeon->tiles[3][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[3][y].walkable = false;

        dungeon->tiles[11][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[11][y].walkable = false;
    }

    /*
     * Doorway into the western room.
     */
    dungeon->tiles[7][10].type =
        JOURNEY_DUNGEON_FLOOR;

    dungeon->tiles[7][10].walkable = true;

    /*
     * Eastern room.
     *
     * Add a larger chamber in the northeast.
     */
    for (int x = 20; x <= 28; ++x)
    {
        dungeon->tiles[x][4].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][4].walkable = false;

        dungeon->tiles[x][10].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][10].walkable = false;
    }

    for (int y = 4; y <= 10; ++y)
    {
        dungeon->tiles[20][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[20][y].walkable = false;

        dungeon->tiles[28][y].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[28][y].walkable = false;
    }

    /*
     * Doorway into the eastern room.
     */
    dungeon->tiles[20][7].type =
        JOURNEY_DUNGEON_FLOOR;

    dungeon->tiles[20][7].walkable = true;

    /*
     * Southern interior wall.
     *
     * This creates a smaller southern chamber.
     */
    for (int x = 4; x <= 27; ++x)
    {
        if (x == 8 || x == 24)
        {
            continue;
        }

        dungeon->tiles[x][17].type =
            JOURNEY_DUNGEON_WALL;

        dungeon->tiles[x][17].walkable = false;
    }

    /*
     * Entrance at the southern edge.
     */
    dungeon->tiles[16][22].type =
        JOURNEY_DUNGEON_EXIT;

    dungeon->tiles[16][22].walkable = true;
}

const JourneyDungeonTile *journey_dungeon_get_tile(
    const JourneyDungeon *dungeon,
    int x,
    int y
)
{
    if (dungeon == NULL)
    {
        return NULL;
    }

    if (x < 0 ||
        x >= dungeon->width ||
        y < 0 ||
        y >= dungeon->height)
    {
        return NULL;
    }

    return &dungeon->tiles[x][y];
}

bool journey_dungeon_is_walkable(
    const JourneyDungeon *dungeon,
    int x,
    int y
)
{
    const JourneyDungeonTile *tile =
        journey_dungeon_get_tile(
            dungeon,
            x,
            y
        );

    if (tile == NULL)
    {
        return false;
    }

    return tile->walkable;
}

bool journey_dungeon_has_interaction(
    const JourneyDungeon *dungeon,
    int x,
    int y
)
{
    const JourneyDungeonTile *tile =
        journey_dungeon_get_tile(
            dungeon,
            x,
            y
        );

    if (tile == NULL)
    {
        return false;
    }

    return tile->type == JOURNEY_DUNGEON_EXIT;
}

