cmake_minimum_required(VERSION 4.0)
project(gameska)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gameska
        main.cpp

        backEnd/render/renderEngine.h
        backEnd/render/renderEngine.cpp
        backEnd/render/consoleBuffer.h
        backEnd/render/consoleBuffer.cpp
        backEnd/render/Camera.h
        backEnd/render/Camera.cpp
        backEnd/render/TerminalUtils.h
        backEnd/render/TerminalUtils.cpp

        backEnd/gameLogic/inputHandler.h
        backEnd/gameLogic/inputHandler.cpp
        backEnd/gameLogic/game.h
        backEnd/gameLogic/game.cpp
        backEnd/gameLogic/LevelLogic.h
        backEnd/gameLogic/LevelLogic.cpp

        backEnd/types/Command.h
        backEnd/types/Vec2.h
        backEnd/types/Color.h

        frontEnd/Classes/mainInheriteClass.cpp
        frontEnd/Classes/map.h
        frontEnd/Classes/map.cpp
        frontEnd/Classes/MapBlock.h
        frontEnd/Classes/MapBlock.cpp
        frontEnd/Classes/Player.h
        backEnd/types/Vec2.h
        frontEnd/Classes/Weapon.cpp
        frontEnd/Classes/Weapon.h
        frontEnd/Classes/HealingPotion.cpp
        frontEnd/Classes/HealingPotion.h
        frontEnd/Classes/Key.cpp
        frontEnd/Classes/Key.h)
        frontEnd/Classes/Player.cpp

        frontEnd/Classes/Menu/MainMenuDesign.h
        frontEnd/Classes/Menu/MainMenuDesign.cpp

        frontEnd/Classes/Menu/CreditsScreen.h
        frontEnd/Classes/Menu/CreditsScreen.cpp

        frontEnd/Classes/Menu/StoryScreen.h
        frontEnd/Classes/Menu/StoryScreen.cpp

        frontEnd/Classes/Menu/MenuCommands.h
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)