//
// Created by Rob on 11/18/2023.
//

#include "EventManager.h"
#include "../CONSOLE.h"

std::vector<EventTile> EventManager::eventVector;
long int EventManager::globalSteps = 0;

bool EventManager::Step() {
    globalSteps++;

    bool changesMade = false;

    std::unique_ptr<CONSOLE> console = std::make_unique<CONSOLE>(GetStdHandle(STD_OUTPUT_HANDLE));

    for (int i = 0; i < eventVector.size(); i++){
        std::unique_ptr<EventTile> eTile = std::make_unique<EventTile>(eventVector[i]);
        TileData* tileData = eTile->tileData;

        if (eTile->currentSteps >= tileData->GetTimedModification()){

            if (tileData->SwapTimedModification()){ // Swap back to the base tile
                console->DrawAtPos(tileData->GetChar(), eTile->position.ToCOORD(), tileData->GetColor());
                WorldGen::WorldGenCopy[eTile->position.x][eTile->position.y] = tileData->GetValue();
            }
            else{
                console->DrawAtPos(tileData->GetAfterModificationChar(), eTile->position.ToCOORD(), tileData->GetAfterModificationColor());
                WorldGen::WorldGenCopy[eTile->position.x][eTile->position.y] = tileData->GetAfterModificationInteger();
            }

            UnregisterEvent(eTile->position);
            changesMade = true;
        }
        else{
            changesMade = false;
        }

        eventVector[i].currentSteps++;

    }

    COORD coord;
    coord.X = 1;
    coord.Y = 1;

    console->WriteAtPos("              ", coord, 192);
    console->WriteAtPos(std::to_string(globalSteps), coord, 192);

    return changesMade;
}

bool EventManager::RegisterEvent(vector2 position) {
    TileData* getTile = Tiles::Map.at(WorldGen::WorldGenCopy[position.x][position.y]);
    if (getTile->GetTimedModification() == -1)
        return false;

    EventTile eventTile;
    eventTile.position = position;
    eventTile.tileData = getTile;
    eventTile.currentSteps = 0;

    eventVector.push_back(eventTile);

    return true;
}

bool EventManager::UnregisterEvent(vector2 position) {
    for (int i = 0; i < eventVector.size(); i++){
        if (eventVector[i].position.IsEqual(position)){
            eventVector.erase(eventVector.begin() + i);
            return true;
        }
    }

    return false;
}




