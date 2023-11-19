//
// Created by Rob on 10/16/2023.
//

#include "Tiles.h"
#include "tiles/Tile_Sand.h"
#include "tiles/Tile_Grass.h"
#include "tiles/Tile_Player.h"
#include "tiles/Tile_Forest.h"
#include "tiles/Tile_Boulder.h"
#include "tiles/Tile_Dirt.h"
#include "tiles/Tile_IndestructibleStone.h"
#include "tiles/Tile_Stone.h"
#include "tiles/Tile_Mineshaft.h"
#include "tiles/Tile_BuildMode.h"
#include "tiles/Tile_Water.h"
#include "tiles/Tile_Unknown.h"
#include "tiles/Tile_CoalOre.h"
#include "tiles/Tile_IronOre.h"
#include "tiles/Tile_Planks.h"
#include "tiles/TIle_StoneBrick.h"

std::map<int, TileData*> Tiles::Map = {
        { 0, new Tile_Water() },
        { 1, new Tile_Grass() },
        { 2, new Tile_Sand() },
        { 3, new Tile_BuildMode() },
        { 4, new Tile_Player() },
        { 5, new Tile_Forest() },
        { 6, new Tile_Boulder() },
        { 7, new Tile_Dirt() },
        { 14, new Tile_Mineshaft() },
        { 15, new Tile_Stone() },
        { 16, new Tile_IndustructibleStone() },
        { 17, new Tile_CoalOre() },
        { 18, new Tile_IronOre() },
        { 30, new Tile_Planks() },
        { 31, new Tile_StoneBrick() },
        { 99, new Tile_Unknown() },
};

int Tiles::GetBackground(TileData *backgroundTile, TileData *foregroundTile) {
    switch (backgroundTile->GetType()){
        case StoneBrick:{
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 121;
                case PlayerTile:
                    return 124;
            }
        }
        case BoulderTile:
        case ForestTile:
        case GrassTile:{
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 33;
                case PlayerTile:
                    return 36;
            }
            break;
        }
        case SandTile:
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 227;
                case PlayerTile:
                    return 228;
            }
            break;
        case PlanksTile:
        case MineshaftTile:
        case DirtTile:
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 105;
                case PlayerTile:
                    return 100;
            }
            break;
        case IronTile:
        case CoalTile:
        case StoneTile:
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 129;
                case PlayerTile:
                    return 132;
            }
            break;
        case WaterTile:{
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 185;
                case PlayerTile:
                    return 180;
            }
        }
        case UnknownTile:
            switch (foregroundTile->GetType()){
                case BuildingMode:
                    return 33;
                case PlayerTile:
                    return 36;
            }
    }
}

