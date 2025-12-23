// e_world.c
// handles the world, including world generation and map modification
// 
// 
// created: 20/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>

// external libraries

// internal headers
#include <e_world.h>

int e_world_map[16 * 16] = {
  1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
  1,0,0,0,1,1,2,1,0,0,0,0,0,0,0,0,
  1,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,
  1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void e_world_set_tile_at_pos(int x_pos, int y_pos, int tile) {
  e_world_map[16 * y_pos + x_pos] = tile; 
}

int e_world_get_tile_at_pos(int x_pos, int y_pos) {
  return e_world_map[16 * y_pos + x_pos];
}
  
void e_world_generate_level() {
  
}
