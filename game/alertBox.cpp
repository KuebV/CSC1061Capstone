//
// Created by Rob on 9/26/2023.
//

#include <iostream>
#include <memory>
#include "alertBox.h"
#include "../Tools/TileMap.h"

alertBox::alertBox(int _width, int _height, HANDLE _handle) {
    this->terminalWidth = _width;
    this->terminalHeight = _height;
    this->handle = _handle;
}

void alertBox::ShowDialogBox(const std::string &message, int** worldMap, int textAttribute) {
    HideDialogBox();

    int xCenterPos = terminalWidth / 2;
    int messageLength = message.length();

    int boxWidth = messageLength + 4;
    int boxHeight = 5;

    int topLeftCorner = xCenterPos - (boxWidth / 2);
    int topRightCorner = topLeftCorner + boxWidth;

    int yStartPos = terminalHeight - boxHeight - 2;
    int yEndPos = yStartPos + boxHeight;

    for (int y = yStartPos; y < yEndPos; y++){
        for (int x = topLeftCorner; x < topRightCorner; x++){
            std::unique_ptr<COORD> ptrCoord = std::make_unique<COORD>();
            ptrCoord->X = x;
            ptrCoord->Y = y;

            Tile tile;
            tile.tileNumber = worldMap[x][y];
            tile.pos = vector2{x, y};

            this->originalTiles.push_back(tile);

            if (x == topLeftCorner && y == yStartPos || x == topRightCorner - 1 && y == yEndPos - 1) DrawAtPos('+', *ptrCoord, textAttribute);
            else if (x == topLeftCorner && y == yEndPos - 1 || x == topRightCorner - 1 && y == yStartPos) DrawAtPos('+', *ptrCoord, textAttribute);
            else if (x == topLeftCorner || x == topRightCorner - 1) DrawAtPos('|', *ptrCoord, textAttribute);
            else if (y == yStartPos || y == yEndPos - 1) DrawAtPos('-', *ptrCoord, textAttribute);
            else DrawAtPos(' ', *ptrCoord, textAttribute);
        }
    }

    int yStart = yStartPos + 2;
    int MessageStartX = xCenterPos - (messageLength / 2);

    int x = MessageStartX;
    for (int i = 0; i < message.length(); i++){
        DrawAtPos(message[i], x, yStart, textAttribute);
        x++;
    }

}

void alertBox::ShowDialogBox(std::vector<std::string> messages, int **worldMap, int textAttribute) {
    HideDialogBox();
    int xCenterPos = terminalWidth / 2;
    int longestMessageLength = 0;

    for (int i = 0; i < messages.size(); i++){
        if (messages[i].length() > longestMessageLength)
            longestMessageLength = messages[i].length();
    }

    int boxWidth = longestMessageLength + 4;
    int boxHeight = messages.size() + 4;

    int topLeftCorner = xCenterPos - (boxWidth / 2);
    int topRightCorner = topLeftCorner + boxWidth;

    int yStartPos = terminalHeight - boxHeight - 2;
    int yEndPos = yStartPos + boxHeight;

    for (int y = yStartPos; y < yEndPos; y++){
        for (int x = topLeftCorner; x < topRightCorner; x++){
            std::unique_ptr<COORD> ptrCoord = std::make_unique<COORD>();
            ptrCoord->X = x;
            ptrCoord->Y = y;

            Tile tile;
            tile.tileNumber = worldMap[x][y];
            tile.pos = vector2{x, y};

            this->originalTiles.push_back(tile);

            if (x == topLeftCorner && y == yStartPos || x == topRightCorner - 1 && y == yEndPos - 1) DrawAtPos('+', *ptrCoord, textAttribute);
            else if (x == topLeftCorner && y == yEndPos - 1 || x == topRightCorner - 1 && y == yStartPos) DrawAtPos('+', *ptrCoord, textAttribute);
            else if (x == topLeftCorner || x == topRightCorner - 1) DrawAtPos('|', *ptrCoord, textAttribute);
            else if (y == yStartPos || y == yEndPos - 1) DrawAtPos('-', *ptrCoord, textAttribute);
            else DrawAtPos(' ', *ptrCoord, textAttribute);
        }
    }

    int yStart = yStartPos + 2;
    for (int i = 0; i < messages.size(); i++){
        int MessageStartX = xCenterPos - (messages[i].length() / 2);

        int x = MessageStartX;
        for (int j = 0; j < messages[i].length(); j++){
            DrawAtPos(messages[i][j], x, yStart, textAttribute);
            x++;
        }

        yStart++;
    }


}


void alertBox::DrawAtPos(char _c, COORD coord, int textAttribute) {
    SetConsoleCursorPosition(this->handle, coord);
    SetConsoleTextAttribute(this->handle, textAttribute);
    std::cout << _c;
}

void alertBox::DrawAtPos(char _c, int x, int y, int textAttribute) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(this->handle, coord);
    SetConsoleTextAttribute(this->handle, textAttribute);
    std::cout << _c;
}

void alertBox::HideDialogBox() {
    for (int i = 0; i < originalTiles.size(); i++){
        Tile originalTile = originalTiles[i];
        DrawAtPos(TileMap::IntToChar(originalTile.tileNumber), originalTile.pos.ToCOORD(), TileMap::IntToColor(originalTile.tileNumber));
    }
    originalTiles.clear();
}
