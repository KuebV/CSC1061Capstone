//
// Created by Rob on 11/18/2023.
//

#ifndef CSC1061CAPSTONE_EVENTMANAGER_H
#define CSC1061CAPSTONE_EVENTMANAGER_H



#include <vector>
#include "TileData.h"
#include "../vector2.h"
#include "../WorldGen.h"
#include "Tiles.h"
#include "EventTile.h"
#include <memory>

class EventManager {
public:
    static bool Step();
    static bool RegisterEvent(vector2 position);
    static bool UnregisterEvent(vector2 position);
private:
    static long int globalSteps;
    static std::vector<EventTile> eventVector;
};


#endif //CSC1061CAPSTONE_EVENTMANAGER_H
