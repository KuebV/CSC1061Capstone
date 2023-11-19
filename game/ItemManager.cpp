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

void ItemManager::handleHarvesting(int resourceTile) {
    std::vector<item*> resources = getResource(resourceTile);
    for (auto & resource : resources)
        inventory::AddItem(resource);
}

/*0 - Tile_Water
 * 1 - solid
 * 2 - sand
 * 3 - sand
 * 4 - player
 * 5 - forest
 * 6 - rocks
 * 7 - dirt
 * 8 - buildingMode
 * 14 - mineshaft
 * 15 - stone
 * 16 - indestructible stone
 * 17 - coal
 * 18 - iron
 * */
std::vector<item *> ItemManager::getResource(int resourceTile) {
    std::vector<item*> itemDrops;

    switch (resourceTile){
        case 1:{
            item* item = new dirt();
            setDropCount(item);
            itemDrops.push_back(item);
            break;
        }
        case 5:{
            item* _stick = new stick();
            item* _log = new logs();

            setDropCount(_stick);
            setDropCount(_log);

            itemDrops.push_back(_stick);
            itemDrops.push_back(_log);
            break;
        }
        case 6:{
            item* _stone = new stone();
            setDropCount(_stone);
            itemDrops.push_back(_stone);
            break;
        }
        case 17:{
            item* _coal = new coal();
            setDropCount(_coal);
            itemDrops.push_back(_coal);
            break;
        }
        case 18:{
            item* _iron = new iron();
            setDropCount(_iron);
            itemDrops.push_back(_iron);
            break;
        }
    }

    return itemDrops;
}

void ItemManager::setDropCount(item *&item) {
    int dropAmount = item->GetDropCount();
    double dropMultiplier = item->GetDropMultiplier();

    double getTotalDrops = floor(dropMultiplier * dropAmount);
    for (int i = 0; i < getTotalDrops; i++)
        item->AddItem();
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
