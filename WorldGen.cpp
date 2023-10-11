//
// Created by Rob on 8/28/2023.
//

#include <unordered_map>
#include <vector>
#include "WorldGen.h"
#include "CaveGeneration.h"

rect WorldGen::worldSize;
int** WorldGen::WorldGenCopy;

int **WorldGen::GenerateBasicWorld(int fillDensity) {
    int** map = new int*[WorldGen::worldSize.width];
    for (int x = 0; x < WorldGen::worldSize.width; x++){
        map[x] = new int[WorldGen::worldSize.height];
        for (int y = 0; y < WorldGen::worldSize.height; y++){
            map[x][y] =  rand() % 100 + 1 > fillDensity ? 1 : 0;
        }
    }
    return map;
}

int **WorldGen::SmoothExistingBasicWorld(int **basicMap, int smoothness) {
    for (int i = 0; i < smoothness; i++){
        for (int x = 0; x < WorldGen::worldSize.width; x++){
            for (int y = 0; y < WorldGen::worldSize.height; y++){
                int neighborTiles = GetSurroundingWalls(basicMap, x, y);
                if (neighborTiles > 4)
                    basicMap[x][y] = 1;
                else
                    basicMap[x][y] = 0;

            }
        }
    }

    return basicMap;
}

int WorldGen::GetSurroundingWalls(int **map, int xPos, int yPos) {
    int wallCount = 0;
    for (int x = xPos - 1; x <= xPos + 1; x++){
        for (int y = yPos - 1; y <= yPos + 1; y++){
            if (x >= 0 && x < WorldGen::worldSize.width && y >= 0 && y < WorldGen::worldSize.height){
                if (x != xPos || y != yPos)
                    wallCount += map[x][y];
            }
            else{
                wallCount++;
            }
        }
    }
    return wallCount;
}



int **WorldGen::GenerateBeaches(int **detailedMap) {
    // 0 = water
    // 1 = land

    for (int x = 0; x < WorldGen::worldSize.width; x++){
        for (int y = 0; y < WorldGen::worldSize.height; y++){
            if (detailedMap[x][y] == 0)
                continue;

            int* surroundingNumbersOfCurrentPosition = GetNeighborNumbers(detailedMap, x, y);

            int numOfSurrounding = GetAmountOfNeighborNumbers(surroundingNumbersOfCurrentPosition);
            if (numOfSurrounding < 4){
                if (surroundingNumbersOfCurrentPosition[1] == 0)
                    detailedMap[x][y] = 3;
                else
                    detailedMap[x][y] = 2;
            }
        }
    }

    return detailedMap;
}

// [0] - top
// [1] - right
// [2] - bottom
// [3] - left
int* WorldGen::GetNeighborNumbers(int **map, int xPos, int yPos) {
    int* surroundingNumbers = new int[4];

    if (yPos - 1 >= 0){
        surroundingNumbers[0] = map[xPos][yPos - 1];
    } else{
        surroundingNumbers[0] = 1;
    }

    if (xPos + 1 < worldSize.width){
        surroundingNumbers[1] = map[xPos + 1][yPos];
    } else{
        surroundingNumbers[1] = 1;
    }

    if (yPos + 1 < worldSize.height){
        surroundingNumbers[2] = map[xPos][yPos + 1];
    } else{
        surroundingNumbers[2] = 1;
    }

    if (xPos - 1 >= 0){
        surroundingNumbers[3] = map[xPos - 1][yPos];
    } else{
        surroundingNumbers[3] = 1;
    }

    return surroundingNumbers;
}

int WorldGen::GetAmountOfNeighborNumbers(const int *surroundingMap) {
    int n = 0;
    for (int i = 0; i < 4; i++){
        n = surroundingMap[i] != 0 ? n + 1 : n;
    }
    return n;
}


// Modified Wave Function Collapse
/*0 - water
 * 1 - solid
 * 2 - sand
 * 3 - sand
 * 4 - player
 * 5 - forest
 * 6 - rocks
 * */
int **WorldGen::GenerateForestry(int **detailedMap, int densityForestry) {
    for (int x = 0; x < WorldGen::worldSize.width; x++){
        for (int y = 0; y < WorldGen::worldSize.height; y++){
            if (detailedMap[x][y] != 1)
                continue;

            detailedMap[x][y] = rand() % 100 + 1 > densityForestry ? 5 : 1;
        }
    }

    for (int i = 0; i < 2; i++){
        for (int x = 0; x < WorldGen::worldSize.width; x++){
            for (int y = 0; y < WorldGen::worldSize.height; y++){

                if (detailedMap[x][y] != 1 || detailedMap[x][y] != 5)
                    continue;

                int* neighborTiles = GetNeighborNumbers(detailedMap, x, y);

                int n = 0;
                for (int j = 0; j < 4; j++){
                    n = neighborTiles[j] != 0 || neighborTiles[j] != 2 || neighborTiles[j] != 3 ? n++ : n;
                }

                if (n > 4){
                    detailedMap[x][y] = 5;
                }
                else{
                    detailedMap[x][y] = 1;
                }

            }
        }
    }

    return detailedMap;
}

int **WorldGen::GenerateBoulders(int **detailedMap, int densityRocks) {
    for (int x = 0; x < WorldGen::worldSize.width; x++) {
        for (int y = 0; y < WorldGen::worldSize.height; y++) {
            if (detailedMap[x][y] != 1)
                continue;

            detailedMap[x][y] = rand() % 100 + 1 > densityRocks ? 6 : 1;
        }
    }

    /*for (int i = 0; i < 2; i++){
        for (int x = 0; x < WorldGen::worldSize.width; x++) {
            for (int y = 0; y < worldSize.height; y++) {
                if (detailedMap[x][y] == 1 || detailedMap[x][y] == 6){
                    int* neighboringTiles = GetNeighborNumbers(detailedMap, x, y);
                    int n = 0;
                    for (int j = 0; j < 4; j++){
                        n = neighboringTiles[j] != 0 || neighboringTiles[j] != 2 || neighboringTiles[j] != 3 ? n++ : n;
                    }

                    if (n > 4){
                        detailedMap[x][y] = 6;
                    }
                    else{
                        detailedMap[x][y] = 1;
                    }

                }
            }
        }
    }*/

    return detailedMap;
}



vector2 WorldGen::FindSuitableSpawnPoint(int **detailedMap, int requiredWalls) {
    bool suitableSpawnFound = false;
    vector2 spawn;
    while (!suitableSpawnFound){
        int randX = rand() % worldSize.width + 1;
        int randY = rand() % worldSize.height + 1;

        if (randX <= 0 || randX >= worldSize.width || randY <= 0 || randY >= worldSize.height)
            continue;

        if (detailedMap[randX][randY] == 1 || detailedMap[randX][randY] == 15){
            int getSurroundingTiles = GetSurroundingWalls(detailedMap, randX, randY);
            if (getSurroundingTiles >= requiredWalls){
                spawn.x = randX;
                spawn.y = randY;
                suitableSpawnFound = true;
            }
        }
    }

    return spawn;
}




/*0 - water
 * 1 - solid
 * 2 - sand
 * 3 - sand
 * 4 - player
 * 5 - forest
 * 6 - rocks
 * 7 - dirt
 * 8 - buildingMode
 * 14 - mineshaft
 * 15 - stone
 * 16 - indestructible stone
 * 17 - coal
 * 18 - iron
 * */

int WorldGen::ModifiedTileResult(int beforeTile) {
    switch (beforeTile){
        case 1:
            return 7;
        case 5:
        case 6:
            return 1;
        case 17:
        case 18:
            return 15;
        default:
            return beforeTile;

    }
}

int **WorldGen::GenerateMineshafts(int **detailedMap, int mineshafts) {
    for (int i = 0; i < mineshafts; i++){
        vector2 suitablePositions = FindSuitableSpawnPoint(detailedMap, 2);
        detailedMap[suitablePositions.x][suitablePositions.y] = 14;
        CaveGeneration::AddCave(CaveGeneration::GenerateSingleCave(25, 1, true), suitablePositions);
    }
    return detailedMap;
}
