//
// Created by Rob on 10/2/2023.
//

#ifndef CSC1061CAPSTONE_STICK_H
#define CSC1061CAPSTONE_STICK_H

#include "../item.h"

class stick : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }

    bool isCraftable() override { return false; }


private:
    std::string _name = "Stick";
    int _count = 0;
    itemType _type = itemType::Sticks;
    double _dropMultiplier = 1.0;
    int _dropCount = 6;
};

#endif //CSC1061CAPSTONE_STICK_H
