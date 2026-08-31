#include <stddef.h>
#include <SDL3/SDL.h>

#include "encounter.h"

void journey_encounter_monster_turn(
    JourneyCharacter *character,
    const JourneyMonster *monster
)
{
    if (character == NULL ||
        monster == NULL ||
        monster->definition == NULL ||
        monster->health <= 0)
    {
        return;
    }

    const int monster_damage =
        monster->definition->damage;

    journey_character_take_damage(
        character,
        monster_damage
    );

    SDL_Log(
        "The %s attacks you for %d damage. "
        "Health: %d/%d",
        monster->definition->name,
        monster_damage,
        character->health,
        character->max_health
    );
}

void journey_encounter_fight(
    JourneyPlayer *player,
    JourneyCharacter *character,
    JourneyMonster *monster
)
{
    if (player == NULL ||
        character == NULL ||
        monster == NULL ||
        monster->definition == NULL ||
        monster->health <= 0)
    {
        return;
    }

    const int old_health = monster->health;

    journey_player_attack_monster(
        player,
        monster
    );

    if (monster->health != old_health)
    {
        SDL_Log(
            "You attack the %s for %d damage. "
            "Health: %d/%d",
            monster->definition->name,
            old_health - monster->health,
            monster->health,
            monster->definition->max_health
        );
    }

    if (monster->health > 0)
    {
        journey_encounter_monster_turn(
            character,
            monster
        );
    }
}

