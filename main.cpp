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
#include "game/window.h"
#include "Tools/Tiles.h"
#include "Tools/File.h"
#include "game/item.h"
#include "game/inventory.h"
#include "game/items/stick.h"
#include "game/items/stone.h"
#include "game/alertBox.h"
#include "game/item_drop_engine.h"


#define WORLDSIZE 119
#define FILL_DENSITY 65




int main() {

    File logFile("latest.logs");

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

    for (int i = 0; i < 255; i++){ // Debug
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        std::cout << i << '\n';
    }

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

    window inv(10, 20, GetStdHandle(STD_OUTPUT_HANDLE));
    window crafting(10, 15, GetStdHandle(STD_OUTPUT_HANDLE));

    alertBox alert(windowWidth, windowHeight, GetStdHandle(STD_OUTPUT_HANDLE));

    player currPlayer(playerSpawn);
    currPlayer.lastPositionNumber = worldMap[playerSpawn.x][playerSpawn.y];

    /*for (int i = 0; i < 5; i++){
        if ((rand() % 10 + 1) % 2 == 0){
            inventory::AddItem(new stick());
        }
        else{
            inventory::AddItem(new stone());
        }
    }*/

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


    alert.ShowDialogBox(std::vector<std::string>{"Hello!", "This an alert box!", "Press your ESCAPE key to close this box!"}, worldMap, 112);


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

                if (!currPlayer.inventoryOpen && !inv.isOpen){
                    currPlayer.ToggleInventoryMovementBehavior();
                    inv.ShowWindow(worldMap, "Inventory: ", currPlayer.currentPosition);

                    COORD cursor = inv.getWindowPos().ToCOORD();
                    for (int i = 0; i < inventory::items.size(); i++){
                        item* item = inventory::items[i];

                        cursor.Y++;
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors::DefaultWhite);

                        std::cout << "(" << i + 1 << ") " << item->GetName() << " (Qty: " << item->GetCount() << ")";
                    }

                }
                else{
                    currPlayer.ToggleInventoryMovementBehavior();
                    inv.HideWindow();
                }

                break;
            }
            case InputKey::UppercaseX:
            case InputKey::LowercaseX:{
                int tileValue = worldMap[currPlayer.currentPosition.x][currPlayer.currentPosition.y];
                worldMap[currPlayer.currentPosition.x][currPlayer.currentPosition.y] = WorldGen::ModifiedTileResult(tileValue);

                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.CurrentPosition_COORD());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColor(WorldGen::ModifiedTileResult(tileValue)));
                std::cout << TileMap::IntToChar(WorldGen::ModifiedTileResult(tileValue));

                item_drop_engine::handleHarvesting(tileValue);
                break;
            }
            case InputKey::LowercaseF:{
                alert.ShowDialogBox("Hello World!", worldMap, 112);
                break;
            }
            case InputKey::EscapeBtn:{
                alert.HideDialogBox();
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

