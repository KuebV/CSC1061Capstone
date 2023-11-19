//
// Created by Rob on 10/10/2023.
//

#include <vector>
#include "CONSOLE.h"
#include "WorldGen.h"
#include "game/TileData.h"
#include "game/Tiles.h"

CONSOLE::CONSOLE(HANDLE _handle) {
    this->_handle = std::make_unique<HANDLE>(_handle);
    this->_bufferInfo = std::make_unique<CONSOLE_SCREEN_BUFFER_INFO>();
}

void CONSOLE::DrawWorldMap(std::vector<std::vector<int>> worldMap) {
    SetConsoleCursorPosition(*this->_handle, PosToCOORD(0, 0));
    for (int y = 0; y < WorldGen::worldSize.height; y++){
        for (int x = 0; x < WorldGen::worldSize.width; x++){
            /*int color = TileMap::IntToColor(worldMap[x][y]);
            char ch = TileMap::IntToChar(worldMap[x][y]);*/

            TileData* tileData = Tiles::Map[worldMap[x][y]];

            SetConsoleTextAttribute(*this->_handle, tileData->GetColor());
            std::cout << tileData->GetChar();
        }
        SetConsoleTextAttribute(*this->_handle, 0);
        std::cout << '\n';
    }
}

COORD CONSOLE::VectorToCOORD(vector2 vector) {
    COORD coord;
    coord.X = vector.x;
    coord.Y = vector.y;
    return coord;
}

COORD CONSOLE::PosToCOORD(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    return coord;
}

rect CONSOLE::GetWindowSize() {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &*this->_bufferInfo);

    short windowWidth = this->_bufferInfo->srWindow.Right - this->_bufferInfo->srWindow.Left + 1;
    short windowHeight = this->_bufferInfo->srWindow.Bottom - this->_bufferInfo->srWindow.Top + 1;

    rect r{};
    r.width = windowWidth;
    r.height = windowHeight;

    return r;
}

void CONSOLE::DrawAtPos(char _c, COORD coord, int textAttribute) {
    SetConsoleCursorPosition(*this->_handle, coord);
    SetConsoleTextAttribute(*this->_handle, textAttribute);
    std::cout << _c;
}

void CONSOLE::DrawAtPos(char _c, int x, int y, int textAttribute) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(*this->_handle, coord);
    SetConsoleTextAttribute(*this->_handle, textAttribute);
    std::cout << _c;
}

void CONSOLE::WriteAtPos(std::string _string, COORD coord, int textAttribute) {
    SetConsoleCursorPosition(*this->_handle, coord);
    SetConsoleTextAttribute(*this->_handle, textAttribute);

    std::cout << _string;
}



void CONSOLE::MenuCalibration() {
    rect initialConsoleSize = GetWindowSize();

    std::vector<std::string> windowSetupDialogue = { "Hello!", "Please set this window to your desired size", "Then press \'ENTER\'"};
    int yStart = (initialConsoleSize.height / 2) - windowSetupDialogue.size();
    for (int i = 0; i < windowSetupDialogue.size(); i++){
        int messageStart = (initialConsoleSize.width / 2) - (windowSetupDialogue[i].length() / 2);

        int x = messageStart;
        for (int j = 0; j < windowSetupDialogue[i].length(); j++){
            DrawAtPos(windowSetupDialogue[i][j], x, yStart, 7);
            x++;
        }

        yStart++;
    }


    std::cin.ignore();
    system("CLS");
}

void CONSOLE::SetTextAttribute(int textAttribute) {
    SetConsoleTextAttribute(*this->_handle, textAttribute);
}
