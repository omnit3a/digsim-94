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

struct tile_info_s e_world_map[MAP_WIDTH * MAP_LENGTH];
void e_world_set_tile_at_pos(int x_pos, int y_pos, struct tile_info_s tile) {
  const int index = MAP_WIDTH * y_pos + x_pos;
  e_world_map[index].tile_id = tile.tile_id;
  e_world_map[index].health = tile.health;
  
}

struct tile_info_s e_world_get_tile_at_pos(int x_pos, int y_pos) {
  return e_world_map[MAP_WIDTH * y_pos + x_pos];
}

void e_world_generate_level() {
  const float perlin_roughness = 0.3;
  for (int y = 0 ; y < MAP_LENGTH ; y++){
    for (int x = 0 ; x < MAP_WIDTH ; x++){      
      float tile = stb_perlin_noise3_seed(x * perlin_roughness, y * perlin_roughness, 0,
					  MAP_WIDTH, MAP_LENGTH, 0,
					  time(0));
      int tile_to_place_id;
      if (tile > 0.65) {
	tile_to_place_id = TILE_IRON;
      } else if (tile > 0.35) {
	tile_to_place_id = TILE_COAL;
      } else if (tile > 0.1) {
	tile_to_place_id = TILE_STONE;
      } else {
	tile_to_place_id = TILE_AIR;
      }
      
      if ((y == 0 || y >= MAP_LENGTH-1) || (x == 0 || x >= MAP_WIDTH-1)) {
	tile_to_place_id = TILE_UNBREAKABLE;
      }

      struct tile_info_s tile_info_for_tile = e_tile_def_to_tile_info(tile_to_place_id);
      e_world_set_tile_at_pos(x, y, tile_info_for_tile);
    }
  }

  // create empty area around the player
  for (int y = -1 ; y < 2 ; y++) {
    for (int x = -1 ; x < 2 ; x++) {
      e_world_set_tile_at_pos((MAP_WIDTH/2)+x, (MAP_LENGTH/2)+y, e_tile_def_to_tile_info(TILE_AIR));
    }
  }
}
