//
// Created by Rob on 9/26/2023.
//

#ifndef CSC1061CAPSTONE_ITEM_DROP_ENGINE_H
#define CSC1061CAPSTONE_ITEM_DROP_ENGINE_H


#include <string>
#include <vector>
#include "item.h"

class item_drop_engine {
public:
    static void handleHarvesting(int resourceTile);
    static std::vector<item*> getResource(int resourceTile);

private:
    static void setDropCount(item*& item);

};


#endif //CSC1061CAPSTONE_ITEM_DROP_ENGINE_H
