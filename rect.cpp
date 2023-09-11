//
// Created by Rob on 9/9/2023.
//

#include "rect.h"
#include <string>

std::string rect::ToString() {
    return "{Width: " + std::to_string(width) + ", Height: " + std::to_string(height) + "}";
}
