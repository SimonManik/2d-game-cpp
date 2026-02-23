# 🎮 PAIN & SUFFERING

A console-based 2D RPG adventure written entirely in C++. The project is built on a custom terminal rendering engine and features enemy combat, map exploration.

## 🚀 About the Project
This game was developed as a team school project with the goal of building game logic and rendering from scratch, without relying on existing game engines (like Unity or Unreal). The architecture strictly separates the `backEnd` (game loop, rendering) and `frontEnd` (game entities, UI).

## 🛠️ My Role
Within the team, I was responsible for the following key areas:
* **UI Design & Development:** Implemented the user interface, including player stats and inventory display.
* **Game Menu & Flow:** Created the main menu, pause screen, story screen, and credits screen.
* **Audio Integration:** Set up background music for various game states (menu theme, dungeon theme).

## 🏗️ Architecture
* **Back-end:** Custom `RenderEngine` and `ConsoleBuffer` for efficient ASCII graphics rendering in the terminal. Input processing (`InputHandler`) and the main game loop.
* **Front-end:** Classes for game entities (`Player`, `Enemy`, `Dragon`, `Skeleton`) and interactive items (`Weapon`, `Key`, `HealingPotion`).

## ⚙️ How to Build and Run
The project uses CMake as its build system.
1. Clone the repository: ``git clone https://github.com/SimonManik/2d-game-cpp.git``
2. Open the project in your preferred IDE (CLion, Visual Studio) or use the terminal.
3. Build using CMake and run the generated `gameska.exe` executable.
