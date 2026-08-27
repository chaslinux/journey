# Journey — Land of the Undead

Journey — Land of the Undead is an open-source, single-player role-playing game written in C for Linux.

The game is inspired by classic role-playing games such as Ultima IV, with tactical, turn-based combat and an entirely undead-themed world.

## Project Status

Journey is currently in early engine development.

Completed checkpoints:

- Checkpoint 001 — Initial buildable Journey skeleton
- Checkpoint 002 — Scalable renderer
- Checkpoint 003 — Input system
- Checkpoint 004 — Tile map system
- Checkpoint 005 — Map rendering
- Checkpoint 006 — Player movement
- Checkpoint 007 — Player presentation
- Checkpoint 008 — Grave interaction
- Checkpoint 009 — Scrolling camera and expanded world map

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
- 320×180 logical game resolution
- Integer scaling to larger 16:9 resolutions
- Keyboard and controller support
- Linux support

## Development Platform

Journey is being developed primarily for Linux.

The initial development environments are:

- Linux Mint 22.3
- Ubuntu 24.04

The project is intended to remain compatible with Debian-based Linux distributions where practical.

## Technology

- Language: C17
- Build system: CMake
- Build tool: Ninja
- Graphics, input, and audio: SDL3
- Logical resolution: 320×180
- Source control: Git
- Repository hosting: GitHub

SDL3 is included in the repository as a Git submodule under the vendored/SDL directory. The project does not depend on a system-provided SDL3 development package.

## Repository Structure

The main source code is located in the src directory.

Current source components include:

- camera — world camera and scrolling
- input — keyboard and controller input
- map — world map and tile definitions
- player — player state and movement
- renderer — graphics rendering
- main — program entry point and game loop

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

## Graphics

The game uses a logical resolution of 320×180.

The renderer is designed to scale the game to larger 16:9 resolutions while keeping the internal game world independent of the physical display resolution.

Integer scaling is preferred for the retro pixel-art presentation.

The game will eventually use deliberately simple artwork inspired by classic RPGs. We are not currently trying to create finished or polished sprites.

## World

The game world will eventually contain:

- Overworld areas
- Towns
- Wilderness
- Ruins
- Graveyards
- Dungeons
- Other areas of interest

Maps are intended to become increasingly data-driven as development progresses.

The current world is an expanded prototype overworld used to develop the map, camera, movement, and interaction systems.

## Gameplay

The player will eventually choose one of three classes:

- Warrior
- Ranger
- Mage

Each class will have different strengths, weaknesses, equipment restrictions, and abilities.

The game will feature:

- Exploration
- Tactical turn-based combat
- Experience and levels
- Equipment
- Weapons and armour
- Magic
- Copper-based economy
- Undead enemies
- Towns and shops
- Dungeons and bosses

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

This should make it easier to expand the game and allow contributors to add content without modifying the core engine.

## License

The game source code is intended to be released under the GNU General Public License version 3.0 (GPL-3.0).

Original artwork and game data are intended to be released under the Creative Commons Attribution-ShareAlike 4.0 International license (CC BY-SA 4.0).

These licenses will be formalized in the repository as the project develops.

