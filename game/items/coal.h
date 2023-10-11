//
// Created by Rob on 10/10/2023.
//

#ifndef CSC1061CAPSTONE_COAL_H
#define CSC1061CAPSTONE_COAL_H

#include "../item.h"

class coal : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }
    int GetDropCount() override { return _dropCount; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }


private:
    std::string _name = "Coal";
    int _count = 0;
    itemType _type = itemType::Coal;
    double _dropMultiplier = 1.0;
    int _dropCount = 1;
};

#endif //CSC1061CAPSTONE_COAL_H
