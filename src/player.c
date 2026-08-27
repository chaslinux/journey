#include <stddef.h>

#include "player.h"

static void journey_player_try_move(
    JourneyPlayer *player,
    const JourneyMap *map,
    int dx,
    int dy
)
{
    if (player == NULL || map == NULL)
    {
        return;
    }

    const int new_x = player->x + dx;
    const int new_y = player->y + dy;

    if (journey_map_is_walkable(map, new_x, new_y))
    {
        player->x = new_x;
        player->y = new_y;
    }
}

void journey_player_init(
    JourneyPlayer *player,
    const JourneyMap *map
)
{
    if (player == NULL || map == NULL)
    {
        return;
    }

    /*
     * Start on the stone path.
     */
    player->x = 16;
    player->y = 12;
}

void journey_player_move_up(
    JourneyPlayer *player,
    const JourneyMap *map
)
{
    journey_player_try_move(player, map, 0, -1);
}

void journey_player_move_down(
    JourneyPlayer *player,
    const JourneyMap *map
)
{
    journey_player_try_move(player, map, 0, 1);
}

void journey_player_move_left(
    JourneyPlayer *player,
    const JourneyMap *map
)
{
    journey_player_try_move(player, map, -1, 0);
}

void journey_player_move_right(
    JourneyPlayer *player,
    const JourneyMap *map
)
{
    journey_player_try_move(player, map, 1, 0);
}

