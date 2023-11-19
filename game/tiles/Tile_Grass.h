//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_GRASS_H
#define CSC1061CAPSTONE_TILE_GRASS_H

#include "../TileData.h"

class Tile_Grass : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

    bool IsHarvestable() override { return harvestable; }
    int GetTimedModification() override { return timedEvent; }

    bool SwapTimedModification() override { return switchBack; }

private:
    char _char = '#';
    int _value = 1;
    int _foregroundColor = 34;

    char _afterChar = '#';
    int _afterValue = 7;
    int _afterForegroundColor = 102;

    TileTypes _type = TileTypes::GrassTile;

    bool harvestable = true;
    int timedEvent = 55;

    bool switchBack = true;
};

#endif //CSC1061CAPSTONE_TILE_GRASS_H
