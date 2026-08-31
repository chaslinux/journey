#ifndef JOURNEY_ENCOUNTER_H
#define JOURNEY_ENCOUNTER_H

#include "character.h"
#include "monster.h"
#include "player.h"

void journey_encounter_fight(
    JourneyPlayer *player,
    JourneyCharacter *character,
    JourneyMonster *monster
);

void journey_encounter_monster_turn(
    JourneyCharacter *character,
    const JourneyMonster *monster
);

#endif
