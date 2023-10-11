//
// Created by Rob on 10/10/2023.
//

#ifndef CSC1061CAPSTONE_CAVEGENERATION_H
#define CSC1061CAPSTONE_CAVEGENERATION_H


#include <vector>
#include "rect.h"
#include "vector2.h"

class CaveGeneration {
public:
    static int GetSurroundingWalls(std::vector<std::vector<int>> caveMap , int xPos, int yPos);
    static rect terminalSize;
    static std::vector<std::vector<std::vector<std::vector<int>>>> Caves;
    static std::vector<std::vector<int>> GenerateSingleCave(int fillDensity, int smoothness, bool generateExit = false);
    static void AddCave(std::vector<std::vector<int>> newCave, vector2 pos);
    static void Init();
    static vector2 GetExit(int** map);
    static std::vector<std::vector<int>> GenerateResources(std::vector<std::vector<int>> caveMap);
    static int CaveSum(std::vector<std::vector<int>> cave);
    static bool CaveEmpty(std::vector<std::vector<int>> cave);

    static int** ToIntArray(std::vector<std::vector<int>> cave);

private:
};


#endif //CSC1061CAPSTONE_CAVEGENERATION_H
