//
// Created by Rob on 11/8/2023.
//

#ifndef CSC1061CAPSTONE_STONE_PICKAXE_H
#define CSC1061CAPSTONE_STONE_PICKAXE_H

#include "../item.h"

class stone_pickaxe : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }

    bool isCraftable() override { return true; }
    std::map<itemType, int> GetCraftingRecipe() override {
        return {
                { itemType::Stones, 3},
                { itemType::Sticks, 4},
        };
    }


private:
    std::string _name = "Stone Pickaxe";
    int _count = 0;
    itemType _type = itemType::StonePickaxe;
    double _dropMultiplier = 2;
    int _dropCount = 1;
};

#endif //CSC1061CAPSTONE_STONE_PICKAXE_H
