//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_PLAYER_H
#define CSC1061CAPSTONE_TILE_PLAYER_H

#include "../TileData.h"

class Tile_Player : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }

private:
    char _char = '0';
    int _value = 4;
    int _foregroundColor = 4;

    char _afterChar = '0';
    int _afterValue = 4;
    int _afterForegroundColor = 4;

    TileTypes _type = TileTypes::PlayerTile;
};

#endif //CSC1061CAPSTONE_TILE_PLAYER_H
