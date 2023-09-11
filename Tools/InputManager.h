//
// Created by Rob on 8/31/2023.
//

#ifndef WORLDGENERATIONTEST_INPUTMANAGER_H
#define WORLDGENERATIONTEST_INPUTMANAGER_H


#include "InputKey.h"

class InputManager {
public:
    static bool GetKey(InputKey key);
    static InputKey GetInput();
    static InputKey IntToInputKey(const int& value);
};


#endif //WORLDGENERATIONTEST_INPUTMANAGER_H
