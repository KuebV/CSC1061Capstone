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
#include "CaveGeneration.h"
#include "CONSOLE.h"


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
    CaveGeneration::terminalSize = rect;
    CaveGeneration::Init();

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
    logFile.Append("Generated Forests. Generating Boulders...\n");

    worldMap = WorldGen::GenerateBoulders(worldMap, 95);
    logFile.Append("Boulders Generated. Finding Suitable Player Spawn\n");
    worldMap = WorldGen::GenerateMineshafts(worldMap, 2);

    // 120 * 30 = 3600 Tiles per Map
    // 3600 * 3600 = 12,960,000

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
    CONSOLE console(GetStdHandle(STD_OUTPUT_HANDLE));

    WorldGen::WorldGenCopy = worldMap;

    console.DrawWorldMap(worldMap);
    alert.ShowDialogBox(std::vector<std::string>{"Hello!", "This an alert box!", "Press your ESCAPE key to close this box!"}, worldMap, 112);


    // Player Movement & World Controls
    while (true){

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

                if (!currPlayer.inventoryOpen && !inv.isOpen){
                    currPlayer.ToggleInventoryMovementBehavior();
                    inv.ShowWindow(worldMap, "Inventory: ", *currPlayer.currentPosition);

                    COORD cursor = inv.getWindowPos().ToCOORD();
                    for (int i = 0; i < inventory::items.size(); i++){
                        item* item = inventory::items[i];

                        cursor.Y++;
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

                        if (item->GetType() == currPlayer.selectedItem->GetType())
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors::DefaultBlue);
                        else
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
                int tileValue = worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y];
                worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = WorldGen::ModifiedTileResult(tileValue);

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
            case InputKey::LowercaseB:
            case InputKey::UppercaseB:{
                std::unique_ptr<std::string> buildModeToggle = std::make_unique<std::string>();
                *currPlayer.playerFlag = *currPlayer.playerFlag == PlayerFlags::BuildMode ? PlayerFlags::Survival : PlayerFlags::BuildMode;
                *buildModeToggle = *currPlayer.playerFlag == PlayerFlags::BuildMode ? "Enabled" : "Disabled";

                if (*currPlayer.playerFlag == PlayerFlags::Survival){
                    *currPlayer.currentPosition = *currPlayer.lastPositionFlagChange;
                    worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = *currPlayer.lastFlagChangeValue;
                }

                if (*currPlayer.playerFlag == PlayerFlags::BuildMode){
                    *currPlayer.lastPositionFlagChange = *currPlayer.currentPosition;
                    *currPlayer.lastFlagChangeValue = worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y];
                    worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = 4;
                }

                alert.ShowDialogBox(std::vector<std::string>{"Build mode has been " + *buildModeToggle, "Press \'B\' to toggle build mode!"}, worldMap, 112);
                break;
            }
            case InputKey::Row1:
            case InputKey::Row2:
            case InputKey::Row3:
            case InputKey::Row4:
            case InputKey::Row5:
            case InputKey::Row6:
            case InputKey::Row7:
            case InputKey::Row8:
            case InputKey::Row9:{
                if (!currPlayer.inventoryOpen)
                    continue;

                int getIndex = ((int)input - 48) - 1;
                if (getIndex < 0 || getIndex > inventory::items.size())
                    continue;

                item* selectedItem = inventory::items[getIndex];

                alert.ShowDialogBox(std::vector<std::string>{"Selected Item: " + selectedItem->GetName(), "Actions:", "\'E\' to Equip", "\'Q\' to drop"}, worldMap, 112);

                std::unique_ptr<bool> inputLoop = std::make_unique<bool>(true);
                while (*inputLoop){
                    InputKey dialogInput = InputManager::GetInput();
                    switch (dialogInput){
                        case InputKey::EscapeBtn:{
                            alert.HideDialogBox();
                            *inputLoop = false;
                            break;
                        }
                        case InputKey::UppercaseE:
                        case InputKey::LowercaseE:{
                            *currPlayer.selectedItem = *selectedItem;
                            alert.HideDialogBox();
                            currPlayer.ToggleInventoryMovementBehavior();
                            inv.HideWindow();
                            *inputLoop = false;
                            break;
                        }
                        case InputKey::LowercaseQ:{
                            inventory::RemoveItem(selectedItem);
                            inv.RefreshInventoryWindow();
                            break;
                        }
                        default:
                            continue;
                    }
                }


                break;
            }
            case InputKey::UppercaseC:
            case InputKey::LowercaseC:{
                crafting.ShowWindow(worldMap, "Crafting", *currPlayer.currentPosition);
                break;
            }
            case InputKey::UppercaseE:
            case InputKey::LowercaseE:{

                logFile.Append("Player Interacting\n");
                if (*currPlayer.playerFlag == PlayerFlags::BuildMode)
                    break;

                alert.HideDialogBox();

                int currentInteractTile = worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y];

                switch (currentInteractTile){
                    case 14:{

                        if (currPlayer.inCaves){
                            worldMap = WorldGen::WorldGenCopy;
                            console.DrawWorldMap(worldMap);
                            *currPlayer.currentPosition = *currPlayer.currentCave;

                            currPlayer.inCaves = false;
                        }
                        else{
                            if (CaveGeneration::Caves[currPlayer.currentPosition->x][currPlayer.currentPosition->y].empty() || CaveGeneration::Caves.empty()){
                                logFile.Append("Player has entered non-existent cave\n");
                                CaveGeneration::AddCave(CaveGeneration::GenerateSingleCave(45, 1), *currPlayer.currentPosition);
                            }

                            worldMap = CaveGeneration::ToIntArray(CaveGeneration::Caves[currPlayer.currentPosition->x][currPlayer.currentPosition->y]);
                            *currPlayer.currentCave = *currPlayer.currentPosition;

                            console.DrawWorldMap(worldMap);
                            vector2 getExit = CaveGeneration::GetExit(worldMap);
                            *currPlayer.currentPosition = getExit;

                            currPlayer.inCaves = true;

                        }
                        break;
                    }
                }
                break;
            }
        }

        // Prevent Player from entering out of bounds
        if (currPlayer.currentPosition->x < 0 || currPlayer.currentPosition->x >= WorldGen::worldSize.width || currPlayer.currentPosition->y < 0 || currPlayer.currentPosition->y >= WorldGen::worldSize.height){
            *currPlayer.currentPosition = *currPlayer.lastPosition;
            continue;
        }

        // Prevent player from entering water if they are in survival
        if (worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] == 0 && *currPlayer.playerFlag == PlayerFlags::Survival || worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] == 16){
            *currPlayer.currentPosition = *currPlayer.lastPosition;
            continue;
        }

        if (currPlayer.inCaves && currPlayer.currentPosition->x == 0 || currPlayer.currentPosition->x >= WorldGen::worldSize.width - 1 || currPlayer.currentPosition->y == 0 || currPlayer.currentPosition->y >= WorldGen::worldSize.height - 1){
            vector2 newCavePos;

            if (currPlayer.currentPosition->x == 0){ // Create West Cave
                newCavePos = currPlayer.currentCave->left();
                currPlayer.currentPosition->x = WorldGen::worldSize.width - 2;
            }
            else if (currPlayer.currentPosition->x == WorldGen::worldSize.width - 1){ // Create East Cave
                newCavePos = currPlayer.currentCave->right();
                currPlayer.currentPosition->x = 1;
            }
            else if (currPlayer.currentPosition->y == 0){ // Create North Cave
                newCavePos = currPlayer.currentCave->up();
                currPlayer.currentPosition->y = WorldGen::worldSize.height - 2;
            }
            else if (currPlayer.currentPosition->y == WorldGen::worldSize.height - 1){
                newCavePos = currPlayer.currentCave->down();
                currPlayer.currentPosition->y = 2;
            }

            if (CaveGeneration::CaveEmpty(CaveGeneration::Caves[newCavePos.x][newCavePos.y])){
                CaveGeneration::AddCave(CaveGeneration::GenerateSingleCave(35, 2), newCavePos);
            }

            *currPlayer.currentCave = newCavePos;

            int** newCave = CaveGeneration::ToIntArray(CaveGeneration::Caves[newCavePos.x][newCavePos.y]);
            worldMap = newCave;

            console.DrawWorldMap(newCave);

        }

        int lastPos = worldMap[currPlayer.lastPosition->x][currPlayer.lastPosition->y];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.LastPosition_COORD());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColor(lastPos));
        std::cout << TileMap::IntToChar(lastPos);

        int colorMode = *currPlayer.playerFlag == PlayerFlags::Survival ? 4 : 8;
        char charMode = *currPlayer.playerFlag == PlayerFlags::Survival ? 'X' : '+';
        int currentPosInt = worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y];

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.CurrentPosition_COORD());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColorWithBackground(colorMode, currentPosInt));
        std::cout << charMode;

        *currPlayer.lastPosition = *currPlayer.currentPosition;

        switch (currentPosInt){
            case 14:{ // Mineshaft
                alert.ShowDialogBox(std::vector<std::string> {"You have found a Mineshaft!", "Press \'E\' to enter"}, worldMap, 112);
                break;
            }
            default:
                break;

        }

        if (!currPlayer.inCaves){
            WorldGen::WorldGenCopy = worldMap;
        }

    }



}

