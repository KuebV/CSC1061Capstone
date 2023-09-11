//
// Created by Rob on 8/30/2023.
//

#ifndef WORLDGENERATIONTEST_PLAYER_H
#define WORLDGENERATIONTEST_PLAYER_H


#include "../vector2.h"
#include "inventory.h"
#include "itemType.h"
#include <string>
#include <windows.h>

struct item{
    int count;
    itemType id;
    std::string itemName;
};

class player {
public:

    vector2 currentPosition;
    vector2 lastPosition;
    int lastPositionNumber;
    vector2 spawnPoint;

    bool disableMovement;
    bool inventoryOpen;

    std::vector<item> inventoryList;


    player(vector2 spawnpoint);
    void MovePlayer(const std::string& direction);
    COORD CurrentPosition_COORD();
    COORD LastPosition_COORD();
    void ToggleInventoryMovementBehavior();

    bool AddItem(item item);
    bool ExistsInInventory(item item);
    bool ModifyInventory(item oldItem, item newItem);

};


#endif //WORLDGENERATIONTEST_PLAYER_H
