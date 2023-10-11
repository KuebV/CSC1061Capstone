//
// Created by Rob on 8/31/2023.
//

#ifndef CSC1061CAPSTONE_WINDOW_H
#define CSC1061CAPSTONE_WINDOW_H

#include <vector>
#include "../vector2.h"
#include "player.h"
#include "../Tools/Tile.h"
#include "../game/inventory.h"
#include <map>
#include <windows.h>


class window {
public:
    window(int windowHeight, int windowWidth, HANDLE handle);

    void ShowWindow(int**& mapArr, const std::string& windowName, vector2 playerPos);
    void HideWindow();
    void RefreshInventoryWindow();

    bool isOpen;
    vector2 getWindowPos();
private:
    std::vector<Tile> originalTiles;
    int windowHeight;
    int windowWidth;
    HANDLE consoleHandle;
    vector2 windowPos;

    int selectedIndex;
    std::map<int, int> selectedItemMap;

};


#endif //CSC1061CAPSTONE_WINDOW_H
