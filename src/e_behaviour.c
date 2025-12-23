// e_behaviour.c
// handles interaction between the player and the game
// 
// 
// created: 19/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// external libraries
#include <raylib.h>

// internal headers
#include <e_storage.h>
#include <e_behaviour.h>
#include <e_render.h>
#include <e_world.h>
#include <e_tile_definitions.h>
#include <player.h>

int score = 0;
int high_score = 0;


void e_behaviour_handle_screens (int * current_screen, int * frame_counter) {
  int new_current_screen = *current_screen;
  int new_frame_counter = *frame_counter;

  new_frame_counter++;
  
  switch (new_current_screen) {
  case LOGO:
    if (new_frame_counter >= 120){
      high_score = e_storage_load_value(STORAGE_POSITION_HIGH_SCORE);      
      new_current_screen = TITLE;
    }
    break;

  case TITLE:
    if (IsKeyPressed(KEY_ENTER)) {
      e_world_generate_level();
      new_current_screen = GAMEPLAY;
    }
    break;

  case GAMEPLAY:
    if (IsKeyPressed(KEY_Q)) {
      new_current_screen = MENU;
    }

    e_behaviour_handle_player_movement();
    e_behaviour_handle_player_actions();
    break;

  case GAMEOVER:
    if (IsKeyPressed(KEY_ENTER)){
      e_storage_save_value(STORAGE_POSITION_HIGH_SCORE, score);

      new_current_screen = TITLE;
    }
    break;

  case MENU:
    if (IsKeyPressed(KEY_Q)) {
      new_current_screen = GAMEPLAY;
      break;     
    }

    if (IsKeyPressed(KEY_T)) {
      e_storage_save_value(STORAGE_POSITION_HIGH_SCORE, score);
      new_current_screen = TITLE;
      break;
    }    
    break;
    
  default:
    break;
  }

  *current_screen = new_current_screen;
  *frame_counter = new_frame_counter + 1;
}

void e_behaviour_handle_player_movement (void) {
  struct player_info_s new_player_info = player_get_info();
  
  if (IsKeyPressed(KEY_LEFT)) {
    new_player_info.x_pos--;
    new_player_info.x_facing = -1;
    new_player_info.y_facing = 0;
  }
  
  if (IsKeyPressed(KEY_RIGHT)) {
    new_player_info.x_pos++;
    new_player_info.x_facing = 1;
    new_player_info.y_facing = 0;
  }

  if (IsKeyPressed(KEY_UP)) {
    new_player_info.y_pos--;
    new_player_info.x_facing = 0;
    new_player_info.y_facing = -1;
  }

  if (IsKeyPressed(KEY_DOWN)) {
    new_player_info.y_pos++;
    new_player_info.x_facing = 0;
    new_player_info.y_facing = 1;
  }
  
  if (e_world_get_tile_at_pos(new_player_info.x_pos, new_player_info.y_pos) > 0 ||
      IsKeyDown(KEY_LEFT_CONTROL)){
    new_player_info.x_pos = player_get_info().x_pos;
    new_player_info.y_pos = player_get_info().y_pos;
  }
  
  // disallow player from exiting level
  if (new_player_info.x_pos < 0) {
    new_player_info.x_pos = 0;
    new_player_info.x_facing = 0;
  } else if (new_player_info.x_pos >= MAP_WIDTH-1) {
    new_player_info.x_pos = MAP_WIDTH-1;
    new_player_info.x_facing = 0;
  }

  if (new_player_info.y_pos < 0) {
    new_player_info.y_pos = 0;
    new_player_info.y_facing = 0;
  } else if (new_player_info.y_pos >= MAP_LENGTH-1) {
    new_player_info.y_pos = MAP_LENGTH-1;
    new_player_info.y_facing = 0;
  }

  player_set_info(new_player_info);
}

void e_behaviour_handle_player_actions (void) {
  struct player_info_s new_player_info = player_get_info();
  int facing_x_pos = new_player_info.x_pos + new_player_info.x_facing;
  int facing_y_pos = new_player_info.y_pos + new_player_info.y_facing;
  int facing_tile = e_world_get_tile_at_pos(facing_x_pos, facing_y_pos);

  bool facing_tile_indestructible = e_tile_def_get_tile_properties(facing_tile).health == -1;
  
  if (IsKeyPressed(KEY_PERIOD) && facing_tile > 0 && !facing_tile_indestructible) {
    e_world_set_tile_at_pos(facing_x_pos, facing_y_pos, 0);
  }
}
