//
// Created by Rob on 11/8/2023.
//

#ifndef CSC1061CAPSTONE_NULLITEM_H
#define CSC1061CAPSTONE_NULLITEM_H

#include "../item.h"

class nullItem : public item{
public:
    itemType GetType() override { return _type; }
    std::string GetName() override { return _name;}
    int GetCount() override { return _count; }
    double GetDropMultiplier() override { return _dropMultiplier; }

    void AddItem() override { _count++; }
    void RemoveItem() override { _count--; }


private:
    std::string _name = "NULL";
    int _count = 0;
    itemType _type = itemType::NAI;
    double _dropMultiplier = 1.0;
    int _dropCount = 0;
};

#endif //CSC1061CAPSTONE_NULLITEM_H
