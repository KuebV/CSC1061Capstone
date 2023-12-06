//
// Created by Rob on 10/16/2023.
//

#ifndef CSC1061CAPSTONE_TILE_FOREST_H
#define CSC1061CAPSTONE_TILE_FOREST_H

#include "../TileData.h"

class Tile_Forest : public TileData{
public:
    char GetChar() override { return _char; }
    int GetValue() override { return _value; }
    int GetColor() override { return _foregroundColor; }

    char GetAfterModificationChar() override { return _afterChar;}
    int GetAfterModificationInteger() override { return _afterValue; }
    int GetAfterModificationColor() override { return _afterForegroundColor; }

    TileTypes GetType() override { return _type; }
    std::map<itemType, int> GetDrops() override {
        return { { itemType::Logs, 2 },
                 { itemType::Sticks, 6}};
    }

private:
    char _char = '^';
    int _value = 5;
    int _foregroundColor = 32;

    char _afterChar = '#';
    int _afterValue = 1;
    int _afterForegroundColor = 34;

    TileTypes _type = TileTypes::ForestTile;
};

#endif //CSC1061CAPSTONE_TILE_FOREST_H
