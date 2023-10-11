//
// Created by Rob on 10/10/2023.
//

#include "CONSOLE.h"
#include "WorldGen.h"
#include "Tools/TileMap.h"

CONSOLE::CONSOLE(HANDLE _handle) {
    this->stdHandle = _handle;
}

void CONSOLE::DrawWorldMap(int **worldMap) {
    SetConsoleCursorPosition(stdHandle, PosToCOORD(0, 0));
    for (int y = 0; y < WorldGen::worldSize.height; y++){
        for (int x = 0; x < WorldGen::worldSize.width; x++){
            int color = TileMap::IntToColor(worldMap[x][y]);
            char ch = TileMap::IntToChar(worldMap[x][y]);

            SetConsoleTextAttribute(stdHandle, color);
            std::cout << ch;
        }
        SetConsoleTextAttribute(stdHandle, 0);
        std::cout << '\n';
    }
}

COORD CONSOLE::VectorToCOORD(vector2 vector) {
    COORD coord;
    coord.X = vector.x;
    coord.Y = vector.y;
    return coord;
}

COORD CONSOLE::PosToCOORD(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    return coord;
}
