#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <inttypes.h>

typedef uint8_t Maze[16][16];

#define CELL_WALL_NORTH   (1 << 0)
#define CELL_WALL_EAST    (1 << 1)
#define CELL_WALL_SOUTH   (1 << 2)
#define CELL_WALL_WEST    (1 << 3)
#define CELL_SEARCHED     (1 << 5) // A cell is searched when using pathfinding algorithms
#define CELL_INTERESTING  (1 << 6) // A cell is interesting if it has more than one exit (more than two openings total)
#define CELL_VISITED      (1 << 7)

enum ActionType {
  STOP_RUN = 0,
  MOVE_FORWARD,
  TURN_CW,
  TURN_CCW,
  SENSE_WALLS,
  AWAIT_INPUT,
};

typedef struct Action {
  enum ActionType type;
  int8_t data;
} Action;

typedef Action Path[256];

#endif
