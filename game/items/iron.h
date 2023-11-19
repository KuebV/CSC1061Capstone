//
// Created by Rob on 10/10/2023.
//

#ifndef CSC1061CAPSTONE_IRON_H
#define CSC1061CAPSTONE_IRON_H

#include "../item.h"

class iron : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }
    int GetDropCount() override { return _dropCount; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }

    bool isCraftable() override { return false; }


private:
    std::string _name = "Iron";
    int _count = 0;
    itemType _type = itemType::Iron;
    double _dropMultiplier = 1.0;
    int _dropCount = 1;
};

#endif //CSC1061CAPSTONE_IRON_H
