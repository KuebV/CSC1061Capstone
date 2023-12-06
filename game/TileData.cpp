//
// Created by Rob on 10/16/2023.
//

#include "TileData.h"

char TileData::GetChar() {
    return '?';
}

int TileData::GetValue() {
    return -1;
}

int TileData::GetColor() {
    return 0;
}

char TileData::GetAfterModificationChar() {
    return '?';
}

int TileData::GetAfterModificationInteger() {
    return -1;
}

int TileData::GetAfterModificationColor() {
    return 0;
}

TileTypes TileData::GetType() {
    return UnknownTile;
}

int TileData::GetTimedModification() {
    return -1;
}

bool TileData::IsHarvestable() {
    return true;
}

bool TileData::SwapTimedModification() {
    return false;
}

std::map<itemType, int> TileData::GetDrops() {
    return std::map<itemType, int> { { itemType::NAI, -1 }};
}



