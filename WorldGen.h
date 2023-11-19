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

    /* <autodoc>
     GenerateBasicWorld | Function
     Return a randomly generated 2D int array based on the passed fillDensity

     [parameters]
     - int fillDensity
    <autodoc> */
    static std::vector<std::vector<int>> GenerateBasicWorld(int fillDensity);

    /* <autodoc>
     SmoothExistingBasicWorld | Function
     Using the Cellular Automa algorithm, smooth the randomly generated array into more realistic terrain

     [parameters]
     - int** basicMap
     - int smoothness
    <autodoc> */
    static std::vector<std::vector<int>> SmoothExistingBasicWorld(std::vector<std::vector<int>> basicMap, int smoothness);

    /* <autodoc>
     GenerateBeaches | Function
     Modify the WorldMap to include beaches around the bodies of Tile_Water

     [parameters]
     - int** detailedMap
    <autodoc> */
    static std::vector<std::vector<int>> GenerateBeaches(std::vector<std::vector<int>> detailedMap);

    /* <autodoc>
     FindSuitableSpawnPoint | Function
     Randomly search for a suitable spawn location for the player, must not spawn the player that may result in them being placed somewhere unsafe

     [parameters]
     - int** detailedMap
     - int requiredWalls = 2
    <autodoc> */
    static vector2 FindSuitableSpawnPoint(std::vector<std::vector<int>> detailedMap, int requiredWalls = 2);

    /* <autodoc>
     GenerateForestry | Function

     Using a modified WorldGen::GenerateBasicWorld function, generate trees around the map
     [parameters]
     - int** detailedMap
     - int densityForestry
    <autodoc> */
    static std::vector<std::vector<int>> GenerateForestry(std::vector<std::vector<int>> detailedMap, int densityForestry);

    /* <autodoc>
     GenerateBoulders | Function

     Using a modified WorldGen::GenerateBasicWorld function, generate boulders around the map
     [parameters]
     - int** detailedMap
     - int densityRocks
    <autodoc> */
    static std::vector<std::vector<int>> GenerateBoulders(std::vector<std::vector<int>> detailedMap, int densityRocks);

    static rect worldSize;

    /* <autodoc>
     ModifiedTileResult | Function

     When the player interacts with a tile, this function will return whether or not the tile needs to be modified to change the end result

     **DOES NOT DIRECTLY MODIFY WORLD MAP**
     [parameters]
     - int beforeTile
    <autodoc> */
    static int ModifiedTileResult(int beforeTile);

    /* <autodoc>
     GenerateMineshafts | Function

     Using a modified WorldGen::GenerateBasicWorld function, generate mineshafts around the map
     [parameters]
     - int** detailedMap
     - int mineshafts // total amount of mineshafts to spawn on the map
    <autodoc> */
    static std::vector<std::vector<int>> GenerateMineshafts(std::vector<std::vector<int>> detailedMap, int mineshafts);
    static std::vector<std::vector<int>> WorldGenCopy;
private:
    static int GetSurroundingWalls(std::vector<std::vector<int>> map, int xPos, int yPos);
    static int* GetNeighborNumbers(std::vector<std::vector<int>> map, int xPos, int yPos);
    static int GetAmountOfNeighborNumbers(const int *surroundingMap);
};


#endif //CSC1061CAPSTONE_WORLDGEN_H
