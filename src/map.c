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

    for (int y = 0; y < JOURNEY_MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < JOURNEY_MAP_WIDTH; ++x)
        {
            JourneyTile *tile = &map->tiles[x][y];

            /*
             * Start with grass everywhere.
             */
            tile->type = JOURNEY_TILE_GRASS;
            tile->walkable = true;

            /*
             * Forest border.
             */
            if (x == 0 ||
                y == 0 ||
                x == JOURNEY_MAP_WIDTH - 1 ||
                y == JOURNEY_MAP_HEIGHT - 1)
            {
                tile->type = JOURNEY_TILE_FOREST;
                tile->walkable = false;
            }

            /*
             * Water feature.
             */
            if (x >= 10 &&
                x <= 14 &&
                y >= 5 &&
                y <= 8)
            {
                tile->type = JOURNEY_TILE_WATER;
                tile->walkable = false;
            }

            /*
             * Stone path.
             */
            if (y == 12 && x >= 3 && x <= 28)
            {
                tile->type = JOURNEY_TILE_STONE;
                tile->walkable = true;
            }
        }
    }
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

