//
// Created by Rob on 11/8/2023.
//

#ifndef CSC1061CAPSTONE_TILE_PLANKS_H
#define CSC1061CAPSTONE_TILE_PLANKS_H

#include "../TileData.h"

class Tile_Planks : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

private:
    char _char = ':';
    int _value = 30;
    int _foregroundColor = 104;

    char _afterChar = ':';
    int _afterValue = 30;
    int _afterForegroundColor = 104;

    TileTypes _type = TileTypes::PlanksTile;
};

#endif //CSC1061CAPSTONE_TILE_PLANKS_H
