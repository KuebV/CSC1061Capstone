//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_MINESHAFT_H
#define CSC1061CAPSTONE_TILE_MINESHAFT_H

#include "../TileData.h"

class Tile_Mineshaft : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

    bool IsHarvestable() override { return harvestable; }

private:
    char _char = 'H';
    int _value = 14;
    int _foregroundColor = 96;

    char _afterChar = 'H';
    int _afterValue = 14;
    int _afterForegroundColor = 96;

    TileTypes _type = TileTypes::MineshaftTile;

    bool harvestable = false;
};

#endif //CSC1061CAPSTONE_TILE_MINESHAFT_H
