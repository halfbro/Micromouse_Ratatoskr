#ifndef __PATHFIND_H__
#define __PATHFIND_H__

#include "structures.h"

void pathfind(Maze* maze, uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, Path* output);
void pathfindOptimized(Maze* maze, uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, Path* output);

uint8_t findClosestUnexploredCell(Maze* maze, uint8_t x, uint8_t y);

#endif
