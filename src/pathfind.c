#include "pathfind.h"
#include "structures.h"

#define DIR_NONE  0
#define DIR_NORTH 1
#define DIR_EAST  2
#define DIR_SOUTH 3
#define DIR_WEST  4

void resetSearchBit(Maze* maze) {
  for (int i=0; i<16; ++i) {
    for (int j=0; j<16; ++j) {
      *maze[i][j] &= ~(CELL_SEARCHED);
    }
  }
}

// Assumes knowledge of the maze is known
void pathfind(Maze* maze, uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, Path* output) {
  // Floodfill (BFS) while keeping track of previous cells
  uint8_t nextcell[32];
  int head=-1, tail=-1;
  resetSearchBit(maze);
  Maze prevcelldir;

  nextcell[++tail % 32] = x + y*16;
  prevcelldir[x][y] = 0;
  *maze[x][y] |= CELL_SEARCHED;

  uint8_t cellnum = 0;
  int cx=0, cy=0;

  do {
    cellnum = nextcell[++head];
    cx = cellnum % 16;
    cy = cellnum / 16;

    if ( (*maze[cx][cy] & CELL_WALL_NORTH) == 0 ) {   // If there is no wall up...
      if ( (*maze[cx][cy+1] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = cx + (cy+1)*16;           // Add the cell to ringbuf...
        *maze[cx][cy+1] |= CELL_SEARCHED;                 // and set the cell to searched
        prevcelldir[cx][cy+1] = DIR_SOUTH;
      }
    }

    if ( (*maze[cx][cy] & CELL_WALL_EAST) == 0 ) {   // If there is no wall right...
      if ( (*maze[cx+1][cy] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = (cx+1) + cy*16;           // Add the cell to ringbuf...
        *maze[cx+1][cy] |= CELL_SEARCHED;                 // and set the cell to searched
        prevcelldir[cx+1][cy] = DIR_WEST;
      }
    }

    if ( (*maze[cx][cy] & CELL_WALL_SOUTH) == 0 ) {   // If there is no wall down...
      if ( (*maze[cx][cy-1] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = cx + (cy-1)*16;           // Add the cell to ringbuf...
        *maze[cx][cy-1] |= CELL_SEARCHED;                 // and set the cell to searched
        prevcelldir[cx][cy-1] = DIR_NORTH;
      }
    }

    if ( (*maze[cx][cy] & CELL_WALL_WEST) == 0 ) {   // If there is no wall left...
      if ( (*maze[cx-1][cy] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = (cx-1) + cy*16;           // Add the cell to ringbuf...
        *maze[cx-1][cy] |= CELL_SEARCHED;                 // and set the cell to searched
        prevcelldir[cx-1][cy] = DIR_EAST;
      }
    }

  } while ( (cx != tx && cy != ty) && (head != tail) );  // While current cell has been visited...

  // Manipulate the prevcelldir array into a usable path
}

// For now just call the normal pathfinding function
void pathfindOptimized(Maze* maze, uint8_t x, uint8_t y, uint8_t tx, uint8_t ty, Path* output) {
  pathfind(maze, x, y, tx, ty, output);
}

uint8_t findClosestUnexploredCell(Maze* maze, uint8_t x, uint8_t y) {
  uint8_t nextcell[32]; // Holds cell number for the next cells to check in BFS
  int head=-1, tail=-1; // Indices used by the ringbuffer
  resetSearchBit(maze);

  nextcell[++tail % 32] = x + y*16;
  *maze[x][y] |= CELL_SEARCHED;

  uint8_t cellnum=0;
  int cx=0, cy=0; 

  do {
    cellnum = nextcell[++head];
    cx = cellnum % 16;
    cy = cellnum / 16;

    if ( (*maze[cx][cy] & CELL_WALL_NORTH) == 0 ) {   // If there is no wall up...
      if ( (*maze[cx][cy+1] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = cx + (cy+1)*16;           // Add the cell to ringbuf...
        *maze[cx][cy+1] |= CELL_SEARCHED;                 // and set the cell to searched
      }
    }

    if ( (*maze[cx][cy] & CELL_WALL_EAST) == 0 ) {   // If there is no wall right...
      if ( (*maze[cx+1][cy] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = (cx+1) + cy*16;           // Add the cell to ringbuf...
        *maze[cx+1][cy] |= CELL_SEARCHED;                 // and set the cell to searched
      }
    }

    if ( (*maze[cx][cy] & CELL_WALL_SOUTH) == 0 ) {   // If there is no wall down...
      if ( (*maze[cx][cy-1] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = cx + (cy-1)*16;           // Add the cell to ringbuf...
        *maze[cx][cy-1] |= CELL_SEARCHED;                 // and set the cell to searched
      }
    }

    if ( (*maze[cx][cy] & CELL_WALL_WEST) == 0 ) {   // If there is no wall left...
      if ( (*maze[cx-1][cy] & CELL_SEARCHED) == 0 ) {   // and it hasn't been searched yet...
        nextcell[++tail % 32] = (cx-1) + cy*16;           // Add the cell to ringbuf...
        *maze[cx-1][cy] |= CELL_SEARCHED;                 // and set the cell to searched
      }
    }

  } while ( (*maze[cx][cy] & CELL_VISITED) && (head != tail) );  // While current cell has been visited...

  if ( head == tail ) return 0;
  return cellnum;
}
