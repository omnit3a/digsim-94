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
      new_current_screen = GAMEPLAY;
    }
    break;

  case GAMEPLAY:
    if (IsKeyPressed(KEY_Q)) {
      new_current_screen = MENU;
    }

    e_behaviour_handle_player();
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

void e_behaviour_handle_player (void) {
  struct player_info_s new_player_info = player_get_info();
  
  if (IsKeyPressed(KEY_LEFT)) {
    new_player_info.x_pos--;
  }
  
  if (IsKeyPressed(KEY_RIGHT)) {
    new_player_info.x_pos++;
  }

  if (IsKeyPressed(KEY_UP)) {
    new_player_info.y_pos--;
  }

  if (IsKeyPressed(KEY_DOWN)) {
    new_player_info.y_pos++;
  }

  if (new_player_info.x_pos < 0) {
    new_player_info.x_pos = 0;
  }

  if (new_player_info.x_pos > 15) {
    new_player_info.x_pos = 15;
  }

  if (new_player_info.y_pos < 0) {
    new_player_info.y_pos = 0;
  }

  if (new_player_info.y_pos > 15) {
    new_player_info.y_pos = 15;
  }

  player_set_info(new_player_info);
}
