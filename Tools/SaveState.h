//
// Created by Rob on 10/28/2023.
//

#ifndef CSC1061CAPSTONE_SAVESTATE_H
#define CSC1061CAPSTONE_SAVESTATE_H

#include "../game/item.h"

class SaveState{
public:

    int WindowWidth;
    int WindowHeight;

    int PlayerXPosition;
    int PlayerYPosition;

    std::vector<std::vector<std::vector<std::vector<int>>>> caveState;
    std::vector<std::vector<int>> worldState;

    std::vector<item*> items;

};

#endif //CSC1061CAPSTONE_SAVESTATE_H
