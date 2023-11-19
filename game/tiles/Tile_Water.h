//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_WATER_H
#define CSC1061CAPSTONE_TILE_WATER_H

#include "../TileData.h"

class Tile_Water : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _char;}
    int GetAfterModificationInteger() override { return _value; }
    int GetAfterModificationColor() override { return _foregroundColor; }

    TileTypes GetType() override { return _type; }

private:
    char _char = '~';
    int _value = 0;
    int _foregroundColor = 191;

    char _afterChar = '~';
    int _afterValue = 0;
    int _afterForegroundColor = 191;

    TileTypes _type = TileTypes::WaterTile;
};

#endif //CSC1061CAPSTONE_TILE_WATER_H
