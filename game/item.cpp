//
// Created by Rob on 10/2/2023.
//

#include "item.h"

itemType item::GetType() {
    return itemType::NAI;
}

int item::GetCount() {
    return -1;
}

std::string item::GetName() {
    return "Quantum stick";
}

double item::GetDropMultiplier() {
    return 0.0;
}

int item::GetDropCount() {
    return 1;
}

void item::AddItem() {}
void item::RemoveItem() {}

bool item::isCraftable() { return false; }
std::map<itemType, int> item::GetCraftingRecipe() { return {}; }
