// e_world.c
// handles the world, including world generation and map modification
// 
// 
// created: 20/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// external libraries
#include <external/stb_perlin.h>

// internal headers
#include <e_tile_definitions.h>
#include <e_world.h>

int e_world_map[MAP_WIDTH * MAP_LENGTH];
void e_world_set_tile_at_pos(int x_pos, int y_pos, int tile) {
  e_world_map[MAP_WIDTH * y_pos + x_pos] = tile; 
}

int e_world_get_tile_at_pos(int x_pos, int y_pos) {
  return e_world_map[MAP_WIDTH * y_pos + x_pos];
}

void e_world_generate_level() {
  const float perlin_roughness = 0.3;
  for (int y = 0 ; y < MAP_LENGTH ; y++){
    for (int x = 0 ; x < MAP_WIDTH ; x++){      
      float tile = stb_perlin_noise3_seed(x * perlin_roughness, y * perlin_roughness, 0,
					  MAP_WIDTH, MAP_LENGTH, 0,
					  time(0));
      if (tile > 0.65) {
	e_world_set_tile_at_pos(x, y, TILE_IRON);
      } else if (tile > 0.35) {
	e_world_set_tile_at_pos(x, y, TILE_COAL);
      } else if (tile > 0.1) {
	e_world_set_tile_at_pos(x, y, TILE_STONE);
      } else {
	e_world_set_tile_at_pos(x, y, TILE_AIR);
      }
      
      if (y == 0 || y >= MAP_LENGTH-1) {
	e_world_set_tile_at_pos(x, y, TILE_UNBREAKABLE);
      } else if (x == 0 || x >= MAP_WIDTH-1) {
	e_world_set_tile_at_pos(x, y, TILE_UNBREAKABLE);
      }
    }
  }

  // create empty area around the player
  for (int y = -1 ; y < 2 ; y++) {
    for (int x = -1 ; x < 2 ; x++) {
      e_world_set_tile_at_pos((MAP_WIDTH/2)+x, (MAP_LENGTH/2)+y, TILE_AIR);
    }
  }
}
