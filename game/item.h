//
// Created by Rob on 10/2/2023.
//

#ifndef CSC1061CAPSTONE_ITEM_H
#define CSC1061CAPSTONE_ITEM_H


#include <string>
#include <map>
#include "items/itemType.h"

class item {
public:
    virtual itemType GetType();
    virtual int GetCount();
    virtual std::string GetName();
    virtual double GetDropMultiplier();
    virtual std::map<itemType, int> GetCraftingRecipe();
    virtual bool isCraftable();

    virtual void AddItem();
    virtual void RemoveItem();

};


#endif //CSC1061CAPSTONE_ITEM_H
