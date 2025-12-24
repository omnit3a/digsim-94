#ifndef E_TILE_DEFINITIONS_H_
#define E_TILE_DEFINITIONS_H_

#include <e_world.h>
#include <stdint.h>

#define AMOUNT_OF_TILES 6

struct e_tile_def_tile_properties {
  int id;
  int atlas_offset;
  int score_given;
  int health;
};

enum e_tile_def_ids {
  TILE_AIR,
  TILE_STONE,
  TILE_COAL,
  TILE_COPPER,
  TILE_IRON,
  TILE_UNBREAKABLE
};

struct e_tile_def_tile_properties e_tile_def_get_tile_properties(int tile);
#endif
