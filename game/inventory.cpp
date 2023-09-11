//
// Created by Rob on 8/31/2023.
//

#include "inventory.h"

void inventory::SetCurrentPosition(vector2 pos) {
    this->currentPlayerPosition = pos;
}

void inventory::SetWindowHeight(int height) {
    this->windowHeight = height;
}

void inventory::SetWindowWidth(int windowWidth) {
    this->windowWidth = windowWidth;
}

void inventory::SetTopLeftPosition(vector2 topRightPos) {
    this->topLeftCornerPosition = topRightPos;
}

std::vector<Tile> inventory::GetOriginalTiles(int **worldMap) {
    std::vector<Tile> tileVector;
    for (int y = topLeftCornerPosition.y; y < topLeftCornerPosition.y + this->windowHeight; y++){
        for (int x = topLeftCornerPosition.x; x < topLeftCornerPosition.x + this->windowWidth; x++){
            vector2 pos(x, y);

            Tile defaultTile;
            defaultTile.pos = pos;
            defaultTile.tileNumber = worldMap[x][y];
            tileVector.push_back(defaultTile);
        }
    }

    return tileVector;
}

