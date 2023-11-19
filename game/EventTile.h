//
// Created by Rob on 11/18/2023.
//

#ifndef CSC1061CAPSTONE_EVENTTILE_H
#define CSC1061CAPSTONE_EVENTTILE_H

#include "../vector2.h"
#include "TileData.h"

class EventTile{
public:
    vector2 position;
    int currentSteps;
    TileData* tileData;
};


#endif //CSC1061CAPSTONE_EVENTTILE_H
