//
// Created by Rob on 10/10/2023.
//

#include <memory>
#include <iostream>
#include "CaveGeneration.h"
#include "WorldGen.h"
#include "Tools/File.h"

rect CaveGeneration::terminalSize;
std::vector<std::vector<std::vector<std::vector<int>>>> CaveGeneration::Caves;

int CaveGeneration::GetSurroundingWalls(std::vector<std::vector<int>> map, int xPos, int yPos) {
    int wallCount = 0;
    for (int x = xPos - 1; x <= xPos + 1; x++){
        for (int y = yPos - 1; y <= yPos + 1; y++){
            if (x >= 0 && x < CaveGeneration::terminalSize.width && y >= 0 && y < CaveGeneration::terminalSize.height){
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

std::vector<std::vector<int>> CaveGeneration::GenerateSingleCave(int fillDensity, int smoothness, bool generateExit) {
    std::vector<std::vector<int>> singleCave(terminalSize.width, std::vector<int>(terminalSize.height, 0));

    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){
            singleCave[x][y] = rand() % 100 + 1 > fillDensity ? 1 : 0;
        }
    }

    for (int i = 0; i < smoothness; i++) {
        for (int x = 0; x < terminalSize.width; x++) {
            for (int y = 0; y < terminalSize.height; y++) {
                int neighborTiles = GetSurroundingWalls(singleCave, x, y);
                if (neighborTiles > 4)
                    singleCave[x][y] = 1;
                else
                    singleCave[x][y] = 0;
            }
        }
    }

    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){
            singleCave[x][y] = singleCave[x][y] == 0 ? 16 : 15;
        }
    }

    if (generateExit){
        vector2 exit = WorldGen::FindSuitableSpawnPoint(singleCave);
        singleCave[exit.x][exit.y] = 14;
    }

    singleCave = OreSeeds(singleCave, 17, 2);
    singleCave = OreSeeds(singleCave, 18, 2);

    return singleCave;


}

void CaveGeneration::AddCave(std::vector<std::vector<int>> newCave, vector2 pos) {
    Caves[pos.x][pos.y] = newCave;
}

int **CaveGeneration::ToIntArray(std::vector<std::vector<int>> cave) {
    int** map = new int*[CaveGeneration::terminalSize.width];
    for (int x = 0; x < CaveGeneration::terminalSize.width; x++){
        map[x] = new int[CaveGeneration::terminalSize.height];
        for (int y = 0; y < CaveGeneration::terminalSize.height; y++){
            map[x][y] = cave[x][y];
        }
    }
    return map;
}

void CaveGeneration::Init() {
    Caves = std::vector<std::vector<std::vector<std::vector<int>>>>(CaveGeneration::terminalSize.width, std::vector<std::vector<std::vector<int>>>(CaveGeneration::terminalSize.height, std::vector<std::vector<int>>(CaveGeneration::terminalSize.width, std::vector<int>(CaveGeneration::terminalSize.height))));
}

vector2 CaveGeneration::GetExit(std::vector<std::vector<int>> map) {
    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){
            if (map[x][y] == 14){
                return {x, y};
            }
        }
    }

    return {0, 0};
}

std::vector<std::vector<int>> CaveGeneration::GenerateResources(std::vector<std::vector<int>> caveMap) {
    int coalFillDensity = 20;
    int ironFillDensity = 10;
    int oreDensity = 10;

    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){

            if (caveMap[x][y] != 15)
                continue;

            int randomizedOreDensity = rand() % 100 + 1;
            if (randomizedOreDensity < oreDensity){
                continue;
            }

            int oreType = rand() % 100 + 1;
            if (oreType < ironFillDensity){
                caveMap[x][y] = 18;
            }
            else if (oreType < coalFillDensity){
                caveMap[x][y] = 17;
            }

        }
    }

    return caveMap;
}

int CaveGeneration::CaveSum(std::vector<std::vector<int>> cave) {
    std::unique_ptr<int> sum = std::make_unique<int>();
    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){
            *sum += cave[x][y];
        }
    }
    return *sum;
}

bool CaveGeneration::CaveEmpty(std::vector<std::vector<int>> cave) {
    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){
            if (cave[x][y] != 16)
                return false;
        }
    }
    return true;
}

void CaveGeneration::Print(const std::string msg) {
    std::unique_ptr<File> logFile = std::make_unique<File>("caves.logs");
    logFile->Append(msg);
}

std::vector<std::vector<int>>
CaveGeneration::OreSeeds(std::vector<std::vector<int>> caveMap, int tileValue, int spaceDensity) {
    for (int x = 0; x < terminalSize.width; x++){
        for (int y = 0; y < terminalSize.height; y++){
            if (rand() % 100 + 1 < spaceDensity && caveMap[x][y] == 15){
                caveMap[x][y] = tileValue;
            }
        }
    }

    return caveMap;
}



