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

bool vector2::OutOfBounds(rect windowSize) {
   if (x < 0 || y < 0 || x > windowSize.width || y > windowSize.height)
       return true;
   return false;
}

bool vector2::IsEqual(vector2 otherVector) {
    if (otherVector.x == x && otherVector.y == y)
        return true;
    return false;
}

vector2 vector2::newDirection(std::vector<std::vector<int>> map, int preventTile, bool random) const {
    vector2 directions[] = { up(), down(), left(), right() };

    int index = 0;
    if (!random){
        for (int i = 0; i < 4; i++){
            if (map[directions[i].x][directions[i].y] != preventTile){
                index = i;
                break;
            }
        }
    }
    else
        index = rand() % 3 + 0;


    return directions[index];
}


