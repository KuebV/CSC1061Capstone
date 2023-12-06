//
// Created by Rob on 11/7/2023.
//

#ifndef CSC1061CAPSTONE_TILE_COALORE_H
#define CSC1061CAPSTONE_TILE_COALORE_H

#include "../TileData.h"

class Tile_CoalOre : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }
    std::map<itemType, int> GetDrops() override {
        return { { itemType::Coal, 1 }};
    }

private:
    char _char = '@';
    int _value = 17;
    int _foregroundColor = 128;

    char _afterChar = '#';
    int _afterValue = 15;
    int _afterForegroundColor = 136;

    TileTypes _type = TileTypes::CoalTile;
};


#endif //CSC1061CAPSTONE_TILE_COALORE_H
