//
// Created by Rob on 9/26/2023.
//

#include <memory>
#include <cmath>
#include "ItemManager.h"
#include "items/dirt.h"
#include "items/stick.h"
#include "items/logs.h"
#include "items/stone.h"
#include "inventory.h"
#include "items/coal.h"
#include "items/iron.h"
#include "items/stone_hatchet.h"
#include "items/nullItem.h"
#include "items/stone_pickaxe.h"
#include "items/ladder.h"
#include "items/planks.h"
#include "items/stone_brick.h"
#include "items/ironIngot.h"
#include "items/iron_hatchet.h"
#include "items/iron_pickaxe.h"
#include "debugMenu.h"
#include "tiles/TileTypes.h"
#include "Tiles.h"

void ItemManager::handleHarvesting(int resourceTile) {
    std::map<itemType, int>::iterator _it;
    TileData* tileData = Tiles::Map[resourceTile];
    std::map<itemType, int> drops = tileData->GetDrops();

    item* equippedItem = inventory::equippedItem;

    for (_it = drops.begin(); _it != drops.end(); _it++){
        int itemMultiplier = floor(_it->second * equippedItem->GetDropMultiplier());
        for (int i = 0; i < itemMultiplier; i++)
            inventory::AddItem(ItemManager::GetItem(_it->first));
    }

}

std::vector<item *> ItemManager::ItemList() {
    return {
        new coal(),
        new dirt(),
        new iron(),
        new logs(),
        new stick(),
        new stone(),
        new stone_hatchet(),
        new stone_pickaxe(),
        new ladder(),
        new planks(),
        new stone_brick(),
        new ironIngot(),
        new iron_hatchet(),
        new iron_pickaxe(),
    };
}

item *ItemManager::GetItem(itemType itemType) {
    std::unique_ptr<std::vector<item*>> itemList_ptr = std::make_unique<std::vector<item*>>(ItemList());
    for (int i = 0; i < itemList_ptr->size(); i++){
        if (itemList_ptr->at(i)->GetType() == itemType)
            return itemList_ptr->at(i);
    }
    return new nullItem();

}
