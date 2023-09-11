//
// Created by Rob on 8/31/2023.
//

#include <conio.h>
#include "InputManager.h"

bool InputManager::GetKey(InputKey key) {
    int c = getch();
    InputKey getKey = static_cast<InputKey>(c);
    if (getKey == key)
        return true;
    return false;
}

InputKey InputManager::GetInput() {
    int c = getch();
    return static_cast<InputKey>(c);
}

InputKey InputManager::IntToInputKey(const int &value) {
    return static_cast<InputKey>(value);
}
