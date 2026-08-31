#include <stddef.h>

#include "player.h"

static bool journey_player_tile_occupied_by_monster(
    int x,
    int y,
    const JourneyMonster *monster
)
{
    if (monster == NULL ||
        monster->definition == NULL ||
        monster->health <= 0)
    {
        return false;
    }

    return monster->x == x &&
           monster->y == y;
}

static bool journey_player_try_move(
    JourneyPlayer *player,
    const JourneyMap *map,
	const JourneyMonster monsters[JOURNEY_MAX_MONSTERS],
    int dx,
    int dy
)
{
    if (player == NULL || map == NULL)
    {
        return false;
    }

    const int new_x = player->x + dx;
    const int new_y = player->y + dy;

    if (!journey_map_is_walkable(
            map,
            new_x,
            new_y))
    {
        return false;
    }

	for (int i = 0; i < JOURNEY_MAX_MONSTERS; ++i)
	{
		if (journey_player_tile_occupied_by_monster(
		        new_x,
		        new_y,
		        &monsters[i]))
		{
		    return false;
		}
	}

    player->x = new_x;
    player->y = new_y;

    return true;
}

static void journey_player_try_move_dungeon(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon,
    int dx,
    int dy
)
{
    if (player == NULL || dungeon == NULL)
    {
        return;
    }

    const int new_x = player->x + dx;
    const int new_y = player->y + dy;

    if (journey_dungeon_is_walkable(
            dungeon,
            new_x,
            new_y))
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
    player->x = 60;
    player->y = 34;
}

bool journey_player_move_up(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster monsters[JOURNEY_MAX_MONSTERS]
)
{
    return journey_player_try_move(
        player,
        map,
        monsters,
        0,
        -1
    );
}

bool journey_player_move_down(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster monsters[JOURNEY_MAX_MONSTERS]
)
{
    return journey_player_try_move(
        player,
        map,
        monsters,
        0,
        1
    );
}

bool journey_player_move_left(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster monsters[JOURNEY_MAX_MONSTERS]
)
{
    return journey_player_try_move(
        player,
        map,
        monsters,
        -1,
        0
    );
}

bool journey_player_move_right(
    JourneyPlayer *player,
    const JourneyMap *map,
    const JourneyMonster monsters[JOURNEY_MAX_MONSTERS]
)
{
    return journey_player_try_move(
        player,
        map,
        monsters,
        1,
        0
    );
}

void journey_player_move_dungeon_up(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
)
{
    journey_player_try_move_dungeon(
        player,
        dungeon,
        0,
        -1
    );
}

void journey_player_move_dungeon_down(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
)
{
    journey_player_try_move_dungeon(
        player,
        dungeon,
        0,
        1
    );
}

void journey_player_move_dungeon_left(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
)
{
    journey_player_try_move_dungeon(
        player,
        dungeon,
        -1,
        0
    );
}

void journey_player_move_dungeon_right(
    JourneyPlayer *player,
    const JourneyDungeon *dungeon
)
{
    journey_player_try_move_dungeon(
        player,
        dungeon,
        1,
        0
    );
}

void journey_player_attack_monster(
    JourneyPlayer *player,
    JourneyMonster *monster
)
{
    if (player == NULL ||
        monster == NULL ||
        monster->definition == NULL ||
        monster->health <= 0)
    {
        return;
    }

    const int dx = player->x - monster->x;
    const int dy = player->y - monster->y;

    if (dx < -1 || dx > 1 ||
        dy < -1 || dy > 1)
    {
        return;
    }

    const int damage = 4;

    journey_monster_take_damage(
        monster,
        damage
    );
}

bool journey_player_is_adjacent_to_monster(
    const JourneyPlayer *player,
    const JourneyMonster *monster
)
{
    if (player == NULL ||
        monster == NULL ||
        monster->health <= 0)
    {
        return false;
    }

    const int dx = player->x - monster->x;
    const int dy = player->y - monster->y;

    return dx >= -1 && dx <= 1 &&
           dy >= -1 && dy <= 1 &&
           (dx != 0 || dy != 0);
}

