//
// Created by Rob on 8/31/2023.
//

#ifndef WORLDGENERATIONTEST_INVENTORY_H
#define WORLDGENERATIONTEST_INVENTORY_H

#include <vector>
#include "../vector2.h"
#include "player.h"
#include "../Tools/Tile.h"

class inventory {
public:
    vector2 topLeftCornerPosition;
    int windowWidth;
    int windowHeight;
    vector2 currentPlayerPosition;

    void SetCurrentPosition(vector2 pos);
    void SetWindowHeight(int height);
    void SetWindowWidth(int windowWidth);
    void SetTopLeftPosition(vector2 topRightPos);

    std::vector<Tile> GetOriginalTiles(int** worldMap);
};


#endif //WORLDGENERATIONTEST_INVENTORY_H
