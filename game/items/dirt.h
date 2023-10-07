//
// Created by Rob on 10/3/2023.
//

#ifndef CSC1061CAPSTONE_DIRT_H
#define CSC1061CAPSTONE_DIRT_H

#include "../item.h"

class dirt : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }
    int GetDropCount() override { return _dropCount; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }


private:
    std::string _name = "Dirt";
    int _count = 0;
    itemType _type = itemType::Dirt;
    double _dropMultiplier = 1.0;
    int _dropCount = 2;
};

#endif //CSC1061CAPSTONE_DIRT_H
