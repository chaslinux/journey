#ifndef JOURNEY_MONSTER_H
#define JOURNEY_MONSTER_H

typedef enum
{
    JOURNEY_ATTACK_MELEE = 0,
    JOURNEY_ATTACK_RANGED,
    JOURNEY_ATTACK_MAGIC
} JourneyAttackType;

typedef enum
{
    JOURNEY_UNDEAD_ANIMAL_DEAD = 0,
    JOURNEY_UNDEAD_HUMANOID,
    JOURNEY_UNDEAD_SPIRIT,
    JOURNEY_UNDEAD_CONSTRUCT
} JourneyUndeadType;

typedef struct
{
    const char *name;

    int max_health;
    int damage;
    int defence;
    int movement;

    int experience;

    int copper_min;
    int copper_max;

    JourneyAttackType attack_type;
    JourneyUndeadType undead_type;
} JourneyMonsterDefinition;

typedef struct
{
    const JourneyMonsterDefinition *definition;

    int x;
    int y;

    int health;
} JourneyMonster;

extern const JourneyMonsterDefinition
    JOURNEY_MONSTER_SKELETAL_RAT;

void journey_monster_init(
    JourneyMonster *monster,
    const JourneyMonsterDefinition *definition,
    int x,
    int y
);

void journey_monster_take_damage(
    JourneyMonster *monster,
    int damage
);

#endif
