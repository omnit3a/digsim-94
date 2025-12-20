// main.c
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
#include <e_render.h>
#include <e_behaviour.h>

int current_screen = LOGO;

int main (int argc, char ** argv){
  int frame_counter = 0;

  //int score = 0;
  //int high_score = 0;

  e_render_init();
  
  while (!WindowShouldClose()) {
    e_behaviour_handle_screens(&current_screen, &frame_counter);
    e_render_main_loop(current_screen);
  }

  e_render_shutdown();
  return 0;
}
