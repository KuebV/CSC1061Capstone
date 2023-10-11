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

void inventory::RemoveItem(item *item) {
    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == item->GetType()){
            items[i]->RemoveItem();
            return;
        }
    }
}

void inventory::RemoveAllItems(item *item) {
    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == item->GetType()){
            items[i]->RemoveItem();
            return;
        }
    }

    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == item->GetType()){
            items.erase(items.begin() + i);
            break;
        }
    }


}


