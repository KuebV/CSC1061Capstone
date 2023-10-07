//
// Created by Rob on 9/11/2023.
//

#include <algorithm>
#include "inventory.h"

std::vector<item*> inventory::items;

bool inventory::ExistsInInventory(item item) {
    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == item.GetType())
            return true;
    }
    return false;
}

void inventory::AddItem(item* item) {
    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == item->GetType()){
            items[i]->AddItem();
            return;
        }
    }
    items.push_back(item);
}


