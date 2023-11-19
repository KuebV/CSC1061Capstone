//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_SAND_H
#define CSC1061CAPSTONE_TILE_SAND_H

#include "../TileData.h"

class Tile_Sand : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

private:
    char _char = '#';
    int _value = 2;
    int _foregroundColor = 238;

    char _afterChar = '#';
    int _afterValue = 2;
    int _afterForegroundColor = 238;

    TileTypes _type = TileTypes::SandTile;
};

#endif //CSC1061CAPSTONE_TILE_SAND_H
