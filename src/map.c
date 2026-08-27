#include <stddef.h>

#include "map.h"

void journey_map_init(JourneyMap *map)
{
    if (map == NULL)
    {
        return;
    }

    map->width = JOURNEY_MAP_WIDTH;
    map->height = JOURNEY_MAP_HEIGHT;

    /*
     * Start with grass everywhere.
     */
    for (int y = 0; y < JOURNEY_MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < JOURNEY_MAP_WIDTH; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_GRASS;
            map->tiles[x][y].walkable = true;
        }
    }

    /*
     * Forest border.
     */
    for (int x = 0; x < JOURNEY_MAP_WIDTH; ++x)
    {
        map->tiles[x][0].type = JOURNEY_TILE_FOREST;
        map->tiles[x][0].walkable = false;

        map->tiles[x][JOURNEY_MAP_HEIGHT - 1].type =
            JOURNEY_TILE_FOREST;
        map->tiles[x][JOURNEY_MAP_HEIGHT - 1].walkable = false;
    }

    for (int y = 0; y < JOURNEY_MAP_HEIGHT; ++y)
    {
        map->tiles[0][y].type = JOURNEY_TILE_FOREST;
        map->tiles[0][y].walkable = false;

        map->tiles[JOURNEY_MAP_WIDTH - 1][y].type =
            JOURNEY_TILE_FOREST;
        map->tiles[JOURNEY_MAP_WIDTH - 1][y].walkable = false;
    }

    /*
     * Northern forest.
     */
    for (int y = 3; y <= 17; ++y)
    {
        for (int x = 8; x <= 43; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_FOREST;
            map->tiles[x][y].walkable = false;
        }
    }

    /*
     * Eastern forest.
     */
    for (int y = 8; y <= 31; ++y)
    {
        for (int x = 91; x <= 116; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_FOREST;
            map->tiles[x][y].walkable = false;
        }
    }

    /*
     * Western forest.
     */
    for (int y = 39; y <= 65; ++y)
    {
        for (int x = 5; x <= 28; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_FOREST;
            map->tiles[x][y].walkable = false;
        }
    }

    /*
     * Southern forest.
     */
    for (int y = 54; y <= 68; ++y)
    {
        for (int x = 72; x <= 111; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_FOREST;
            map->tiles[x][y].walkable = false;
        }
    }

    /*
     * Northern water feature.
     */
    for (int y = 7; y <= 13; ++y)
    {
        for (int x = 53; x <= 63; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_WATER;
            map->tiles[x][y].walkable = false;
        }
    }

    /*
     * Southern water feature.
     */
    for (int y = 42; y <= 50; ++y)
    {
        for (int x = 49; x <= 58; ++x)
        {
            map->tiles[x][y].type = JOURNEY_TILE_WATER;
            map->tiles[x][y].walkable = false;
        }
    }

    /*
     * Main east-west road.
     */
    for (int x = 4; x <= 105; ++x)
    {
        map->tiles[x][34].type = JOURNEY_TILE_STONE;
        map->tiles[x][34].walkable = true;

        map->tiles[x][35].type = JOURNEY_TILE_STONE;
        map->tiles[x][35].walkable = true;
    }

    /*
     * Main north-south road.
     */
    for (int y = 16; y <= 58; ++y)
    {
        map->tiles[68][y].type = JOURNEY_TILE_STONE;
        map->tiles[68][y].walkable = true;

        map->tiles[69][y].type = JOURNEY_TILE_STONE;
        map->tiles[69][y].walkable = true;
    }

    /*
     * Western road to the graveyard.
     */
    for (int x = 18; x <= 40; ++x)
    {
        map->tiles[x][45].type = JOURNEY_TILE_STONE;
        map->tiles[x][45].walkable = true;
    }

    /*
     * Eastern road toward the dungeon.
     */
    for (int y = 35; y <= 48; ++y)
    {
        map->tiles[102][y].type = JOURNEY_TILE_STONE;
        map->tiles[102][y].walkable = true;
    }

    /*
     * Graveyard clearing.
     *
     * The graveyard sits beside the western road.
     * All graves remain accessible.
     */
    map->tiles[29][45].type = JOURNEY_TILE_GRAVE;
    map->tiles[29][45].walkable = true;

    map->tiles[32][44].type = JOURNEY_TILE_GRAVE;
    map->tiles[32][44].walkable = true;

    map->tiles[35][45].type = JOURNEY_TILE_GRAVE;
    map->tiles[35][45].walkable = true;

    map->tiles[32][47].type = JOURNEY_TILE_GRAVE;
    map->tiles[32][47].walkable = true;

    map->tiles[35][48].type = JOURNEY_TILE_GRAVE;
    map->tiles[35][48].walkable = true;
}

const JourneyTile *journey_map_get_tile(
    const JourneyMap *map,
    int x,
    int y
)
{
    if (map == NULL)
    {
        return NULL;
    }

    if (x < 0 ||
        x >= map->width ||
        y < 0 ||
        y >= map->height)
    {
        return NULL;
    }

    return &map->tiles[x][y];
}

bool journey_map_is_walkable(
    const JourneyMap *map,
    int x,
    int y
)
{
    const JourneyTile *tile =
        journey_map_get_tile(map, x, y);

    if (tile == NULL)
    {
        return false;
    }

    return tile->walkable;
}

bool journey_map_has_interaction(
    const JourneyMap *map,
    int x,
    int y
)
{
    const JourneyTile *tile =
        journey_map_get_tile(map, x, y);

    if (tile == NULL)
    {
        return false;
    }

    return tile->type == JOURNEY_TILE_GRAVE;
}

