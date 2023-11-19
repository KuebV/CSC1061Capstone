//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILES_H
#define CSC1061CAPSTONE_TILES_H

#include <map>
#include "TileData.h"

class Tiles {
public:
    static std::map<int, TileData*> Map;
    static int GetBackground(TileData* backgroundTile, TileData* foregroundTile);
};


#endif //CSC1061CAPSTONE_TILES_H
