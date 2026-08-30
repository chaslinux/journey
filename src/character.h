#ifndef JOURNEY_CHARACTER_H
#define JOURNEY_CHARACTER_H

#include <stdbool.h>

#include "item.h"

#define JOURNEY_CHARACTER_NAME_LENGTH 32
#define JOURNEY_STARTING_COPPER 100
#define JOURNEY_INVENTORY_SIZE 8

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

    const JourneyItemDefinition *
        inventory[JOURNEY_INVENTORY_SIZE];

    int inventory_count;
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

bool journey_character_add_item(
    JourneyCharacter *character,
    const JourneyItemDefinition *item
);

int journey_character_get_item_count(
    const JourneyCharacter *character
);

const JourneyItemDefinition *
journey_character_get_item(
    const JourneyCharacter *character,
    int index
);

const char *journey_character_get_class_name(
    JourneyClass class
);

#endif

