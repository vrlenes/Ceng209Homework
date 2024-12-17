Dungeon Adventure Game

Game Description

Dungeon Adventure Game is a text-based console adventure game where players explore a dungeon, collect items, fight creatures, and aim to defeat the ultimate boss, the Dragon. The player navigates through rooms, discovers hidden treasures, and engages in battles to survive and win.

Gameplay Rules and Instructions

Starting the Game:

The player starts at room [0,0] in a 4x4 dungeon grid.

Initial stats: Health = 100, Strength = 10.

Available Commands:

move <direction>: Move in a specified direction (up, down, left, right).

look: Inspect the current room for creatures and items.

pickup: Collect an item in the current room.

drop: Drop an item from the player's inventory.

attack: Attack a creature in the current room.

inventory: Show the player's inventory.

stats: Display the player's health and strength.

map: Show the dungeon grid and the player's current position.

save <filename>: Save the current game state to a file.

load <filename>: Load a previously saved game state.

exit: Exit the game.

The Dungeon:

The dungeon consists of 16 rooms arranged in a 4x4 grid.

Each room may contain:

Items: Weapons (e.g., swords, axes) or potions that affect player stats.

Creatures: Enemies like goblins, spiders, and the final boss, the Dragon.

Objective:

Explore all the rooms, collect powerful items, and defeat creatures.

Defeat the Dragon in the final room [3,3] to win the game.

File Structure

The project consists of the following files:

main.c: The entry point of the game. Manages the main menu and game loop.

game.c / game.h: Handles game initialization, room creation, and linking rooms.

playerFuncs.c / playerFuncs.h: Implements player actions such as movement, item management, and combat.

menu.c / menu.h: Provides functions to save and load the game state.

README.md: This file explaining the game and its structure.

Code Overview

Structures:

Item: Represents objects like weapons and potions.

Creature: Represents enemies encountered in the dungeon.

Room: Defines each room, its description, items, and creatures.

Player: Holds player information, including health, strength, and inventory.

Core Functions:

initialize_game: Sets up the dungeon, player, and rooms.

move: Allows the player to navigate through the dungeon.

attack: Engages combat with creatures in the current room.

pickup / dropItem: Manages the player's inventory.

save_game / load_game: Saves and restores the game state.

Game Flow:

The player starts at the dungeon's entrance.

Rooms are explored by moving in the specified directions.

Items are collected to boost stats, and creatures must be defeated.

The game ends when the Dragon is defeated.

How to Compile and Run

Use a C compiler such as GCC.

To compile the project, run the following command:

gcc main.c game.c playerFuncs.c menu.c -o dungeon_game

Run the compiled game:

./dungeon_game

To clean up the compiled files:

rm dungeon_game

Example Gameplay

=== Dungeon Adventure Game ===
1. New Game
2. Load Game
3. Exit
Enter your choice: 1

Available commands: move <direction>, map, look, pickup, drop, attack, inventory, stats, save <filename>, load <filename>, exit
> move right
You moved right.
> look
Room description: A dark room filled with webs and a lurking giant spider.
A creature is here: Giant Spider (Health: 40)
> attack
You attack the Giant Spider!
The Giant Spider attacks you!
...

Requirements

A C compiler (e.g., GCC)

A terminal or command-line interface

Contribution

Contributions are welcome! If you'd like to improve the game, please fork the repository, make changes, and submit a pull request. You can also open an issue for bug reports or feature suggestions.

License

This project is released under the MIT License.

