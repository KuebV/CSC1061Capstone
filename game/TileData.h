//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILEDATA_H
#define CSC1061CAPSTONE_TILEDATA_H


#include <string>
#include "../Tools/Colors.h"
#include "tiles/TileTypes.h"
#include "items/itemType.h"
#include <map>

class TileData {
public:
    virtual char GetChar();
    virtual int GetValue();
    virtual int GetColor();
    virtual char GetAfterModificationChar();
    virtual int GetAfterModificationInteger();
    virtual int GetAfterModificationColor();
    virtual TileTypes GetType();
    virtual int GetTimedModification();
    virtual bool IsHarvestable();
    virtual bool SwapTimedModification();

    virtual std::map<itemType, int> GetDrops();
};



#endif //CSC1061CAPSTONE_TILEDATA_H
