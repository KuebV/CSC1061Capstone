//
// Created by Rob on 10/3/2023.
//

#ifndef CSC1061CAPSTONE_LOGS_H
#define CSC1061CAPSTONE_LOGS_H

#include "../item.h"

class logs : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }

    bool isCraftable() override { return false; }


private:
    std::string _name = "Logs";
    int _count = 0;
    itemType _type = itemType::Logs;
    double _dropMultiplier = 1.0;
    int _dropCount = 3;
};

#endif //CSC1061CAPSTONE_LOGS_H
