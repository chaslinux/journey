#include <stdbool.h>

#include <SDL3/SDL.h>

#include "camera.h"
#include "character.h"
#include "dungeon.h"
#include "game.h"
#include "input.h"
#include "encounter.h"
#include "map.h"
#include "monster.h"
#include "player.h"
#include "renderer.h"

static JourneyClass journey_next_class(
    JourneyClass class
)
{
    switch (class)
    {
        case JOURNEY_CLASS_WARRIOR:
            return JOURNEY_CLASS_RANGER;

        case JOURNEY_CLASS_RANGER:
            return JOURNEY_CLASS_MAGE;

        case JOURNEY_CLASS_MAGE:
        default:
            return JOURNEY_CLASS_WARRIOR;
    }
}

static JourneyClass journey_previous_class(
    JourneyClass class
)
{
    switch (class)
    {
        case JOURNEY_CLASS_WARRIOR:
            return JOURNEY_CLASS_MAGE;

        case JOURNEY_CLASS_RANGER:
            return JOURNEY_CLASS_WARRIOR;

        case JOURNEY_CLASS_MAGE:
        default:
            return JOURNEY_CLASS_RANGER;
    }
}

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log(
            "SDL initialization failed: %s",
            SDL_GetError()
        );

        return 1;
    }

    SDL_Log("Journey started.");

    SDL_Log(
        "SDL version: %d.%d.%d",
        SDL_MAJOR_VERSION,
        SDL_MINOR_VERSION,
        SDL_MICRO_VERSION
    );

    JourneyRenderer renderer = {0};

    if (!journey_renderer_init(&renderer))
    {
        SDL_Quit();
        return 1;
    }

    JourneyMap map = {0};
    journey_map_init(&map);

    JourneyPlayer player = {0};
    journey_player_init(&player, &map);

    JourneyCharacter character = {0};

	JourneyMonster monsters[JOURNEY_MAX_MONSTERS] = {0};

	journey_monster_init(
		&monsters[0],
		&JOURNEY_MONSTER_SKELETAL_RAT,
		75,
		34
	);

	journey_monster_init(
		&monsters[1],
		&JOURNEY_MONSTER_SKELETAL_RAT,
		80,
		34
	);

    JourneyDungeon dungeon = {0};
    journey_dungeon_init(&dungeon);

    JourneyCamera camera = {0};
    journey_camera_init(&camera, &player);

    JourneyInput input = {0};
    journey_input_init(&input);

    JourneyGameState game_state =
        JOURNEY_GAME_CHARACTER_CREATION;

    JourneyLocation location =
        JOURNEY_LOCATION_OVERWORLD;

    JourneyClass selected_class =
        JOURNEY_CLASS_WARRIOR;

    bool running = true;
    int engaged_monster = -1;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            journey_input_process_event(
                &input,
                &event
            );

            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                journey_renderer_resize(&renderer);
            }
        }

        if (input.quit)
        {
            running = false;
        }

        /*
         * ==================================================
         * CHARACTER CREATION
         * ==================================================
         */
        if (game_state == JOURNEY_GAME_CHARACTER_CREATION)
        {
            /*
             * Up/Down and W/S cycle through classes.
             */
            if (input.move_up)
            {
                selected_class =
                    journey_previous_class(
                        selected_class
                    );

                SDL_Log(
                    "Selected class: %s",
                    journey_character_get_class_name(
                        selected_class
                    )
                );
            }

            if (input.move_down)
            {
                selected_class =
                    journey_next_class(
                        selected_class
                    );

                SDL_Log(
                    "Selected class: %s",
                    journey_character_get_class_name(
                        selected_class
                    )
                );
            }

            /*
             * E confirms the selected class.
             */
            if (input.interact)
            {
                journey_character_init(
                    &character,
                    selected_class
                );

                game_state =
                    JOURNEY_GAME_PLAYING;

                SDL_Log(
                    "Character created: %s",
                    journey_character_get_class_name(
                        character.class
                    )
                );

                SDL_Log(
                    "Level: %d  Health: %d/%d  Copper: %d",
                    character.level,
                    character.health,
                    character.max_health,
                    character.copper
                );
            }
        }

        /*
         * ==================================================
         * GAMEPLAY
         * ==================================================
         */
        else if (game_state == JOURNEY_GAME_PLAYING)
        {
            const int old_x = player.x;
            const int old_y = player.y;
            bool moved = false;

            /*
             * Use a Healing Potion when I is pressed.
             */
            if (input.use_item)
            {
                const int old_health = character.health;

                if (journey_character_use_healing_potion(
                        &character))
                {
                    SDL_Log(
                        "You use a Healing Potion. "
                        "Health: %d/%d",
                        character.health,
                        character.max_health
                    );
                }
                else if (old_health >= character.max_health)
                {
                    SDL_Log(
                        "You are already at full health."
                    );
                }
                else
                {
                    SDL_Log(
                        "You do not have a Healing Potion."
                    );
                }
            }

            /*
             * Movement depends on the current location.
             */
            if (location == JOURNEY_LOCATION_OVERWORLD)
            {
                if (input.move_up)
                {
                    moved = journey_player_move_up(
                        &player,
                        &map,
                        monsters
                    );
                }
                else if (input.move_down)
                {
                    moved = journey_player_move_down(
                        &player,
                        &map,
                        monsters
                    );
                }
                else if (input.move_left)
                {
                    moved = journey_player_move_left(
                        &player,
                        &map,
                        monsters
                    );
                }
                else if (input.move_right)
                {
                    moved = journey_player_move_right(
                        &player,
                        &map,
                        monsters
                    );
                }
            }
            else if (location == JOURNEY_LOCATION_DUNGEON)
            {
                if (input.move_up)
                {
                    journey_player_move_dungeon_up(
                        &player,
                        &dungeon
                    );
                }

                if (input.move_down)
                {
                    journey_player_move_dungeon_down(
                        &player,
                        &dungeon
                    );
                }

                if (input.move_left)
                {
                    journey_player_move_dungeon_left(
                        &player,
                        &dungeon
                    );
                }

                if (input.move_right)
                {
                    journey_player_move_dungeon_right(
                        &player,
                        &dungeon
                    );
                }
            }

            /*
             * An engaged monster gets a response after
             * the player moves, as long as the player
             * remains adjacent.
             */
            if (location == JOURNEY_LOCATION_OVERWORLD &&
                moved &&
                engaged_monster >= 0 &&
                engaged_monster < JOURNEY_MAX_MONSTERS)
            {
                JourneyMonster *monster =
                    &monsters[engaged_monster];

                if (monster->health > 0 &&
                    journey_player_is_adjacent_to_monster(
                        &player,
                        monster))
                {
                    journey_encounter_monster_turn(
                        &character,
                        monster
                    );
                }
            }

            /*
             * Moving away from the engaged monster
             * cleanly ends the engagement.
             */
            if (engaged_monster >= 0 &&
                engaged_monster < JOURNEY_MAX_MONSTERS)
            {
                JourneyMonster *monster =
                    &monsters[engaged_monster];

                if (monster->health <= 0 ||
                    !journey_player_is_adjacent_to_monster(
                        &player,
                        monster))
                {
                    engaged_monster = -1;
                }
            }

            /*
             * Attack an adjacent monster when E is pressed.
             */
            if (location == JOURNEY_LOCATION_OVERWORLD &&
                input.interact)
            {
                int target_monster = -1;

                for (int i = 0;
                     i < JOURNEY_MAX_MONSTERS;
                     ++i)
                {
                    if (monsters[i].health > 0 &&
                        journey_player_is_adjacent_to_monster(
                            &player,
                            &monsters[i]))
                    {
                        target_monster = i;
                        break;
                    }
                }

                if (target_monster >= 0)
                {
                    JourneyMonster *monster =
                        &monsters[target_monster];

                    engaged_monster = target_monster;

                    const int old_health =
                        monster->health;

                    journey_encounter_fight(
                        &player,
                        &character,
                        monster
                    );

                    if (monster->health == 0 &&
                        old_health > 0)
                    {
                        const int experience =
                            monster->definition->experience;

                        const int copper_range =
                            monster->definition->copper_max -
                            monster->definition->copper_min + 1;

                        const int copper =
                            monster->definition->copper_min +
                            SDL_rand(copper_range);

                        const bool leveled_up =
                            journey_character_add_experience(
                                &character,
                                experience
                            );

                        journey_character_add_copper(
                            &character,
                            copper
                        );

                        engaged_monster = -1;

                        if (leveled_up)
                        {
                            SDL_Log(
                                "You reached level %d! Max health is now %d.",
                                character.level,
                                character.max_health
                            );
                        }

                        SDL_Log(
                            "%s defeated! "
                            "You gain %d experience and %d copper. "
                            "Total XP: %d  Copper: %d",
                            monster->definition->name,
                            experience,
                            copper,
                            character.experience,
                            character.copper
                        );
                    }
                }
            }

            /*
             * Enter the dungeon when E is pressed
             * while standing on the dungeon entrance.
             */
            if (location == JOURNEY_LOCATION_OVERWORLD &&
                input.interact)
            {
                const JourneyTile *tile =
                    journey_map_get_tile(
                        &map,
                        player.x,
                        player.y
                    );

                if (tile != NULL &&
                    tile->type == JOURNEY_TILE_DUNGEON)
                {
                    location =
                        JOURNEY_LOCATION_DUNGEON;

                    player.x = 16;
                    player.y = 21;

                    SDL_Log(
                        "You enter the ancient dungeon."
                    );
                }
            }

            /*
             * Interact with the dungeon exit
             * or an adjacent chest when E is pressed.
             */
            if (location == JOURNEY_LOCATION_DUNGEON &&
                input.interact)
            {
                const JourneyDungeonTile *tile =
                    journey_dungeon_get_interaction(
                        &dungeon,
                        player.x,
                        player.y
                    );

                if (tile != NULL)
                {
                    if (tile->type ==
                        JOURNEY_DUNGEON_EXIT)
                    {
                        location =
                            JOURNEY_LOCATION_OVERWORLD;

                        player.x = 102;
                        player.y = 49;

                        SDL_Log(
                            "You exit the ancient dungeon."
                        );
                    }
					else if (tile->type ==
							 JOURNEY_DUNGEON_CHEST)
					{
						JourneyDungeonTile *chest =
							(JourneyDungeonTile *)tile;

						chest->type =
							JOURNEY_DUNGEON_CHEST_OPEN;

						chest->walkable = true;

						SDL_Log(
							"You open the ancient chest."
						);

						if (journey_character_add_item(
								&character,
								&JOURNEY_ITEM_DEFINITION_HEALING_POTION))
						{
							SDL_Log(
								"You found: %s.",
								JOURNEY_ITEM_DEFINITION_HEALING_POTION.name
							);
						}
						else
						{
							SDL_Log(
								"Your inventory is full."
							);
						}
					}
                }
            }

            /*
             * Trigger the grave interaction when
             * the player enters a grave tile.
             */
            if (location == JOURNEY_LOCATION_OVERWORLD &&
                (player.x != old_x ||
                 player.y != old_y))
            {
                const JourneyTile *tile =
                    journey_map_get_tile(
                        &map,
                        player.x,
                        player.y
                    );

                if (tile != NULL &&
                    tile->type == JOURNEY_TILE_GRAVE)
                {
                    SDL_Log(
                        "You discovered an ancient grave."
                    );
                }
            }

            /*
             * Camera follows the player.
             */
            if (location == JOURNEY_LOCATION_OVERWORLD)
            {
                journey_camera_follow(
                    &camera,
                    &player,
                    map.width,
                    map.height
                );
            }
            else if (location == JOURNEY_LOCATION_DUNGEON)
            {
                journey_camera_follow(
                    &camera,
                    &player,
                    dungeon.width,
                    dungeon.height
                );
            }
        }

        /*
         * Reset one-frame input.
         */
        journey_input_init(&input);

        /*
         * ==================================================
         * RENDER
         * ==================================================
         */
        journey_renderer_begin(&renderer);

        if (game_state == JOURNEY_GAME_CHARACTER_CREATION)
        {
            journey_renderer_draw_character_creation(
                &renderer,
                selected_class
            );
        }
        else if (game_state == JOURNEY_GAME_PLAYING)
        {
            if (location == JOURNEY_LOCATION_OVERWORLD)
            {
                journey_renderer_draw_map(
                    &renderer,
                    &map,
                    &camera
                );
            }
            else if (location == JOURNEY_LOCATION_DUNGEON)
            {
                journey_renderer_draw_dungeon(
                    &renderer,
                    &dungeon,
                    &camera
                );
            }

            if (location == JOURNEY_LOCATION_OVERWORLD)
            {
                for (int i = 0;
                     i < JOURNEY_MAX_MONSTERS;
                     ++i)
                {
                    if (monsters[i].definition != NULL &&
                        monsters[i].health > 0)
                    {
                        journey_renderer_draw_monster(
                            &renderer,
                            &monsters[i],
                            &camera
                        );
                    }
                }
            }

            journey_renderer_draw_player(
                &renderer,
                &player,
                &camera
            );
        }

        journey_renderer_present(&renderer);
    }

    journey_renderer_shutdown(&renderer);
    SDL_Quit();

    return 0;
}

