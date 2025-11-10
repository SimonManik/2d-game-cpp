cmake_minimum_required(VERSION 4.0)
project(zoo_zs2025_2026_xjanota3)

set(CMAKE_CXX_STANDARD 14)

include_directories(gameska)
include_directories(gameska/backEnd)

add_executable(zoo_zs2025_2026_xjanota3
        gameska/backEnd/renderEngine.cpp
        gameska/backEnd/renderEngine.h
        gameska/main.cpp
        gameska/README.md)
