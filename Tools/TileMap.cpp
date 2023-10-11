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
            return '*';
        case 7:
        case 8:
            return '#';
        case 9:
            return '+';
        case 14:
            return '#';
        case 15:
        case 16:
            return ' ';
        case 17:
        case 18:{
            return '*';
        }

        default:
            return '?';
    }
}

int TileMap::IntToColor(const int &i) {
    switch (i){
        case 0:
            return 191;
        case 1:
            return 34;
        case 2:
        case 3:
            return 239;
        case 4:
            return 4;
        case 5:
            return 32;
        case 6:
            return 40;
        case 7:
            return 102;
        case 8:
            return 96;
        case 14:
            return 104;
        case 15:
            return 119;
        case 16:
            return 128;
        case 17:
            return 136;
        case 18:
            return 134;
        default:
            return 13;
    }
}

/*0 - water
 * 1 - solid
 * 2 - sand
 * 3 - sand
 * 4 - player
 * 5 - forest
 * 6 - rocks
 * 7 - dirt
 * 8 - buildingMode
 * 14 - mineshaft
 * 15 - stone
 * 16 - indestructible stone
 * 17 - coal
 * 18 - iron
 * */

int TileMap::IntToColorWithBackground(const int &i, const int &backgroundTile) {
    switch (backgroundTile) {
        case 0: {
            switch (i) {
                case 4:
                    return 4;
                case 8:
                    return 9;
            }
        }
        case 2:
        case 3: {
            switch (i) {
                case 4:
                    return 228;
                case 8:
                    return 227;
            }
        }
        case 5:
        case 6:
        case 1: {
            switch (i) {
                case 4:
                    return 36;
                case 8:
                    return 33;
            }
        }
        case 7: {
            switch (i) {
                case 4:
                    return 100;
                case 8:
                    return 105;
            }
        }
        case 14:{
            switch (i) {
                case 4:
                    return 100;
                case 8:
                    return 105;
            }
        }
        case 15:{
            switch (i){
                case 4:
                    return 116;
                case 8:
                    return 115;
            }
        }



    }
}



