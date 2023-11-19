//
// Created by Rob on 10/30/2023.
//

#ifndef CSC1061CAPSTONE_MAINMENU_H
#define CSC1061CAPSTONE_MAINMENU_H

#include <windows.h>
#include <memory>
#include <map>
#include "../rect.h"
#include <iostream>
#include <vector>

class mainMenu {
public:
    mainMenu(HANDLE _handle, rect windowSize);
    int DrawMainMenu();
    std::string HandleMainMenu(int startMenuPos);

    std::string CreateNewGame(int startingPos);
    void LoadGame(int startingPos);
    void ColorTest(int startingPos);
    void About(int startingPos);

    void ClearBuffer(int startingPos);

private:
    std::unique_ptr<HANDLE> _handle;
    std::unique_ptr<CONSOLE_SCREEN_BUFFER_INFO> _bufferInfo;

    void DrawAtPos(char _c, COORD coord, int textAttribute);
    void DrawAtPos(char _c, int x, int y, int textAttribute);

    int GetStringStartingPosition(std::string str);
    int GetStringStartingPosition(int strLength);

    std::vector<std::string> GetLogoName();
    COORD PosToCOORD(int x, int y);

    void PrintTextInMiddle(int startingPosition, std::string text, int textAttribute);

    rect windowSize;
};


#endif //CSC1061CAPSTONE_MAINMENU_H
