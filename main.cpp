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
#include "game/window.h"
#include "Tools/File.h"
#include "game/item.h"
#include "game/inventory.h"
#include "game/items/stick.h"
#include "game/items/stone.h"
#include "game/alertBox.h"
#include "game/ItemManager.h"
#include "CaveGeneration.h"
#include "CONSOLE.h"
#include "game/Tiles.h"
#include "game/tiles/Tile_Player.h"
#include "Tools/SaveState.h"
#include "game/mainMenu.h"
#include "game/crafting.h"
#include "game/items/nullItem.h"
#include "game/EventManager.h"
#include "game/debugMenu.h"

#define WORLDSIZE 119
#define FILL_DENSITY 65


std::string getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}

int main() {

    std::unique_ptr<std::string> osName = std::make_unique<std::string>(getOsName());
    if (*osName != "Windows 64-bit" && *osName != "Windows 32-bit"){
        std::cout << "This program is not designed for " << *osName << "!\nPress Enter to Exit\n";
        std::cin.ignore();
        exit(1);
    }

    CONSOLE console(GetStdHandle(STD_OUTPUT_HANDLE));
    console.MenuCalibration();

    mainMenu mainMenu(GetStdHandle(STD_OUTPUT_HANDLE), console.GetWindowSize());
    int startMenuPos = mainMenu.DrawMainMenu();
    std::string result = mainMenu.HandleMainMenu(startMenuPos);

    rect windowSize = console.GetWindowSize();

    File logFile("latest.logs");
    File binFile("savestate.bin");
    logFile.Silence(false);

    std::unordered_map<std::string, std::string> applicationTags = {
            { "worldSeed", "-1"},
            { "debugMode", "false"},
            { "cheatMode", "false"}
    };
    std::string worldGenFile = "application.tags";
    if (!Tag::TagFileExists(worldGenFile))
        Tag::CreateTagFile(worldGenFile, applicationTags);

    applicationTags = Tag::ReadTagFile(worldGenFile);

    /*std::cout << "\nWorld Generation Project\n-----------------\n";
    std::cout << "Written by: Robert Thompson\nFor CSC1061\n";
    std::cout << "-----------------\n";

    std::cout << "\nWorld Generation\n-----------------\nYou can change settings in the file \"worldGen.tags\"\n";
    std::cout << "World Seed: " << applicationTags["worldSeed"] << '\n';
    std::cout << "World Density: " << applicationTags["worldDensity"] << '\n';

    *//*for (int i = 0; i < 255; i++){ // Debug
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        std::cout << i << '\n';
    }*//*

    std::cout << "\nPress \"ENTER\" to generate the world\n";
    std::cout << "NOTE: Do not resize the terminal window after generating the world, you may resize it now if you want\n";
    std::cin.ignore();*/


    logFile.Append("Generating World...\n");

    WorldGen::worldSize = windowSize;
    CaveGeneration::terminalSize = windowSize;
    CaveGeneration::Init();

    logFile.Append("World Size: " + windowSize.ToString() + "\n");

    system("CLS");

    //WorldGen::worldSeed = std::stoi(applicationTags["worldSeed"]) == -1 ? time(NULL) : std::stoi(applicationTags["worldSeed"]);
    srand(std::stoi(applicationTags["worldSeed"]) == -1 ? time(NULL) : std::stoi(applicationTags["worldSeed"]));

    std::vector<std::vector<int>> worldMap;
    vector2 playerSpawn;
    player currPlayer(playerSpawn);

    bool debugMode = Tag::ToBoolean(applicationTags["debugMode"]);
    bool cheatMode = Tag::ToBoolean(applicationTags["cheatMode"]);

    console.SetTextAttribute(112);

    if (result == ""){
        worldMap = WorldGen::GenerateBasicWorld(35);
        logFile.Append("Basic World Generated. Smoothing Terrain...\n");

        logFile.Append("Basic World Generated. Smoothing Terrain...\n");

        worldMap = WorldGen::SmoothExistingBasicWorld(worldMap, 5);
        logFile.Append("Smooth Terrain Completed. Generating Beaches...\n");

        worldMap = WorldGen::GenerateBeaches(worldMap);
        logFile.Append("Generated Beaches. Generating Forestry...\n");

        worldMap = WorldGen::GenerateForestry(worldMap, 70);
        logFile.Append("Generated Forests. Generating Boulders...\n");

        worldMap = WorldGen::GenerateBoulders(worldMap, 95);
        logFile.Append("Boulders Generated. Finding Suitable Player Spawn\n");
        worldMap = WorldGen::GenerateMineshafts(worldMap, 2);

        playerSpawn = WorldGen::FindSuitableSpawnPoint(worldMap);
        logFile.Append("Suitable Spawn Found.\n");
    }
    else{
        std::cout << "Loading Saved State...\n";
        SaveState save = binFile.ReadSaveFile();

        if (save.WindowHeight != console.GetWindowSize().height || save.WindowWidth != console.GetWindowSize().width){
            console.SetTextAttribute(116);
            std::cout << "FATAL ERROR: WINDOW SIZE DOES NOT EQUAL THE CURRENT SAVED GAME\n";
            std::cout << "SAVED WINDOW SIZE: " << std::to_string(save.WindowWidth) << "x" << std::to_string(save.WindowHeight) << "\n";
            std::cout << "CURRENT WINDOW SIZE: " << std::to_string(console.GetWindowSize().width) << "x" << std::to_string(console.GetWindowSize().height) << "\n";

            std::cout << "\nPRESS ANY KEY TO QUIT";
            std::cin.ignore();
            exit(1);
        }

        *currPlayer.currentPosition = {save.PlayerXPosition, save.PlayerYPosition};
        std::cout << "Current Player Loaded\n";

        inventory::items = save.items;
        std::cout << "Inventory Loaded\n";

        worldMap = save.worldState;
        std::cout << "World Loaded\n";

        CaveGeneration::Caves = save.caveState;
        std::cout << "Caves Loaded";

    }


    logFile.Append("World Generated. Spawning Player...\n");
    logFile.Silence(true);
    system("CLS");

    window inv(10, 30, GetStdHandle(STD_OUTPUT_HANDLE));
    window crafting(10, 30, GetStdHandle(STD_OUTPUT_HANDLE));
    alertBox alert(windowSize.width, windowSize.height, GetStdHandle(STD_OUTPUT_HANDLE));

    WorldGen::WorldGenCopy = worldMap;
    currPlayer.selectedItem = new nullItem();

    if (cheatMode){
        std::vector<item*> itemList = ItemManager::ItemList();
        for (int i = 0; i < itemList.size(); i++){
            for (int j = 0; j < 999; j++){
                inventory::AddItem(itemList[i]);
            }
        }
    }

    console.DrawWorldMap(worldMap);
    alert.ShowDialogBox(std::vector<std::string>{"Hello!", "Welcome to Terra", "Press your ESCAPE key to close this box!"}, worldMap, 112);


    debugMenu::Register("handleHarvesting");
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

                if (!currPlayer.inventoryOpen && !inv.isOpen && !currPlayer.craftingOpen){
                    int size = inventory::items.size();

                    inv.SetHeight(size + 2);
                    currPlayer.ToggleInventoryMovementBehavior();
                    inv.ShowWindow(worldMap, "Inventory: ", *currPlayer.currentPosition);

                    COORD cursor = inv.getWindowPos().ToCOORD();
                    for (int i = 0; i < inventory::items.size(); i++){
                        item* item = inventory::items[i];
                        if (item->GetCount() <= 0)
                            continue;


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
                if (!Tiles::Map[tileValue]->IsHarvestable())
                    break;

                EventManager::RegisterEvent(*currPlayer.currentPosition);

                //worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = WorldGen::ModifiedTileResult(tileValue);
                worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = Tiles::Map[tileValue]->GetAfterModificationInteger();

                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.CurrentPosition_COORD());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Tiles::Map[tileValue]->GetAfterModificationColor());
                std::cout << Tiles::Map[tileValue]->GetAfterModificationChar();

                ItemManager::handleHarvesting(tileValue);
                break;
            }
            case InputKey::LowercaseF:{
                alert.ShowDialogBox("Hello World!", worldMap, 112);
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

                // Black magic inputs
                // I guess I wrote this line a few weeks ago now, but it confuses me now?
                // From what i understand, it converts the ASCII value of the input to an integer
                // Then we subtract 48 to get the actual input, then subtract 1 again for the index
                int getIndex = ((int)input - 48) - 1;
                if (getIndex < 0 || getIndex > inventory::items.size())
                    continue;

                if (currPlayer.inventoryOpen && !currPlayer.craftingOpen) {
                    item* selectedItem = inventory::items[getIndex];

                    alert.ShowDialogBox(std::vector<std::string>{"Selected Item: " + selectedItem->GetName(), "Actions:", "\'E\' to Equip", "\'Q\' to drop"}, worldMap, 112);

                    // What??, why didnt I just use a normal boolean here?
                    // Oh no, the horrors, I might loose a couple nano seconds if I don't use a pointer here
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
                                currPlayer.selectedItem = inventory::GetItem(selectedItem->GetType());
                                alert.HideDialogBox();
                                currPlayer.ToggleInventoryMovementBehavior();
                                inv.HideWindow();
                                *inputLoop = false;
                                break;
                            }
                            case InputKey::LowercaseQ:{
                                inventory::RemoveItem(selectedItem);

                                if (selectedItem->GetCount() <= 0){
                                    alert.HideDialogBox();
                                }

                                inv.RefreshInventoryWindow();
                                break;
                            }
                            default:
                                continue;
                        }
                    }
                }

                if (currPlayer.craftingOpen && !currPlayer.inventoryOpen){
                    item* selectedItem = crafting::CraftableItems()[getIndex];
                    alert.ShowDialogBox(std::vector<std::string>{"Selected Item: " + selectedItem->GetName(), "Actions:", "\'F\' to craft one", "\'G\' to craft multiple"}, worldMap, 112);

                    std::unique_ptr<bool> inputLoop = std::make_unique<bool>(true);
                    while (*inputLoop){
                        InputKey dialogInput = InputManager::GetInput();
                        switch (dialogInput){
                            case InputKey::EscapeBtn:{
                                alert.HideDialogBox();
                                *inputLoop = false;
                                break;
                            }
                            case InputKey::UppercaseF:
                            case InputKey::LowercaseF:{

                                std::map<itemType, int>::iterator it;
                                std::map<itemType, int> recipe = selectedItem->GetCraftingRecipe();
                                for (it = recipe.begin(); it != recipe.end(); it++){
                                    inventory::RemoveItem(inventory::GetItem(it->first), it->second);
                                }

                                inventory::AddItem(selectedItem);

                                // Craft One Item
                                //alert.HideDialogBox();
                                currPlayer.ToggleCraftingMovementBehavior();
                                crafting.HideWindow();
                                *inputLoop = false;
                                break;
                            }
                            case InputKey::UppercaseG:
                            case InputKey::LowercaseG:{

                                std::map<itemType, int>::iterator it;
                                std::map<itemType, int> recipe = selectedItem->GetCraftingRecipe();
                                for (it = recipe.begin(); it != recipe.end(); it++){

                                    if (inventory::GetItem(it->first)->GetCount() < it->second){
                                        *inputLoop = false;
                                        crafting.HideWindow();
                                        currPlayer.ToggleCraftingMovementBehavior();
                                        alert.HideDialogBox();
                                        break;
                                    }
                                    inventory::RemoveItem(inventory::GetItem(it->first), it->second);
                                }

                                inventory::AddItem(selectedItem);
                                break;
                            }
                            default:
                                continue;
                        }
                    }
                }




                break;
            } // Inventory
            case InputKey::UppercaseC:
            case InputKey::LowercaseC:{

                if (!currPlayer.inventoryOpen && !inv.isOpen && !currPlayer.craftingOpen){
                    currPlayer.ToggleCraftingMovementBehavior();

                    crafting.SetHeight(crafting::CraftableItems().size() + 2);
                    crafting.ShowWindow(worldMap, "Crafting", *currPlayer.currentPosition);

                    COORD cursor = crafting.getWindowPos().ToCOORD();
                    std::vector<item*> craftableItems = crafting::CraftableItems();
                    for (int i = 0; i < craftableItems.size(); i++){
                        item* item = craftableItems[i];

                        cursor.Y++;
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colors::DefaultWhite);
                        std::cout << "(" << i + 1 << ") " << item->GetName();
                    }

                }

                else if (currPlayer.craftingOpen){
                    currPlayer.ToggleCraftingMovementBehavior();
                    crafting.HideWindow();
                }

                break;
            } // Crafting Menu
            case InputKey::UppercaseE:
            case InputKey::LowercaseE:{

                if (*currPlayer.playerFlag == PlayerFlags::BuildMode){
                    if (currPlayer.currentPosition->IsEqual(*currPlayer.lastPositionFlagChange)){
                        break;
                    }

                    itemType currentItemType = currPlayer.selectedItem->GetType();
                    if (currPlayer.selectedItem->GetCount() <= 0){
                        break;
                    }

                    switch (currentItemType){
                        case itemType::Planks:{
                            inventory::RemoveItem(currPlayer.selectedItem);
                            worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = TileTypes::PlanksTile;
                            break;
                        }
                        case itemType::StoneBricks:{
                            inventory::RemoveItem(currPlayer.selectedItem);
                            worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = TileTypes::StoneBrick;
                            break;
                        }
                        case itemType::Ladder:{
                            inventory::RemoveItem(currPlayer.selectedItem);
                            worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] = TileTypes::MineshaftTile;
                            break;
                        }
                    }
                }

                if (*currPlayer.playerFlag == PlayerFlags::Survival){
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
                                if (CaveGeneration::CaveSum(CaveGeneration::Caves[currPlayer.currentPosition->x][currPlayer.currentPosition->y]) < 10){
                                    logFile.Append("Player has entered non-existent cave\n");
                                    CaveGeneration::AddCave(CaveGeneration::GenerateSingleCave(35, 2, true), *currPlayer.currentPosition);
                                }

                                worldMap =CaveGeneration::Caves[currPlayer.currentPosition->x][currPlayer.currentPosition->y];
                                *currPlayer.currentCave = *currPlayer.currentPosition;

                                console.DrawWorldMap(worldMap);
                                vector2 getExit = CaveGeneration::GetExit(worldMap);
                                *currPlayer.currentPosition = getExit;

                                currPlayer.inCaves = true;

                            }
                            break;
                        }
                    }
                }



                break;
            } // Interaction
            case InputKey::F12:{
                alert.ShowDialogBox(std::vector<std::string> {
                    "Selected Item: " + currPlayer.selectedItem->GetName(),
                    "Item Amount: " + std::to_string(currPlayer.selectedItem->GetCount()),
                    "",
                    "Flag: " + std::to_string((int)*currPlayer.playerFlag),
                    &"Inventory Open: " [ currPlayer.inventoryOpen] ? "True" : "False",
                    &"Crafting Open: " [ currPlayer.craftingOpen] ? "True" : "False",
                }, worldMap, 112);
                break;
            }
            case InputKey::EscapeBtn:{
                if (alert.isActive){
                    alert.HideDialogBox();
                    break;
                }

                if (crafting.isOpen){
                    crafting.HideWindow();
                    currPlayer.ToggleCraftingMovementBehavior();
                    break;
                }

                if (inv.isOpen){
                    inv.HideWindow();
                    currPlayer.ToggleInventoryMovementBehavior();
                    break;
                }


                alert.ShowDialogBoxAlignLeft(std::vector<std::string>
                        {
                            "$PAUSED",
                            "$----------",
                            "1.) Save Game",
                            "2.) Controls",
                            "3.) Help",
                            "4.) Crafting Recipes",
                            "5.) Quit"
                        },
                worldMap, 112);

                bool escape = false;
                while (!escape){
                    InputKey inputKey = InputManager::GetInput();
                    switch (inputKey){
                        case InputKey::EscapeBtn:{
                            escape = true;
                            alert.HideDialogBox();
                            break;
                        }
                        case InputKey::Row1:{
                            if (currPlayer.inCaves){
                                alert.ShowDialogBox("You cannot save in a cave!", worldMap, 112);
                                escape = true;
                                break;
                            }

                            alert.ShowDialogBox(std::vector<std::string>{"Saving Game...", "This process may take a while. Do not quit during this time!"}, worldMap, 112);

                            SaveState saveState;
                            saveState.PlayerXPosition = currPlayer.currentPosition->x;
                            saveState.PlayerYPosition = currPlayer.currentPosition->y;

                            saveState.caveState = CaveGeneration::Caves;
                            saveState.worldState = worldMap;

                            saveState.items = inventory::items;
                            saveState.WindowHeight = console.GetWindowSize().height;
                            saveState.WindowWidth = console.GetWindowSize().width;

                            bool success = binFile.WriteSaveFile(saveState);
                            if (success){
                                alert.ShowDialogBox("Game Successfully Saved!", worldMap, 112);
                            }
                            else{
                                alert.ShowDialogBox("Game was unable to save!", worldMap, 112);
                            }
                            escape = true;


                            break;
                        }
                        case InputKey::Row2:{
                            alert.ShowDialogBoxAlignLeft(std::vector<std::string>
                                {
                                "$GAME CONTROLS",
                                "$-------------------",
                                "$MOVEMENT",
                                "$-------------------",
                                "WASD - Move Player",
                                "\'C\' - Open Crafting Menu",
                                "\'I\' - Open Inventory Menu",
                                "\'B\' - Enter / Exit Build Mode",
                                "\'X\' - Harvest Material",
                                "\'E\' - Interact / Build (if applicable)",
                                "$-------------------",
                                "$Inventory / Crafting",
                                "$-------------------",
                                "Pressing the numbers associated with",
                                "an item will open an action menu"
                                },
                            worldMap, 112);
                            escape = true;
                            break;
                        }
                        case InputKey::Row3:{
                            alert.ShowDialogBoxAlignLeft(std::vector<std::string>
                                {
                                    "$HELP",
                                    "$----------------",
                                    "If you're experiencing bugs, that is to be expected due",
                                    "the scale of this game!",
                                    "",
                                    "In the case that you cannot move, pressing \'C\' or \'I\' twice may help",
                                    "If you trap yourself, press \'F12\' to respawn"

                                },
                            worldMap, 112);
                            escape = true;
                            break;
                        }
                        case InputKey::Row4:{
                            std::vector<std::string> line = { "$CRAFTING RECIPES", "$-----------------------", ""};

                            for (int i = 0; i < ItemManager::ItemList().size(); i++){
                                if (!ItemManager::ItemList()[i]->isCraftable())
                                    continue;

                                std::string text = "";
                                text += ItemManager::ItemList()[i]->GetName() + ": ";

                                std::map<itemType, int> requiredItems = ItemManager::ItemList()[i]->GetCraftingRecipe();
                                std::map<itemType, int>::iterator _it;

                                for (_it = requiredItems.begin(); _it != requiredItems.end(); _it++){
                                    text += ItemManager::GetItem(_it->first)->GetName() + " x" + std::to_string(_it->second) + " ";
                                }

                                line.push_back(text);
                            }

                            alert.ShowDialogBoxAlignLeft(line, worldMap, 112);
                            escape = true;
                            break;
                        }
                    }
                }



            }
        }

        // Prevent Player from entering out of bounds
        if (currPlayer.currentPosition->x < 0 || currPlayer.currentPosition->x >= WorldGen::worldSize.width || currPlayer.currentPosition->y < 0 || currPlayer.currentPosition->y >= WorldGen::worldSize.height){
            *currPlayer.currentPosition = *currPlayer.lastPosition;
            continue;
        }

        // Indestructible and Impassible Tiles
        if (*currPlayer.playerFlag == PlayerFlags::Survival &&
            worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] == TileTypes::WaterTile ||
            worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] == TileTypes::IndestructibleStoneTile ||
            worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y] == TileTypes::StoneBrick
        ){

            *currPlayer.currentPosition = *currPlayer.lastPosition;
            continue;
        }

        if (currPlayer.inCaves){
            if (currPlayer.currentPosition->x == 0 || currPlayer.currentPosition->x >= WorldGen::worldSize.width - 1 || currPlayer.currentPosition->y == 0 || currPlayer.currentPosition->y >= WorldGen::worldSize.height - 1){

                vector2 newCavePos;
                CaveGeneration::Caves[currPlayer.currentCave->x][currPlayer.currentCave->y] = worldMap;

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
                else if (currPlayer.currentPosition->y == WorldGen::worldSize.height - 1){ // Create South Cave
                    newCavePos = currPlayer.currentCave->down();
                    currPlayer.currentPosition->y = 2;
                }

                if (CaveGeneration::CaveEmpty(CaveGeneration::Caves[newCavePos.x][newCavePos.y]) || CaveGeneration::CaveSum(CaveGeneration::Caves[newCavePos.x][newCavePos.y]) < 10){
                    CaveGeneration::AddCave(CaveGeneration::GenerateSingleCave(35, 2), newCavePos);
                }

                *currPlayer.currentCave = newCavePos;

                std::vector<std::vector<int>> newCave = CaveGeneration::Caves[newCavePos.x][newCavePos.y];
                worldMap = newCave;

                console.DrawWorldMap(newCave);

            }
        }


        int lastPos = worldMap[currPlayer.lastPosition->x][currPlayer.lastPosition->y];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.LastPosition_COORD());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Tiles::Map[lastPos]->GetColor());
        std::cout << Tiles::Map[lastPos]->GetChar();

        int colorMode = *currPlayer.playerFlag == PlayerFlags::Survival ? 4 : 3;
        char charMode = *currPlayer.playerFlag == PlayerFlags::Survival ? '0' : '+';
        int currentPosInt = worldMap[currPlayer.currentPosition->x][currPlayer.currentPosition->y];

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currPlayer.CurrentPosition_COORD());
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TileMap::IntToColorWithBackground(colorMode, currentPosInt));

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Tiles::GetBackground(Tiles::Map[currentPosInt], Tiles::Map[colorMode]));
        std::cout << charMode;

        switch (currentPosInt){
            case 14:{ // Mineshaft
                alert.ShowDialogBox(std::vector<std::string> {"You have found a Mineshaft!", "Press \'E\' to enter"}, worldMap, 112);
                break;
            }
            default:
                if (alert.isActive && worldMap[currPlayer.lastPosition->x][currPlayer.lastPosition->y] == TileTypes::MineshaftTile)
                    alert.HideDialogBox();

                break;

        }

        *currPlayer.lastPosition = *currPlayer.currentPosition;

        if (!currPlayer.inCaves){
            bool eventChanged = EventManager::Step();
            WorldGen::WorldGenCopy = worldMap;

            if (eventChanged)
                worldMap = WorldGen::WorldGenCopy;
        }

        if (debugMode)
            debugMenu::DrawMenu();

        inventory::equippedItem = currPlayer.selectedItem;

    }



}

