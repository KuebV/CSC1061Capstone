//
// Created by Rob on 10/10/2023.
//

#ifndef CSC1061CAPSTONE_CONSOLE_H
#define CSC1061CAPSTONE_CONSOLE_H

#include <windows.h>
#include "vector2.h"
#include "rect.h"
#include <memory>
#include <map>

class CONSOLE {
public:
    /* <autodoc>
     CONSOLE | Constructor
     [parameters]
     - HANDLE _handle
    <autodoc> */
    CONSOLE(HANDLE _handle);

    /* <autodoc>
     DrawWorldMap | Function

     Re-Draws to the screen based on the passed worldMap parameter
     [parameter]
     - int** worldMap
    <autodoc> */
    void DrawWorldMap(std::vector<std::vector<int>>  worldMap);

    /* <autodoc>
     VectorToCOORD | Function
    [parameter]
     - vector2 vector
    <autodoc> */
    static COORD VectorToCOORD(vector2 vector);

    /* <autodoc>
     PosToCOORD | Function
     [parameter]
     - int x
     - int y
    <autodoc> */
    static COORD PosToCOORD(int x, int y);

    rect GetWindowSize();

    void DrawAtPos(char _c, COORD coord, int textAttribute);
    void DrawAtPos(char _c, int x, int y, int textAttribute);

    void WriteAtPos(std::string _string, COORD coord, int textAttribute);

    void MenuCalibration();

    void SetTextAttribute(int textAttribute);
private:
    std::unique_ptr<HANDLE> _handle;
    std::unique_ptr<CONSOLE_SCREEN_BUFFER_INFO> _bufferInfo;


};


#endif //CSC1061CAPSTONE_CONSOLE_H
