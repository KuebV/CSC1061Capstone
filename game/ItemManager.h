//
// Created by Rob on 9/26/2023.
//

#ifndef CSC1061CAPSTONE_ITEMMANAGER_H
#define CSC1061CAPSTONE_ITEMMANAGER_H


#include <string>
#include <vector>
#include "item.h"

class ItemManager {
public:
    static void handleHarvesting(int resourceTile);
    static std::vector<item*> getResource(int resourceTile);
    static std::vector<item*> ItemList();
    static item* GetItem(itemType itemType);

private:
    static void setDropCount(item*& item);

};


#endif //CSC1061CAPSTONE_ITEMMANAGER_H
