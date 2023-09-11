#include <iostream>
#include <random>
#include <conio.h>
#include <windows.h>
#include <unordered_map>
#include <memory>
#include "Tools/Tag.h"
#include "WorldGen.h"
#include "game/player.h"
#include "Tools/InputKey.h"
#include "Tools/InputManager.h"
#include "Tools/TileMap.h"
#include "game/inventory.h"
#include "Tools/Tiles.h"
#include "Tools/File.h"


#define WORLDSIZE 119
#define FILL_DENSITY 65




int main() {

    File logFile("latest.log");

    std::unordered_map<std::string, std::string> worldGenTags = {
            { "worldSeed", "-1"},
            { "worldDensity", "35"}
    };
    std::string worldGenFile = "worldGen.tags";
    if (!Tag::TagFileExists(worldGenFile))
        Tag::CreateTagFile(worldGenFile, worldGenTags);

    worldGenTags = Tag::ReadTagFile(worldGenFile);

    std::cout << "\nWorld Generation Project\n-----------------\n";
    std::cout << "Written by: Robert Thompson\nFor CSC1061\n";
    std::cout << "-----------------\n";

    std::cout << "\nWorld Generation\n-----------------\nYou can change settings in the file \"worldGen.tags\"\n";
    std::cout << "World Seed: " << worldGenTags["worldSeed"] << '\n';
    std::cout << "World Density: " << worldGenTags["worldDensity"] << '\n';

    /*for (int i = 0; i < 255; i++){ // Debug
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        std::cout << i << '\n';
    }*/

    std::cout << "\nPress \"ENTER\" to generate the world\n";
    std::cout << "NOTE: Do not resize the terminal window after generating the world, you may resize it now if you want\n";
    std::cin.ignore();

    logFile.Append("Generating World...\n");


    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

    short windowWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    short windowHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

    COORD newConsoleSize;
    newConsoleSize.X = bufferInfo.dwSize.X - 1;
    newConsoleSize.Y = windowHeight;

    int status = SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newConsoleSize);
    if (status == 0){
        logFile.Append("Changing Screen Buffer Size Failed! Reason: " + std::to_string(GetLastError()) + "\n");
    }

    rect rect;
    rect.height = windowHeight;
    rect.width = windowWidth;

    WorldGen::worldSize = rect;
    logFile.Append("World Size: " + rect.ToString() + "\n");

    system("CLS");

    //WorldGen::worldSeed = std::stoi(worldGenTags["worldSeed"]) == -1 ? time(NULL) : std::stoi(worldGenTags["worldSeed"]);
    srand(std::stoi(worldGenTags["worldSeed"]) == -1 ? time(NULL) : std::stoi(worldGenTags["worldSeed"]));

    int** worldMap = WorldGen::GenerateBasicWorld(std::stoi(worldGenTags["worldDensity"]));
    logFile.Append("Basic World Generated. Smoothing Terrain...\n");

    /*for (int y = 0; y < WorldGen::worldSize; y++){
        for (int x = 0; x < WorldGen::worldSize; x++){
            std::cout << numToChar(worldMap[x][y]);
        }
    }*/

    worldMap = WorldGen::SmoothExistingBasicWorld(worldMap, 5);
    logFile.Append("Smooth Terrain Completed. Generating Beaches...\n");

    worldMap = WorldGen::GenerateBeaches(worldMap);
    logFile.Append("Generated Beaches. Generating Forestry...\n");

    worldMap = WorldGen::GenerateForestry(worldMap, 85);
    logFile.Append("Forestry Generated. Finding Suitable Player Spawn\n");

    vector2 playerSpawn = WorldGen::FindSuitableSpawnPoint(worldMap);
    logFile.Append("Suitable Spawn Found.\n");

    /*for (int y = 0; y < WorldGen::worldSize; y++){
        for (int x = 0; x < WorldGen::worldSize; x++){
            std::cout << worldMap[x][y];
        }
        std::cout << '\n';
    }*/

    logFile.Append("World Generated. Spawning Player...\n");

    inventory inv;

    player currPlayer(playerSpawn);
    currPlayer.lastPositionNumber = worldMap[playerSpawn.x][playerSpawn.y];

    item placeholderItem;
    placeholderItem.count = 10;
    placeholderItem.id = itemType::Sticks;
    placeholderItem.itemName = "Sticks";

    currPlayer.AddItem(placeholderItem);

    logFile.Append("Items in Inventory: " + std::to_string(currPlayer.inventoryList.size()) + "\n");

    for (int y = 0; y < WorldGen::worldSize.height; y++){
        for (int x = 0; x < WorldGen::worldSize.width; x++){

            if (currPlayer.currentPosition.x == x && currPlayer.currentPosition.y == y){
                currPlayer.lastPositionNumber = worldMap[x][y];
                worldMap[x][y] = 4;
            }

            int color = TileMap::IntToColor(worldMap[x][y]);
            char ch = TileMap::IntToChar(worldMap[x][y]);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            std::cout << ch;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        std::cout << '\n';
    }


    // Player Movement & World Controls
    while (true){

        logFile.Append("Current Player Position: " + currPlayer.currentPosition.ToString() + '\n');

        InputKey input = InputManager::GetInput();
        switch (input){
            case InputKey::UppercaseW:
            case InputKey::LowercaseW:
                currPlayer.MovePlayer("UP");
                break;
            case InputKey::UppercaseD:
            case InputKey::LowercaseD:
                currPlayer.MovePlayer("RIGHT");
                break;
            case InputKey::UppercaseS:
            case InputKey::LowercaseS:
                currPlayer.MovePlayer("DOWN");
                break;
            case InputKey::UppercaseA:
            case InputKey::LowercaseA:
                currPlayer.MovePlayer("LEFT");
                break;
            case InputKey::UppercaseI:
            case InputKey::LowercaseI:{ // Inventory

                const int inventoryWidth = 15;
                const int inventoryHeight = 10;

                if (!currPlayer.inventoryOpen){
                    currPlayer.ToggleInventoryMovementBehavior();
                    vector2 topLeftCorner = currPlayer.currentPosition;

#pragma region InventoryAdjustments
                    for (int r = 0; r < 3; r++){
                        topLeftCorner = topLeftCorner.right();
                    }

                    for (int u = 0; u < inventoryHeight / 2; u++){
                        topLeftCorner = topLeftCorner.up();
                    }

                    if (topLeftCorner.peekUp(inventoryHeight / 2) <= 0){
                        vector2 newPos = topLeftCorner;
                        while (newPos.y <= 0){
                            newPos = newPos.down();
                        }
                        topLeftCorner = newPos;
                    }

                    if (topLeftCorner.peekDown(inventoryHeight) >= WorldGen::worldSize.height){
                        vector2 newPos = topLeftCorner;
                        while (newPos.peekDown(inventoryHeight) >= WorldGen::worldSize.height){
                            newPos = newPos.up();
                        }
                        topLeftCorner = newPos;
                    }

                    if (topLeftCorner.peekRight(inventoryWidth) >= WorldGen::worldSize.width){
                        topLeftCorner = vector2(topLeftCorner.x - 13, topLeftCorner.y);
                    }

#pragma endregion InventoryAdjustments

                    inv.SetTopLeftPosition(topLeftCorner);
                    inv.SetCurrentPosition(currPlayer.currentPosition);
                    inv.SetWindowHeight(inventoryHeight);
                    inv.SetWindowWidth(inventoryWidth);

                    for (int y = topLeftCorner.y; y < topLeftCorner.y + inventoryHeight; y++){
                        for (int x = topLeftCorner.x; x < topLeftCorner.x + inventoryWidth; x++){
                            COORD coord;
                            coord.X = x;
                            coord.Y = y;
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                            std::cout << ' ';
                        }
                        std::cout << '\n';
                    }

                    COORD cursor;
                    cursor.X = topLeftCorner.x;
                    cursor.Y = topLeftCorner.y;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    std::cout << "Inventory:";

                    for (auto& item : currPlayer.inventoryList){
                        cursor.Y++;
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors::DefaultWhite);

                        std::cout << item.itemName << " (" << item.count << ")";
                    }

                }
                else{
                    currPlayer.ToggleInventoryMovementBehavior();
                    std::vector<Tile> tileVector = inv.GetOriginalTiles(worldMap);
                    for (int i = 0; i < tileVector.size(); i++){
                        vector2 v = tileVector[i].pos;
                        int tileValue = tileVector[i].tileNumber;

                        COORD cursor = v.ToCOORD();
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColor(tileValue));
                        std::cout << TileMap::IntToChar(tileValue);
                    }
                }

                break;
            }

        }

        if (currPlayer.currentPosition.x < 0 || currPlayer.currentPosition.x >= WorldGen::worldSize.width || currPlayer.currentPosition.y < 0 || currPlayer.currentPosition.y >= WorldGen::worldSize.height){
            currPlayer.currentPosition = currPlayer.lastPosition;
            continue;
        }

        int lastNum = currPlayer.lastPositionNumber;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.LastPosition_COORD());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColor(lastNum));
        std::cout << TileMap::IntToChar(lastNum);

        currPlayer.lastPositionNumber = worldMap[currPlayer.currentPosition.x][currPlayer.currentPosition.y];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.CurrentPosition_COORD());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColor(4));
        std::cout << TileMap::IntToChar(4);

        currPlayer.lastPosition = currPlayer.currentPosition;

    }



}

