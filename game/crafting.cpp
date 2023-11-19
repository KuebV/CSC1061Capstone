//
// Created by Rob on 10/10/2023.
//

#include "crafting.h"
#include "ItemManager.h"
#include "inventory.h"

std::vector<item *> crafting::CraftableItems() {
    std::vector<item*> craftableItems;

    std::vector<item*> allItems = ItemManager::ItemList();
    for (int i = 0; i < allItems.size(); i++){
        if (!allItems[i]->isCraftable())
            continue;

        std::map<itemType, int> requiredItems = allItems[i]->GetCraftingRecipe();
        std::map<itemType, int>::iterator it;

        for (it = requiredItems.begin(); it != requiredItems.end(); it++){
            item* getItemFromPlayerInventory = inventory::GetItem(it->first);
            if (getItemFromPlayerInventory->GetType() == itemType::NAI)
                break;

            if (getItemFromPlayerInventory->GetCount() >= it->second){
                craftableItems.push_back(allItems[i]);
                break;
            }
        }
    }

    return craftableItems;
}
