//
// Created by Rob on 11/7/2023.
//

#ifndef CSC1061CAPSTONE_TILE_IRONORE_H
#define CSC1061CAPSTONE_TILE_IRONORE_H

#include "../TileData.h"

class Tile_IronOre : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }
    std::map<itemType, int> GetDrops() override {
        return { { itemType::Iron, 1 }};
    }

private:
    char _char = '@';
    int _value = 18;
    int _foregroundColor = 135;

    char _afterChar = '#';
    int _afterValue = 15;
    int _afterForegroundColor = 136;

    TileTypes _type = TileTypes::IronTile;
};

#endif //CSC1061CAPSTONE_TILE_IRONORE_H
