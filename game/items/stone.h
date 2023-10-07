//
// Created by Rob on 10/2/2023.
//

#ifndef CSC1061CAPSTONE_STONE_H
#define CSC1061CAPSTONE_STONE_H


#include "../item.h"

class stone : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }
    int GetDropCount() override { return _dropCount; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }

private:
    std::string _name = "Stone";
    int _count = 0;
    itemType _type = itemType::Stones;
    double _dropMultiplier = 1.0;
    int _dropCount = 2;
};


#endif //CSC1061CAPSTONE_STONE_H
