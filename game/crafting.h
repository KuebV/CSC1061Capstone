//
// Created by Rob on 10/10/2023.
//

#ifndef CSC1061CAPSTONE_CRAFTING_H
#define CSC1061CAPSTONE_CRAFTING_H

#include <string>
#include <map>
#include <vector>
#include "item.h"

class crafting {
public:
    static std::map<itemType, std::vector<itemType>> recipes;
};


#endif //CSC1061CAPSTONE_CRAFTING_H
