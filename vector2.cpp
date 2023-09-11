//
// Created by Rob on 8/30/2023.
//

#include <memory>
#include "vector2.h"
#include <string>

vector2::vector2(int x, int y) {
    this->x = x;
    this->y = y;
}

vector2::vector2() : vector2(0, 0) {}

vector2 vector2::up() const {
    return {x, y - 1};
}

vector2 vector2::down() const {
    return {x, y + 1};
}

vector2 vector2::right() const {
    return {x + 1, y};
}

vector2 vector2::left() const {
    return {x - 1, y};
}

bool vector2::outOfBounds(int worldSize) const {
    if (x < 0 || y < 0 || x >= worldSize || y >= worldSize)
        return true;
    return false;
}

COORD vector2::ToCOORD() {
    return {static_cast<SHORT>(x), static_cast<SHORT>(y)};
}

int vector2::peekUp(int n) {
    return y - n;
}

int vector2::peekDown(int n) {
    return y + n;
}

int vector2::peekRight(int n) {
    return x + n;
}

int vector2::peekLeft(int n) {
    return x - n;
}

std::string vector2::ToString() {
    return "{X: " + std::to_string(x) + ", Y: " + std::to_string(y) + "}";
}

