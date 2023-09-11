cmake_minimum_required(VERSION 3.24)
project(CSC1061Capstone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(CSC1061Capstone main.cpp WorldGen.cpp WorldGen.h Tools/Tag.cpp Tools/Tag.h game/player.cpp game/player.h vector2.cpp vector2.h Tools/InputManager.cpp Tools/InputManager.h Tools/InputKey.h game/inventory.cpp game/inventory.h Tools/TileMap.cpp Tools/TileMap.h Tools/Tiles.h Tools/Colors.h Tools/Tile.h game/itemType.h rect.cpp rect.h Tools/File.cpp Tools/File.h WorldGen.cpp)
