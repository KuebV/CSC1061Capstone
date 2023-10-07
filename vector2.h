//
// Created by Rob on 8/30/2023.
//

#ifndef CSC1061CAPSTONE_VECTOR2_H
#define CSC1061CAPSTONE_VECTOR2_H

#include <windows.h>
#include <string>


class vector2 {
public:
    int x;
    int y;

    vector2 up() const;
    vector2 down() const;
    vector2 right() const;
    vector2 left() const;

    int peekUp(int n);
    int peekDown(int n);
    int peekRight(int n);
    int peekLeft(int n);

    COORD ToCOORD();

    bool outOfBounds(int worldSize) const;

    vector2(int x, int y);
    vector2();

    std::string ToString();
};


#endif //CSC1061CAPSTONE_VECTOR2_H
