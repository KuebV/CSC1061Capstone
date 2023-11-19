# WorldGen.h

## GenerateBasicWorld | Function

### Description:
Return a randomly generated 2D int array based on the passed fillDensity


### Implementation:
```static int** GenerateBasicWorld(int fillDensity);```

### Parameters:
- int fillDensity


_____________________________________________
---
## SmoothExistingBasicWorld | Function

### Description:
Using the Cellular Automa algorithm, smooth the randomly generated array into more realistic terrain


### Implementation:
```static int** SmoothExistingBasicWorld(int** basicMap, int smoothness);```

### Parameters:
- int** basicMap
- int smoothness


_____________________________________________
---
## GenerateBeaches | Function

### Description:
Modify the WorldMap to include beaches around the bodies of water


### Implementation:
```static int** GenerateBeaches(int** detailedMap);```

### Parameters:
- int** detailedMap


_____________________________________________
---
## FindSuitableSpawnPoint | Function

### Description:
Randomly search for a suitable spawn location for the player, must not spawn the player that may result in them being placed somewhere unsafe


### Implementation:
```static vector2 FindSuitableSpawnPoint(int** detailedMap, int requiredWalls = 2);```

### Parameters:
- int** detailedMap
- int requiredWalls = 2


_____________________________________________
---
## GenerateForestry | Function

### Description:
Using a modified WorldGen::GenerateBasicWorld function, generate trees around the map


### Implementation:
```static int** GenerateForestry(int** detailedMap, int densityForestry);```

### Parameters:
- int** detailedMap
- int densityForestry


_____________________________________________
---
## GenerateBoulders | Function

### Description:
Using a modified WorldGen::GenerateBasicWorld function, generate boulders around the map


### Implementation:
```static int** GenerateBoulders(int** detailedMap, int densityRocks);```

### Parameters:
- int** detailedMap
- int densityRocks


_____________________________________________
---
## ModifiedTileResult | Function

### Description:
When the player interacts with a tile, this function will return whether or not the tile needs to be modified to change the end result
**DOES NOT DIRECTLY MODIFY WORLD MAP**


### Implementation:
```static int ModifiedTileResult(int beforeTile);```

### Parameters:
- int beforeTile


_____________________________________________
---
## GenerateMineshafts | Function

### Description:
Using a modified WorldGen::GenerateBasicWorld function, generate mineshafts around the map


### Implementation:
```static int** GenerateMineshafts(int** detailedMap, int mineshafts);```

### Parameters:
- int** detailedMap
- int mineshafts // total amount of mineshafts to spawn on the map


_____________________________________________
---

