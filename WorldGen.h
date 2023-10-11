//
// Created by Rob on 8/28/2023.
//

#ifndef CSC1061CAPSTONE_WORLDGEN_H
#define CSC1061CAPSTONE_WORLDGEN_H


#include <cstdlib>
#include <iostream>
#include "vector2.h"
#include "rect.h"

class WorldGen {
public:
    static int** GenerateBasicWorld(int fillDensity);
    static int** SmoothExistingBasicWorld(int** basicMap, int smoothness);
    static int** GenerateBeaches(int** detailedMap);
    static vector2 FindSuitableSpawnPoint(int** detailedMap, int requiredWalls = 2);
    static int** GenerateForestry(int** detailedMap, int densityForestry);
    static int** GenerateBoulders(int** detailedMap, int densityRocks);
    static rect worldSize;
    static int ModifiedTileResult(int beforeTile);
    static int** GenerateMineshafts(int** detailedMap, int mineshafts);
    static int** WorldGenCopy;
private:
    static int GetSurroundingWalls(int** map, int xPos, int yPos);
    static int* GetNeighborNumbers(int** map, int xPos, int yPos);
    static int GetAmountOfNeighborNumbers(const int *surroundingMap);
};


#endif //CSC1061CAPSTONE_WORLDGEN_H
