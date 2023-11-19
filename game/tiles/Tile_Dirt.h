//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_DIRT_H
#define CSC1061CAPSTONE_TILE_DIRT_H

#include "../TileData.h"

class Tile_Dirt : public TileData{
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
    char _char = '#';
    int _value = 7;
    int _foregroundColor = 102;

    char _afterChar = '#';
    int _afterValue = 1;
    int _afterForegroundColor = 34;

    TileTypes _type = TileTypes::DirtTile;

    bool harvestable = false;
};

#endif //CSC1061CAPSTONE_TILE_DIRT_H
