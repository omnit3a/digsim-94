// e_behaviour.c
// <insert notes here>
// 
// 
// created: 19/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>

// external libraries
#include <raylib.h>

// internal headers
#include <e_storage.h>
#include <e_behaviour.h>

int score = 0;
int high_score = 0;

#include <e_render.h>

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
