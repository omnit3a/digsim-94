// e_tile_definitions.c
// handles the properties of tiles in world.
// 
// 
// created: 23/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>

// external libraries

// internal headers
#include <e_tile_definitions.h>

struct e_tile_def_tile_properties tile_defs[AMOUNT_OF_TILES] = {
  {0, 0,  -1},
  {1, 1,   1},
  {2, 2,   2},
  {3, 3,   2},
  {4, 4,   2},
  {5, 16, -1} 
};

struct e_tile_def_tile_properties e_tile_def_get_tile_properties(int tile) {
  if (tile >= AMOUNT_OF_TILES) {
    return tile_defs[tile];
  }
  
  return tile_defs[tile];
}
