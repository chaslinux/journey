#ifndef JOURNEY_CHARACTER_H
#define JOURNEY_CHARACTER_H

#include <stdbool.h>

#define JOURNEY_CHARACTER_NAME_LENGTH 32
#define JOURNEY_STARTING_COPPER 100

typedef enum
{
    JOURNEY_CLASS_WARRIOR = 0,
    JOURNEY_CLASS_RANGER,
    JOURNEY_CLASS_MAGE
} JourneyClass;

typedef struct
{
    char name[JOURNEY_CHARACTER_NAME_LENGTH];

    JourneyClass class;

    int strength;
    int agility;
    int intelligence;

    int health;
    int max_health;

    int level;
    int experience;

    int copper;
} JourneyCharacter;

void journey_character_init(
    JourneyCharacter *character,
    JourneyClass class
);

void journey_character_add_experience(
    JourneyCharacter *character,
    int experience
);

void journey_character_add_copper(
    JourneyCharacter *character,
    int copper
);

const char *journey_character_get_class_name(
    JourneyClass class
);

#endif

