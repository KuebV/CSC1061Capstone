//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_STONE_H
#define CSC1061CAPSTONE_TILE_STONE_H

#include "../TileData.h"

class Tile_Stone : public TileData{
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
    int _value = 15;
    int _foregroundColor = 136;

    char _afterChar = '#';
    int _afterValue = 15;
    int _afterForegroundColor = 136;

    TileTypes _type = TileTypes::StoneTile;
};

#endif //CSC1061CAPSTONE_TILE_STONE_H
