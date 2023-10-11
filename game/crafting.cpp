//
// Created by Rob on 10/10/2023.
//

#include "crafting.h"

std::map<itemType, std::vector<itemType>> crafting::recipes =
{
        { itemType::StoneHatchet, std::vector<itemType> {Stones, Stones, Sticks, Sticks, Sticks}},
        { itemType::StonePickaxe, std::vector<itemType> {Stones, Stones, Stones, Stones, Stones, Sticks, Sticks, Sticks, Sticks}}
};