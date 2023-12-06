//
// Created by Rob on 12/5/2023.
//

#ifndef CSC1061CAPSTONE_IRON_PICKAXE_H
#define CSC1061CAPSTONE_IRON_PICKAXE_H

#include "../item.h"

class iron_pickaxe : public item{
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
                { itemType::IronIngot, 3},
                { itemType::Sticks, 8},
        };
    }


private:
    std::string _name = "Iron Pickaxe";
    int _count = 0;
    itemType _type = itemType::IronPickaxe;
    double _dropMultiplier = 3;
    int _dropCount = 1;
};

#endif //CSC1061CAPSTONE_IRON_PICKAXE_H
