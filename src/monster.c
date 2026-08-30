#include <stddef.h>

#include "monster.h"

const JourneyMonsterDefinition
    JOURNEY_MONSTER_SKELETAL_RAT =
{
    .name = "Skeletal Rat",

    .max_health = 8,
    .damage = 2,
    .defence = 1,
    .movement = 5,

    .experience = 4,

    .copper_min = 1,
    .copper_max = 6,

    .attack_type = JOURNEY_ATTACK_MELEE,
    .undead_type = JOURNEY_UNDEAD_ANIMAL_DEAD
};

void journey_monster_init(
    JourneyMonster *monster,
    const JourneyMonsterDefinition *definition,
    int x,
    int y
)
{
    if (monster == NULL ||
        definition == NULL)
    {
        return;
    }

    monster->definition = definition;

    monster->health = definition->max_health;

    monster->x = x;
    monster->y = y;
}
