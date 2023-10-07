//
// Created by Rob on 9/26/2023.
//

#ifndef CSC1061CAPSTONE_ALERTBOX_H
#define CSC1061CAPSTONE_ALERTBOX_H

#include <string>
#include <windows.h>
#include <vector>
#include "../Tools/Tile.h"


class alertBox {
public:
    alertBox(int _width, int _height, HANDLE _handle);
    void ShowDialogBox(const std::string& message, int** worldMap, int textAttribute);
    void ShowDialogBox(std::vector<std::string> messages, int** worldMap, int textAttribute);
    void HideDialogBox();
private:
    std::vector<Tile> originalTiles;
    HANDLE handle;

    int terminalHeight;
    int terminalWidth;

    void DrawAtPos(char _c, COORD coord, int textAttribute);
    void DrawAtPos(char _c, int x, int y, int textAttribute);
};


#endif //CSC1061CAPSTONE_ALERTBOX_H
