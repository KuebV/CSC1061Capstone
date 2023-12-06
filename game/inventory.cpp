//
// Created by Rob on 9/11/2023.
//

#include <algorithm>
#include "inventory.h"
#include "items/nullItem.h"

std::vector<item*> inventory::items;
item* inventory::equippedItem;

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

    item->AddItem();
    items.push_back(item);
}

void inventory::RemoveItem(item *it) {
    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == it->GetType()){
            items[i]->RemoveItem();
            return;
        }
    }

    auto lessZero = [](item* it) { return it->GetCount() <= 0; };
    if (auto _it = std::find_if(begin(items), end(items), lessZero); _it != end(items)){
        items.erase(_it);
    }

}

void inventory::RemoveItem(item *it, int count) {
    for (int i = 0; i < items.size(); i++){
        if (items[i]->GetType() == it->GetType()){
            for (int j = 0; j < count; j++){
                items[i]->RemoveItem();
            }
        }
    }

    auto lessZero = [](item* it) { return it->GetCount() <= 0; };
    if (auto _it = std::find_if(begin(items), end(items), lessZero); _it != end(items)){
        items.erase(_it);
    }
}


item *inventory::GetItem(itemType itemType) {
    for (int i = 0; i < items.size(); i++)
        if (items[i]->GetType() == itemType)
            return items[i];
    return new nullItem();
}




