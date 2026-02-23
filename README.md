# Console-Based Adventure Game (C++)

A console-based text adventure game developed in C++ featuring room navigation, combat encounters, item collection, and inventory management. The game is fully command-driven and runs in the terminal.

## Features
- Text-based navigation using directional commands (N, E, S, W)
- Multiple locations with unique descriptions
- Item system including weapons, armour, potions, and treasure
- Player, monster, and boss combat mechanics
- Inventory management and game state tracking
- Modular object-oriented design using C++ classes

## Project Structure
- `Player`, `Monster`, and `Boss` classes handle character logic and combat
- `Location` and `GameWorld` manage navigation and environments
- `Item`, `Weapon`, `Armour`, `Potion`, and `Treasure` implement the item system
- Main game loop processes user commands via console input

## How to Run
Compile and run the game using a C++ compiler:

```bash
g++ *.cpp -o AdventureGame
./AdventureGame
