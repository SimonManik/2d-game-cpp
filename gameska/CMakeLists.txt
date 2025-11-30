cmake_minimum_required(VERSION 4.0)
project(gameska)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gameska main.cpp
        backEnd/render/renderEngine.h
        backEnd/render/consoleBuffer.cpp
        backEnd/render/consoleBuffer.h
        frontEnd/Classes/mainInheriteClass.cpp
        frontEnd/Classes/map.h
        frontEnd/Classes/map.cpp
        frontEnd/Classes/MapBlock.cpp
        frontEnd/Classes/MapBlock.h
        backEnd/gameLogic/camera.cpp
        backEnd/gameLogic/camera.h
        backEnd/gameLogic/inputHandler.cpp
        backEnd/gameLogic/inputHandler.h
        backEnd/types/Command.h
        backEnd/gameLogic/game.cpp
        backEnd/gameLogic/game.h
        frontEnd/Classes/Player.cpp
        frontEnd/Classes/Player.h
        backEnd/types/Vec2.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
