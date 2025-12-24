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
  {0, 0,  0, -1}, // air
  {1, 1,  0,  1}, // stone
  {2, 2,  1,  2}, // coal
  {3, 3,  4,  2}, // copper
  {4, 4,  2,  2}, // iron
  {5, 16, 0, -1}  // unbreakable stone
};

struct e_tile_def_tile_properties e_tile_def_get_tile_properties(int tile) {
  if (tile >= AMOUNT_OF_TILES) {
    return tile_defs[tile];
  }
  
  return tile_defs[tile];
}
