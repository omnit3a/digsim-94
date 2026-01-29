#ifndef E_WORLD_H_
#define E_WORLD_H_

#include <stdbool.h>

#define MAP_WIDTH 32
#define MAP_LENGTH 32

struct tile_info_s {
  int tile_id;
  int health;
};

void e_world_set_tile_at_pos(int x_pos, int y_pos, struct tile_info_s tile);
struct tile_info_s e_world_get_tile_at_pos(int x_pos, int y_pos);

void e_world_generate_level();

#endif
