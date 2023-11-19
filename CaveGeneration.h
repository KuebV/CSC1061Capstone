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
    /* <autodoc>
    GetSurroundingWalls | Function

     Get the amount of walls that are surrounding a specified set of X and Y position

     [parameters]
     - std::vector<std::vector<int>> caveMap
     - int xPos // X-Coordinate
     - int yPos // Y-Coordinate
     */
    static int GetSurroundingWalls(std::vector<std::vector<int>> caveMap , int xPos, int yPos);

    /* <autodoc>
     terminalSize | Property

     Width and Height of the current terminal window. Exact same as WorldGen::worldSize but with a different name
     <autodoc> */
    static rect terminalSize;

    /* <autodoc>
     Caves | Property

     4D Vector of all the current caves
     <autodoc> */
    static std::vector<std::vector<std::vector<std::vector<int>>>> Caves;

    /* <autodoc>
     GenerateSingleCave | Function

     Generate a 2D Integer Vector of a cave. Includes Resources

     [parameters]
     - int fillDensity // WorldGen recommends 35
     - int smoothness
     - bool generateExit = false // Only changed to true when a mineshaft is being generated
     <autodoc> */
    static std::vector<std::vector<int>> GenerateSingleCave(int fillDensity, int smoothness, bool generateExit = false);

    /* <autodoc>
    AddCave | Function

     Adds the passed 2D Vector parameter to the 4D integer vector:
     ```cpp
     CaveGeneration::Caves
     ```

     [parameters]
     - std::vector<std::vector<int>> newCave
     - vector2 pos
     <autodoc> */
    static void AddCave(std::vector<std::vector<int>> newCave, vector2 pos);

    /* <autodoc>
    Init | Function

    Initializes the Caves Vector
     <autodoc> */
    static void Init();

    /* <autodoc>
     GetExit | Function

     Find a suitable exit for the exit-hatch to spawn.

     Similar to the `WorldGen::FindSuitableSpawnPoint`

     [parameters]
     - int** map
     <autodoc> */
    static vector2 GetExit(std::vector<std::vector<int>> map);

    /* <autodoc>
     Generate Resources | Function

     Generates random resources such as Iron, and Coal

     [parameters]
     - std::vector<std::vector<int>>
     <autodoc> */
    static std::vector<std::vector<int>> GenerateResources(std::vector<std::vector<int>> caveMap);

    /* <autodoc>
     CaveSum | Function

     Gets the cumulative sum of the cave elements.
     Mostly used in conjunction to figure out if the cave has been generated or not

     [parameters]
     - std::vector<std::vector<int>> cave
     <autodoc> */
    static int CaveSum(std::vector<std::vector<int>> cave);

    /* <autodoc>
     CaveEmpty | Function | [DEPRECATED]

     Alternative for CaveSum, returns boolean

     [parameters]
     - std::vector<std::vector<int>> cave
     <autodoc> */
    static bool CaveEmpty(std::vector<std::vector<int>> cave);

    static void Print(const std::string msg);

    static int** ToIntArray(std::vector<std::vector<int>> cave);

    static std::vector<std::vector<int>> OreSeeds(std::vector<std::vector<int>> caveMap, int tileValue, int spaceDensity);

private:
};


#endif //CSC1061CAPSTONE_CAVEGENERATION_H
