# Journey - Land of the Undead

Journey - Land of the Undead is an open-source, single-player role-playing game written in C for Linux.

The game is inspired by classic role-playing games such as Ultima IV, with tactical, turn-based combat and an entirely undead-themed world.

## Project Status

Journey is currently in early engine and gameplay development.

Completed checkpoints:

- Checkpoint 001 - Initial buildable Journey skeleton
- Checkpoint 002 - Scalable renderer
- Checkpoint 003 - Input system
- Checkpoint 004 - Tile map system
- Checkpoint 005 - Map rendering
- Checkpoint 006 - Player movement
- Checkpoint 007 - Player presentation
- Checkpoint 008 - Grave interaction
- Checkpoint 009 - Scrolling camera and expanded world map
- Checkpoint 010 - Dungeon entry, dungeon rendering, dungeon movement, collision, and camera
- Checkpoint 011 - Data-driven monster definition and monster rendering
- Checkpoint 012 - README update and project documentation
- Checkpoint 013 - Data-driven monster definitions and rendering
- Checkpoint 014 - Basic monster combat and rewards
- Checkpoint 015 - Inventory and chest item rewards
- Checkpoint 016 - Basic character progression
- Checkpoint 017 - Monster counterattack and character damage (Upcoming)

The current prototype contains:

- A 128 x 72 overworld
- An expanded overworld with forests, water, roads, graves, and a dungeon entrance
- Player movement and collision on the overworld
- A scrolling overworld camera
- Ancient grave interaction
- Dungeon entry using the E key
- A 32 x 24 dungeon
- Dungeon walls and collision
- Dungeon movement
- A scrolling dungeon camera
- Location-based rendering and movement
- A data-driven monster definition system
- A Skeletal Rat monster definition
- Monster health, damage, defence, movement, experience, and copper reward data
- Monster attack and undead type definitions
- Monster placement and rendering in the overworld
- Basic player-versus-monster combat
- Monster damage and defeat
- Experience rewards
- Copper rewards
- Character levels
- Warrior, Ranger, and Mage character classes
- Class-specific starting attributes and health
- Character health and maximum health
- Automatic level-up from experience
- An eight-slot character inventory
- Dungeon chest interaction
- Healing Potion item rewards
- Monster counterattacks
- Character damage from monster attacks

The current combat system is an early prototype. The player can attack an adjacent monster, monsters can respond with basic attacks, and defeating a monster awards experience and copper.

Character progression currently supports the first level-up. The current prototype uses a simple experience threshold and increases maximum health when the character reaches level 2.

The inventory system currently stores item definitions rather than individual item instances. The first implemented item is a Healing Potion awarded from a dungeon chest.

Monsters currently use simple placeholder graphics rather than finished artwork.

Towns and settlements have not yet been implemented.

## Planned Features

- Single-player, single-character RPG
- Warrior, Ranger, and Mage classes
- Tactical, turn-based combat
- Undead-themed enemies and world
- Overworld exploration
- Towns and settlements
- Wilderness areas
- Ruins and other areas of interest
- Multi-level dungeons
- Weapons, armour, and magical equipment
- Copper-based economy
- Experience and character levels
- Data-driven monsters, equipment, spells, maps, NPCs, and encounters
- Pixel-art-inspired graphics
- 320 x 180 logical game resolution
- Integer scaling to larger 16:9 resolutions
- Keyboard and controller support
- Linux support

## Development Platform

Journey is being developed primarily for Linux.

The current development environment is:

- Linux Mint 22.3

Earlier development was performed on:

- Ubuntu 24.04

The project is intended to remain compatible with Debian-based Linux distributions where practical.

The project has been successfully built and tested after moving from Ubuntu 24.04 to Linux Mint 22.3. The existing build continues to work with:

    cmake --build build

The resulting executable can be run with:

    ./build/journey

Development is currently being performed using the Xed text editor on Linux Mint.

## Technology

- Language: C17
- Build system: CMake
- Build tool: Ninja
- Graphics, input, and audio: SDL3
- Logical resolution: 320 x 180
- Source control: Git
- Repository hosting: GitHub

SDL3 is included in the repository as a Git submodule under the vendored/SDL directory. The project does not depend on a system-provided SDL3 development package.

## Repository Structure

The main source code is located in the src directory.

Current source components include:

- camera - world and dungeon camera
- character - player character classes, attributes, health, progression, inventory, and character state
- dungeon - dungeon map and tile definitions
- game - game location and state definitions
- input - keyboard input
- item - data-driven item definitions
- map - overworld map and tile definitions
- monster - data-driven monster definitions and monster state
- player - player state, movement, and basic monster combat
- renderer - graphics rendering
- main - program entry point and game loop

SDL3 is maintained under the vendored/SDL directory.

CMakeLists.txt contains the project build configuration.

README.md contains project documentation.

.gitignore contains Git ignore rules.

## Development Philosophy

The engine is being designed to keep game rules and content as data-driven as practical.

The long-term goal is to avoid hard-coding individual monsters, weapons, spells, NPCs, and other game content throughout the engine.

C provides the underlying game engine, while data will eventually define much of the game's content.

Git checkpoints are used throughout development so that major milestones remain identifiable and recoverable.

Each checkpoint should leave the project in a buildable and playable state whenever practical.

The game is intended to echo the design philosophy of classic RPGs such as Ultima IV. Movement, exploration, encounters, character development, and other systems will be developed with that style of gameplay in mind while using an original setting, world, characters, and game systems.

## Graphics

The game uses a logical resolution of 320 x 180.

The renderer is designed to scale the game to larger 16:9 resolutions while keeping the internal game world independent of the physical display resolution.

Integer scaling is preferred for the retro pixel-art presentation.

The game will eventually use deliberately simple artwork inspired by classic RPGs. We are not currently trying to create finished or polished sprites.

The player, monsters, map, and dungeon currently use simple placeholder or prototype graphics while the underlying game systems are being developed.

## World

The game world will eventually contain:

- Overworld areas
- Towns
- Wilderness
- Ruins
- Graveyards
- Dungeons
- Other areas of interest

The current overworld is 128 x 72 tiles.

The current prototype overworld contains:

- Grassland
- Forest regions
- Water features
- Stone roads
- An ancient graveyard area
- An ancient dungeon entrance
- A Skeletal Rat encounter

The player cannot pass through forest or water tiles.

The current dungeon prototype is 32 x 24 tiles and contains:

- Floors
- Walls
- A dungeon exit
- A chest

Maps are intended to become increasingly data-driven as development progresses.

## Gameplay

The player can currently choose one of three classes:

- Warrior
- Ranger
- Mage

Each class currently has different starting attributes and maximum health.

The current prototype supports:

- Character creation
- Warrior, Ranger, and Mage classes
- Overworld exploration
- Dungeon exploration
- Player movement
- Collision
- Grave interaction
- Dungeon entry and exit
- Chest interaction
- Basic monster combat
- Monster counterattacks
- Character health
- Monster health
- Experience rewards
- Character levels
- Copper rewards
- Basic inventory management
- Healing Potion item rewards

The current character classes have different starting attributes:

- Warrior - high Strength and health
- Ranger - high Agility with balanced Strength and Intelligence
- Mage - high Intelligence with lower Strength and health

The current character progression system begins at level 1.

A character currently reaches level 2 after earning 4 experience. Upon reaching level 2, maximum health increases by 20 and current health is restored to the new maximum.

Further levels, abilities, equipment restrictions, and class progression have not yet been implemented.

## Combat

Combat is currently a simple prototype intended to establish the foundation for a future tactical, turn-based combat system.

The player can attack an adjacent monster by pressing E.

The current player attack deals a fixed amount of damage.

The monster definition supplies its damage value for counterattacks.

When a monster survives a player attack, it can attack the character.

Character health is reduced by incoming monster damage and cannot fall below zero.

When a monster is defeated, the character receives:

- Experience
- A random amount of copper within the monster's defined reward range

The current combat system does not yet include:

- Class-based attacks
- Weapon damage
- Armour
- Attack rolls
- Defence calculations
- Critical hits
- Status effects
- Spells
- Multiple simultaneous enemies
- Full turn management
- Character death handling
- Monster AI
- Monster movement during combat

These systems will be developed incrementally.

## Character Progression

Character definitions currently contain:

- Name
- Class
- Strength
- Agility
- Intelligence
- Health
- Maximum health
- Level
- Experience
- Copper
- Inventory

The three available classes are:

- Warrior
- Ranger
- Mage

Characters begin at level 1 with 0 experience and 100 copper.

The current prototype has a simple level 2 threshold of 4 experience.

Leveling currently increases maximum health by 20 and restores the character to full health.

The progression system is intentionally simple at this stage and will eventually be expanded into a more complete class and level system.

## Inventory and Items

Characters currently have an eight-slot inventory.

The inventory stores references to data-driven item definitions.

The first implemented item is the Healing Potion.

The current dungeon chest awards one Healing Potion when opened, provided the character has available inventory space.

The current inventory system does not yet implement:

- Using items
- Removing items
- Stacking items
- Equipment
- Weapons
- Armour
- Item quantities
- Shops
- Item purchasing or selling

These systems are planned for future development.

## Monsters

The monster system is being developed as a foundation for future encounters.

Monster definitions currently contain data such as:

- Name
- Maximum health
- Damage
- Defence
- Movement
- Experience reward
- Minimum copper reward
- Maximum copper reward
- Attack type
- Undead type

The current implemented monster is:

- Skeletal Rat

The current monster system separates a monster's definition from its runtime state.

A monster definition contains shared data describing a monster type, while an individual monster instance contains runtime information such as:

- Position
- Current health
- Reference to its definition

This allows multiple instances of the same monster type to share a common definition while maintaining their own state.

The long-term goal is to use this system for a larger data-driven enemy system.

## Data-Driven Design

Game content will eventually be represented as data rather than requiring individual C code for every object.

This approach is planned for:

- Monsters
- Weapons
- Armour
- Spells
- NPCs
- Maps
- Shops
- Encounters
- Treasure
- Quests
- Items

Monster definitions are currently the first practical implementation of this approach.

The item system is also beginning to use the same separation between definitions and runtime character state.

This approach should make it easier to expand the game and allow contributors to add content without modifying the core engine.

## Controls

The current keyboard controls are:

- W / Up Arrow - Move up
- S / Down Arrow - Move down
- A / Left Arrow - Move left
- D / Right Arrow - Move right
- E - Interact and attack
- Escape - Quit

Controller support is planned but is not yet implemented as a complete gameplay control system.

## Building

Journey uses CMake and Ninja.

A configured build can be compiled with:

    cmake --build build

The game can then be launched with:

    ./build/journey

The project should remain buildable after each development checkpoint whenever practical.

## Git Checkpoints

Git checkpoints are used to mark meaningful development milestones.

Current checkpoint tags include:

- checkpoint-001
- checkpoint-002
- checkpoint-003
- checkpoint-004
- checkpoint-005
- checkpoint-006
- checkpoint-007
- checkpoint-008
- checkpoint-009
- checkpoint-010
- checkpoint-011
- checkpoint-012
- checkpoint-013
- checkpoint-014
- checkpoint-015
- checkpoint-016

The monster counterattack work is the next development milestone and is represented by Checkpoint 017 once tagged.

The project currently uses Git tags to make it possible to return to known-good development states as the engine evolves.

## License

The game source code is intended to be released under the GNU General Public License version 3.0 (GPL-3.0).

Original artwork and game data are intended to be released under the Creative Commons Attribution-ShareAlike 4.0 International license (CC BY-SA 4.0).

These licenses will be formalized in the repository as the project develops.

