# CONSOLE.h

## CONSOLE | Constructor

### Implementation:
```CONSOLE(HANDLE _handle);```

### Parameters:
- HANDLE _handle


_____________________________________________
---
## DrawWorldMap | Function

### Description:
Re-Draws to the screen based on the passed worldMap parameter
[parameter]
- int** worldMap
void DrawWorldMap(int** worldMap);


### Implementation:
```void DrawWorldMap(int** worldMap);```


_____________________________________________
---
## VectorToCOORD | Function

### Description:
[parameter]
- vector2 vector
static COORD VectorToCOORD(vector2 vector);


### Implementation:
```static COORD VectorToCOORD(vector2 vector);```


_____________________________________________
---
## PosToCOORD | Function

### Description:
[parameter]
- int x
- int y
static COORD PosToCOORD(int x, int y);


### Implementation:
```static COORD PosToCOORD(int x, int y);```


_____________________________________________
---

