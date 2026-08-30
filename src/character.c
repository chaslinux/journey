#include <stddef.h>

#include "character.h"

void journey_character_init(
    JourneyCharacter *character,
    JourneyClass class
)
{
    if (character == NULL)
    {
        return;
    }

    character->name[0] = '\0';

    switch (class)
    {
        case JOURNEY_CLASS_WARRIOR:
            character->class = JOURNEY_CLASS_WARRIOR;
            character->strength = 14;
            character->agility = 8;
            character->intelligence = 6;
            character->max_health = 120;
            break;

        case JOURNEY_CLASS_RANGER:
            character->class = JOURNEY_CLASS_RANGER;
            character->strength = 10;
            character->agility = 14;
            character->intelligence = 8;
            character->max_health = 100;
            break;

        case JOURNEY_CLASS_MAGE:
            character->class = JOURNEY_CLASS_MAGE;
            character->strength = 6;
            character->agility = 8;
            character->intelligence = 14;
            character->max_health = 80;
            break;

        default:
            character->class = JOURNEY_CLASS_WARRIOR;
            character->strength = 14;
            character->agility = 8;
            character->intelligence = 6;
            character->max_health = 120;
            break;
    }

    character->health = character->max_health;

    character->level = 1;
    character->experience = 0;

    character->copper = JOURNEY_STARTING_COPPER;

    for (int i = 0; i < JOURNEY_INVENTORY_SIZE; ++i)
    {
        character->inventory[i] = NULL;
    }

    character->inventory_count = 0;
}

const char *journey_character_get_class_name(
    JourneyClass class
)
{
    switch (class)
    {
        case JOURNEY_CLASS_WARRIOR:
            return "Warrior";

        case JOURNEY_CLASS_RANGER:
            return "Ranger";

        case JOURNEY_CLASS_MAGE:
            return "Mage";

        default:
            return "Unknown";
    }
}

void journey_character_add_experience(
    JourneyCharacter *character,
    int experience
)
{
    if (character == NULL || experience < 0)
    {
        return;
    }

    character->experience += experience;
}

void journey_character_add_copper(
    JourneyCharacter *character,
    int copper
)
{
    if (character == NULL || copper < 0)
    {
        return;
    }

    character->copper += copper;
}

bool journey_character_add_item(
    JourneyCharacter *character,
    const JourneyItemDefinition *item
)
{
    if (character == NULL ||
        item == NULL ||
        character->inventory_count >= JOURNEY_INVENTORY_SIZE)
    {
        return false;
    }

    character->inventory[
        character->inventory_count
    ] = item;

    character->inventory_count++;

    return true;
}

int journey_character_get_item_count(
    const JourneyCharacter *character
)
{
    if (character == NULL)
    {
        return 0;
    }

    return character->inventory_count;
}

const JourneyItemDefinition *
journey_character_get_item(
    const JourneyCharacter *character,
    int index
)
{
    if (character == NULL ||
        index < 0 ||
        index >= character->inventory_count)
    {
        return NULL;
    }

    return character->inventory[index];
}

