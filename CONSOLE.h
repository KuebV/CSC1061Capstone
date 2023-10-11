//
// Created by Rob on 10/10/2023.
//

#ifndef CSC1061CAPSTONE_CONSOLE_H
#define CSC1061CAPSTONE_CONSOLE_H

#include <windows.h>
#include "vector2.h"

class CONSOLE {
public:
    CONSOLE(HANDLE _handle);
    void DrawWorldMap(int** worldMap);
    static COORD VectorToCOORD(vector2 vector);
    static COORD PosToCOORD(int x, int y);
private:
    HANDLE stdHandle;
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
};


#endif //CSC1061CAPSTONE_CONSOLE_H
