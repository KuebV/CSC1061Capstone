//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_BOULDER_H
#define CSC1061CAPSTONE_TILE_BOULDER_H

#include "../TileData.h"

class Tile_Boulder : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

private:
    char _char = '*';
    int _value = 6;
    int _foregroundColor = 40;

    char _afterChar = '#';
    int _afterValue = 1;
    int _afterForegroundColor = 34;

    TileTypes _type = TileTypes::BoulderTile;
};

#endif //CSC1061CAPSTONE_TILE_BOULDER_H
