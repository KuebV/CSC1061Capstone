//
// Created by Rob on 10/30/2023.
//

#include <conio.h>
#include "mainMenu.h"
#include "../CONSOLE.h"
#include "InputManager.h"

mainMenu::mainMenu(HANDLE _handle, rect windowSize) {
    this->_handle = std::make_unique<HANDLE>(_handle);
    this->_bufferInfo = std::make_unique<CONSOLE_SCREEN_BUFFER_INFO>();
    this->windowSize = windowSize;
}

void mainMenu::DrawAtPos(char _c, COORD coord, int textAttribute) {
    SetConsoleCursorPosition(*this->_handle, coord);
    SetConsoleTextAttribute(*this->_handle, textAttribute);
    std::cout << _c;
}

void mainMenu::DrawAtPos(char _c, int x, int y, int textAttribute) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(*this->_handle, coord);
    SetConsoleTextAttribute(*this->_handle, textAttribute);
    std::cout << _c;
}

int mainMenu::DrawMainMenu() {
    rect rect = windowSize;

    int yPos = 0;
    int xPos = 0;
    for (int i = 0; i < 2; i++){
        for (int x = 0; x < rect.width; x++){
            DrawAtPos(' ', x, yPos, 112);
        }

        for (int y = 0; y < rect.height - 1; y++){
            DrawAtPos(' ', xPos, y, 112);
        }

        yPos = rect.height - 1;
        xPos = rect.width - 1;
    }

    int xMiddle = rect.width / 2;
    int yMiddle = rect.height / 2;

    int logoYPosition = yMiddle - 10;
    std::vector<std::string> logoData = GetLogoName();
    int messageLength = logoData[0].length();

    int xStartPos = xMiddle - (messageLength / 2);

    yPos = logoYPosition;
    xPos = xStartPos;

    SetConsoleTextAttribute(*this->_handle, 7);

    for (int i = 0; i < logoData.size(); i++){
        COORD coord;
        coord.X = xPos;
        coord.Y = yPos;

        SetConsoleCursorPosition(*this->_handle, coord);

        std::cout << logoData[i];
        yPos++;
    }

    return yPos;
}

std::vector<std::string> mainMenu::GetLogoName() {
    return {
            "  _______                      ",
            " |__   __|                     ",
            "    | |  ___  _ __  _ __  __ _ ",
            "    | | / _ \\| '__|| '__|/ _` |",
            "    | ||  __/| |   | |  | (_| |",
            "    |_| \\___||_|   |_|   \\__,_|",
            "                               ",
            "--------------------------------",
            "Use WASD to navigate this menu ",
            "--------------------------------",
    };
}

COORD mainMenu::PosToCOORD(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    return coord;
}

std::string mainMenu::HandleMainMenu(int startMenuPos) {
    std::map<int, std::string> mainMenuSelections = {
            { startMenuPos + 1, "Start New Game"},
            { startMenuPos + 2, "Load Game"},
            { startMenuPos + 3, "Color Test"},
            { startMenuPos + 4, "About"},
            { startMenuPos + 5, "Exit"}
    };

    std::map<int, std::string>::iterator it;
    for (it = mainMenuSelections.begin(); it != mainMenuSelections.end(); it++){
        int xPos = (windowSize.width / 2) - (it->second.length() / 2);
        SetConsoleCursorPosition(*this->_handle, PosToCOORD(xPos, it->first));
        std::cout << it->second;
    }

    bool selecting = true;
    int minimumIndex = startMenuPos + 1;
    int maximumIndex = startMenuPos + mainMenuSelections.size();

    int selectionPos = minimumIndex;
    int lastSelection = selectionPos;

    int initialSelection = GetStringStartingPosition(mainMenuSelections[selectionPos]);
    SetConsoleTextAttribute(*this->_handle, 112);
    SetConsoleCursorPosition(*this->_handle, PosToCOORD(initialSelection, selectionPos));
    std::cout << mainMenuSelections[selectionPos];

    while (selecting){
        InputKey userInput = InputManager::GetInput();
        switch (userInput){
            case InputKey::UppercaseW:
            case InputKey::LowercaseW:{
                if (selectionPos > minimumIndex)
                    selectionPos--;
                break;
            }
            case InputKey::UppercaseS:
            case InputKey::LowercaseS:{
                if (selectionPos < maximumIndex)
                    selectionPos++;
                break;
            }
            case InputKey::CarriageFeed:
            case InputKey::UppercaseD:
            case InputKey::LowercaseD:{
                int length = mainMenuSelections[selectionPos].length();
                switch (length){
                    case 14:{ // Start Game
                        return "";
                    }
                    case 9:{ // Load Game
                        return "savestate.bin";
                    }
                    case 10:{ // Color Test
                        ColorTest(startMenuPos);
                        break;
                    }
                    case 5:{ // About
                        About(minimumIndex - 1);
                        break;
                    }
                    case 4:{ // Exit
                        exit(0);
                    }
                }
                break;
            }
            case UppercaseA:
            case LowercaseA:{
                ClearBuffer(startMenuPos);

                HandleMainMenu(startMenuPos);
                break;
            }
        }

        if (selectionPos != lastSelection){
            int messageStart = GetStringStartingPosition(mainMenuSelections[lastSelection]);
            SetConsoleTextAttribute(*this->_handle, 7);
            SetConsoleCursorPosition(*this->_handle, PosToCOORD(messageStart, lastSelection));
            std::cout << mainMenuSelections[lastSelection];

            messageStart = GetStringStartingPosition(mainMenuSelections[selectionPos]);
            SetConsoleTextAttribute(*this->_handle, 112);
            SetConsoleCursorPosition(*this->_handle, PosToCOORD(messageStart, selectionPos));
            std::cout << mainMenuSelections[selectionPos];
        }

        lastSelection = selectionPos;



    }
}

int mainMenu::GetStringStartingPosition(std::string str) {
    return (windowSize.width / 2) - (str.length() / 2);
}

int mainMenu::GetStringStartingPosition(int strLength) {
    return (windowSize.width / 2) - (strLength / 2);
}

void mainMenu::About(int startingPos) {
    ClearBuffer(startingPos);

    std::string message = "This application was written by Rob Thompson for CSC 1061 / Computer Science II";
    SetConsoleCursorPosition(*this->_handle, PosToCOORD(GetStringStartingPosition(message), startingPos + 1));
    std::cout << message;
}

void mainMenu::ClearBuffer(int startingPos) {
    SetConsoleTextAttribute(*this->_handle, 7);
    for (int x = 1; x < windowSize.width - 1; x++){
        for (int y = startingPos; y < windowSize.height - 1; y++){
            SetConsoleCursorPosition(*this->_handle, PosToCOORD(x, y));
            std::cout << ' ';
        }
    }


}

void mainMenu::ColorTest(int startingPos) {
    ClearBuffer(startingPos);

    for (int i = 0; i < 255; i++){

        if (i % 16 == 0)
            std::cout << "\n\n";

        if (i % 8 == 0)
            std::cout << "\n";

        SetConsoleTextAttribute(*this->_handle, i);
        std::cout << i << "     ";
    }
}

void mainMenu::PrintTextInMiddle(int startingPosition, std::string text, int textAttribute) {
    int startingX = GetStringStartingPosition(text);
    SetConsoleCursorPosition(*this->_handle, PosToCOORD(startingX, startingPosition));
    SetConsoleTextAttribute(*this->_handle, textAttribute);
    std::cout << text;
}



