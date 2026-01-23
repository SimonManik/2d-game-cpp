cmake_minimum_required(VERSION 3.20)
project(gameska)

set(CMAKE_CXX_STANDARD 17)

# 1. Definice spustitelného souboru a seznam VŠECH zdrojových souborů (.cpp)
add_executable(gameska
        main.cpp
        backEnd/gameLogic/Game.cpp
        backEnd/gameLogic/InputHandler.cpp
        backEnd/gameLogic/LevelLogic.cpp
        backEnd/render/Camera.cpp
        backEnd/render/ConsoleBuffer.cpp
        backEnd/render/RenderEngine.cpp
        backEnd/render/TerminalUtils.cpp
        backEnd/render/UIRender.cpp
        frontEnd/Classes/Menu/CreditsScreen.cpp
        frontEnd/Classes/Menu/MainMenuDesign.cpp
        frontEnd/Classes/Menu/PauseMenu.cpp
        frontEnd/Classes/Menu/StoryScreen.cpp
        frontEnd/Classes/Enemy.cpp
        frontEnd/Classes/Player.cpp
        frontEnd/Classes/Map.cpp
        frontEnd/Classes/MapBlock.cpp
        frontEnd/Classes/MainInheriteClass.cpp
)

# knihovna pro zvuk
if(WIN32)
    target_link_libraries(gameska winmm)
endif()