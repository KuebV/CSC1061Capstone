//
// Created by Rob on 8/31/2023.
//

#include "TileMap.h"

char TileMap::IntToChar(const int &i) {
    switch (i){
        case 0:
            return '~';
        case 1:
            return '#';
        case 2:
            return '/';
        case 3:
            return '\\';
        case 4:
            return 'X';
        case 5:
            return '^';
        case 6:
            return '.';
        case 7:
            return '#';
        default:
            return '?';
    }
}

int TileMap::IntToColor(const int &i) {
    switch (i){
        case 0:
            return 9;
        case 1:
            return 34;
        case 2:
        case 3:
            return 6;
        case 4:
            return 4;
        case 5:
            return 32;
        case 6:
            return 40;
        case 7:
            return 102;
        default:
            return 13;
    }
}


