//
// Created by Rob on 11/9/2023.
//

#ifndef CSC1061CAPSTONE_TILE_STONEBRICK_H
#define CSC1061CAPSTONE_TILE_STONEBRICK_H

#include "../TileData.h"

class Tile_StoneBrick : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

private:
    char _char = '=';
    int _value = 31;
    int _foregroundColor = 120;

    char _afterChar = '=';
    int _afterValue = 31;
    int _afterForegroundColor = 120;

    TileTypes _type = TileTypes::StoneBrick;
};

#endif //CSC1061CAPSTONE_TILE_STONEBRICK_H
