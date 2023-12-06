//
// Created by Rob on 8/31/2023.
//

#include "window.h"
#include "../WorldGen.h"
#include "Tiles.h"

window::window(int windowHeight, int windowWidth, HANDLE _handle) {
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    this->consoleHandle = _handle;

    this->isOpen = false;
    this->selectedIndex = 0;
}

void window::ShowWindow(std::vector<std::vector<int>>&mapArr, const std::string& windowName, vector2 playerPosition) {
#pragma region Adjust Window
    vector2 topLeftCorner = playerPosition;
    for (int r = 0; r < windowWidth / 2; r++){
        topLeftCorner = topLeftCorner.right();
    }
    for (int u = 0; u < windowHeight / 2; u++){
        topLeftCorner = topLeftCorner.up();
    }

    // Advanced Adjustments (Keep the Window inside the Terminal Buffer)
    if (topLeftCorner.peekUp(windowHeight / 2) <= 0){
        vector2 newPos = topLeftCorner;
        while (newPos.y <= 0){
            newPos = newPos.down();
        }
        topLeftCorner = newPos;
    }

    if (topLeftCorner.peekDown(windowHeight) >= WorldGen::worldSize.height){
        vector2 newPos = topLeftCorner;
        while (newPos.peekDown(windowHeight) >= WorldGen::worldSize.height){
            newPos = newPos.up();
        }
        topLeftCorner = newPos;
    }

    if (topLeftCorner.peekRight(windowWidth) >= WorldGen::worldSize.width){
        topLeftCorner = vector2(topLeftCorner.x - (windowWidth + (windowWidth / 2)), topLeftCorner.y);
    }

#pragma endregion

#pragma region Get Original Tiles
    for (int y = topLeftCorner.y; y < topLeftCorner.y + this->windowHeight; y++){
        for (int x = topLeftCorner.x; x < topLeftCorner.x + this->windowWidth; x++){
            vector2 pos(x, y);

            Tile defaultTile;
            defaultTile.pos = pos;
            defaultTile.tileNumber = mapArr[x][y];
            this->originalTiles.push_back(defaultTile);
        }
    }
#pragma endregion

    for (int y = topLeftCorner.y; y < topLeftCorner.y + this->windowHeight; y++){
        for (int x = topLeftCorner.x; x < topLeftCorner.x + this->windowWidth; x++){
            COORD coord;
            coord.X = x;
            coord.Y = y;

            SetConsoleCursorPosition(this->consoleHandle, coord);
            SetConsoleTextAttribute(this->consoleHandle, 7);

            std::cout << ' ';
        }
        std::cout << '\n';
    }

    COORD cursor;
    cursor.X = topLeftCorner.x;
    cursor.Y = topLeftCorner.y;

    SetConsoleCursorPosition(this->consoleHandle, cursor);
    SetConsoleTextAttribute(this->consoleHandle, 7);

    std::cout << windowName;

    isOpen = true;
    windowPos = topLeftCorner;
}

void window::HideWindow() {
    for (int i = 0; i < this->originalTiles.size(); i++){
        vector2 vector = this->originalTiles[i].pos;
        int tileValue = this->originalTiles[i].tileNumber;

        TileData* data = Tiles::Map[tileValue];

        COORD cursor = vector.ToCOORD();
        SetConsoleCursorPosition(this->consoleHandle, cursor);
        SetConsoleTextAttribute(this->consoleHandle, data->GetColor());
        std::cout << data->GetChar();
    }

    isOpen = false;
    this->originalTiles.clear();
    this->selectedIndex = 0;
    this->selectedItemMap.clear();
}

vector2 window::getWindowPos() {
    return this->windowPos;
}

void window::RefreshInventoryWindow() {
    COORD cursor = getWindowPos().ToCOORD();
    for (int i = 0; i < inventory::items.size(); i++){
        item* item = inventory::items[i];
        if (item->GetCount() <= 0)
            continue;

        cursor.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors::DefaultWhite);

        std::cout << "(" << i + 1 << ") " << item->GetName() << " (Qty: " << item->GetCount() << ")";
    }
}

void window::SetHeight(int height) {
    this->windowHeight = height;
}

void window::SetWidth(int width) {
    this->windowWidth = width;
}


