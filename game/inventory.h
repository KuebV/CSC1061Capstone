//
// Created by Rob on 9/11/2023.
//

#ifndef CSC1061CAPSTONE_INVENTORY_H
#define CSC1061CAPSTONE_INVENTORY_H


#include <vector>
#include "item.h"

class inventory {
public:
    static std::vector<item*> items;

    static void AddItem(item* item);
    static void RemoveItem(item* item);
    static void RemoveAllItems(item* item);
    static bool ExistsInInventory(item item);
};


#endif //CSC1061CAPSTONE_INVENTORY_H
