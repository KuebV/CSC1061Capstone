# CaveGeneration.h

## GetSurroundingWalls | Function

### Description:
Get the amount of walls that are surrounding a specified set of X and Y position


### Implementation:
```    static rect terminalSize;```

### Parameters:
- std::vector\<std::vector\<int\>\> caveMap
- int xPos // X-Coordinate
- int yPos // Y-Coordinate


_____________________________________________
---
## Caves | Property

### Description:
4D Vector of all the current caves
static std::vector<std::vector<std::vector<std::vector<int>>>> Caves;


### Implementation:
```static std::vector<std::vector<std::vector<std::vector<int>>>> Caves;```


_____________________________________________
---
## GenerateSingleCave | Function

### Description:
Generate a 2D Integer Vector of a cave. Includes Resources


### Implementation:
```static std::vector<std::vector<int>> GenerateSingleCave(int fillDensity, int smoothness, bool generateExit = false);```

### Parameters:
- int fillDensity // WorldGen recommends 35
- int smoothness
- bool generateExit = false // Only changed to true when a mineshaft is being generated


_____________________________________________
---
## AddCave | Function

### Description:
Adds the passed 2D Vector parameter to the 4D integer vector:
```cpp
CaveGeneration::Caves
```


### Implementation:
```static void AddCave(std::vector<std::vector<int>> newCave, vector2 pos);```

### Parameters:
- std::vector\<std::vector\<int\>\> newCave
- vector2 pos


_____________________________________________
---
## Init | Function

### Description:
Initializes the Caves Vector
static void Init();


### Implementation:
```static void Init();```


_____________________________________________
---
## GetExit | Function

### Description:
Find a suitable exit for the exit-hatch to spawn.
Similar to the `WorldGen::FindSuitableSpawnPoint`


### Implementation:
```static vector2 GetExit(int** map);```

### Parameters:
- int** map


_____________________________________________
---
## Generate Resources | Function

### Description:
Generates random resources such as Iron, and Coal


### Implementation:
```static std::vector<std::vector<int>> GenerateResources(std::vector<std::vector<int>> caveMap);```

### Parameters:
- std::vector\<std::vector\<int\>\>


_____________________________________________
---
## CaveSum | Function

### Description:
Gets the cumulative sum of the cave elements.
Mostly used in conjunction to figure out if the cave has been generated or not


### Implementation:
```static int CaveSum(std::vector<std::vector<int>> cave);```

### Parameters:
- std::vector\<std::vector\<int\>\> cave


_____________________________________________
---
## CaveEmpty | Function | [DEPRECATED]

### Description:
Alternative for CaveSum, returns boolean


### Implementation:
```static bool CaveEmpty(std::vector<std::vector<int>> cave);```

### Parameters:
- std::vector\<std::vector\<int\>\> cave


_____________________________________________
---

