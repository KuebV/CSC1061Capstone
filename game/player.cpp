//
// Created by Rob on 8/30/2023.
//

#include "player.h"

player::player(vector2 spawnpoint) {
    this->spawnPoint = spawnpoint;
    this->currentPosition = spawnpoint;
    this->lastPosition = spawnpoint;
    this->disableMovement = false;
    this->inventoryOpen = false;
}

void player::MovePlayer(const std::string &direction) {
    if (!this->disableMovement){
        switch (direction[0]){
            case 'N':
            case 'U':
                currentPosition.y = currentPosition.y- 1;
                break;
            case 'R':
            case 'E':
                currentPosition.x = currentPosition.x + 1;
                break;
            case 'D':
            case 'S':
                currentPosition.y = currentPosition.y + 1;
                break;
            case 'L':
            case 'W':
                currentPosition.x = currentPosition.x - 1;
                break;

        }
    }

}

COORD player::CurrentPosition_COORD() {
    COORD cc;
    cc.X = currentPosition.x;
    cc.Y = currentPosition.y;
    return cc;
}

COORD player::LastPosition_COORD() {
    COORD cc;
    cc.X = lastPosition.x;
    cc.Y = lastPosition.y;
    return cc;;
}

void player::ToggleInventoryMovementBehavior() {
    this->inventoryOpen = !this->inventoryOpen;
    this->disableMovement = !this->disableMovement;
}

