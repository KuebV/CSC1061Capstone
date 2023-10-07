//
// Created by Rob on 8/31/2023.
//

#ifndef CSC1061CAPSTONE_INPUTMANAGER_H
#define CSC1061CAPSTONE_INPUTMANAGER_H


#include "InputKey.h"

class InputManager {
public:
    static bool GetKey(InputKey key);
    static InputKey GetInput();
    static InputKey IntToInputKey(const int& value);
};


#endif //CSC1061CAPSTONE_INPUTMANAGER_H
