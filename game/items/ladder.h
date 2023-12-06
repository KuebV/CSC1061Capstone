//
// Created by Rob on 11/8/2023.
//

#ifndef CSC1061CAPSTONE_LADDER_H
#define CSC1061CAPSTONE_LADDER_H

#include "../item.h"

class ladder : public item{
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
                { itemType::Sticks, 50},
                { itemType::Logs, 25},
        };
    }


private:
    std::string _name = "Ladder";
    int _count = 0;
    itemType _type = itemType::Ladder;
    double _dropMultiplier = 1.0;
    int _dropCount = 3;
};

#endif //CSC1061CAPSTONE_LADDER_H
