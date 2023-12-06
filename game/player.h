//
// Created by Rob on 8/30/2023.
//

#ifndef CSC1061CAPSTONE_PLAYER_H
#define CSC1061CAPSTONE_PLAYER_H


#include "../vector2.h"
#include "window.h"
#include "items/itemType.h"
#include "item.h"
#include "PlayerFlags.h"
#include <string>
#include <windows.h>
#include <memory>


class player {
public:
    bool disableMovement;
    bool inventoryOpen;
    bool inCaves;
    bool craftingOpen;

    item* selectedItem;

    std::unique_ptr<PlayerFlags> playerFlag = std::make_unique<PlayerFlags>();
    std::unique_ptr<vector2> currentPosition = std::make_unique<vector2>();
    std::unique_ptr<vector2> lastPosition = std::make_unique<vector2>();
    std::unique_ptr<vector2> spawnPoint = std::make_unique<vector2>();

    std::unique_ptr<vector2> lastPositionFlagChange = std::make_unique<vector2>();
    std::unique_ptr<int> lastFlagChangeValue = std::make_unique<int>();

    std::unique_ptr<vector2> currentCave = std::make_unique<vector2>();

    player(vector2 spawnpoint);
    void MovePlayer(const std::string& direction);
    COORD CurrentPosition_COORD();
    COORD LastPosition_COORD();
    void ToggleInventoryMovementBehavior();
    void ToggleCraftingMovementBehavior();

};


#endif //CSC1061CAPSTONE_PLAYER_H
