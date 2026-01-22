cmake_minimum_required(VERSION 4.0)
project(gameska)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gameska
        main.cpp

        backEnd/render/RenderEngine.h
        backEnd/render/RenderEngine.cpp
        backEnd/render/ConsoleBuffer.h
        backEnd/render/ConsoleBuffer.cpp
        backEnd/render/Camera.h
        backEnd/render/Camera.cpp
        backEnd/render/TerminalUtils.h
        backEnd/render/TerminalUtils.cpp

        backEnd/gameLogic/InputHandler.h
        backEnd/gameLogic/InputHandler.cpp
        backEnd/gameLogic/Game.h
        backEnd/gameLogic/Game.cpp
        backEnd/gameLogic/LevelLogic.h
        backEnd/gameLogic/LevelLogic.cpp

        backEnd/types/Command.h
        backEnd/types/Vec2.h
        backEnd/types/Color.h

        frontEnd/Classes/MainInheriteClass.h
        frontEnd/Classes/MainInheriteClass.cpp
        frontEnd/Classes/Enemy.h
        frontEnd/Classes/Enemy.cpp
        frontEnd/Classes/Map.h
        frontEnd/Classes/Map.cpp
        frontEnd/Classes/MapBlock.h
        frontEnd/Classes/MapBlock.cpp
        frontEnd/Classes/Player.h
        backEnd/types/Vec2.h
        frontEnd/Classes/Item.h
        frontEnd/Classes/Item.cpp
        frontEnd/Classes/Weapon.cpp
        frontEnd/Classes/Weapon.h
        frontEnd/Classes/HealingPotion.cpp
        frontEnd/Classes/HealingPotion.h
        frontEnd/Classes/Key.cpp
        frontEnd/Classes/Key.h
        frontEnd/Classes/Player.cpp

        frontEnd/Classes/Menu/MainMenuDesign.h
        frontEnd/Classes/Menu/MainMenuDesign.cpp

        frontEnd/Classes/Menu/CreditsScreen.h
        frontEnd/Classes/Menu/CreditsScreen.cpp

        frontEnd/Classes/Menu/StoryScreen.h
        frontEnd/Classes/Menu/StoryScreen.cpp

        frontEnd/Classes/Menu/MenuCommands.h
        frontEnd/Classes/Weapon.h
        frontEnd/Classes/Spider.h
        frontEnd/Classes/Skeleton.h
        frontEnd/Classes/Menu/PauseMenu.h
        frontEnd/Classes/Menu/PauseMenu.cpp
        backEnd/render/UIRender.h
        backEnd/render/UIRender.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)