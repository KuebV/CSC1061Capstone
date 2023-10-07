//
// Created by Rob on 8/30/2023.
//

#ifndef CSC1061CAPSTONE_PLAYER_H
#define CSC1061CAPSTONE_PLAYER_H


#include "../vector2.h"
#include "window.h"
#include "itemType.h"
#include "item.h"
#include <string>
#include <windows.h>


class player {
public:

    vector2 currentPosition;
    vector2 lastPosition;
    int lastPositionNumber;
    vector2 spawnPoint;

    bool disableMovement;
    bool inventoryOpen;




    player(vector2 spawnpoint);
    void MovePlayer(const std::string& direction);
    COORD CurrentPosition_COORD();
    COORD LastPosition_COORD();
    void ToggleInventoryMovementBehavior();

};


#endif //CSC1061CAPSTONE_PLAYER_H
