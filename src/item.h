#ifndef JOURNEY_ITEM_H
#define JOURNEY_ITEM_H

typedef enum
{
    JOURNEY_ITEM_NONE = 0,
    JOURNEY_ITEM_HEALING_POTION
} JourneyItemType;

typedef struct
{
    JourneyItemType type;
    const char *name;
} JourneyItemDefinition;

extern const JourneyItemDefinition
    JOURNEY_ITEM_DEFINITION_HEALING_POTION;

#endif

