// render.c
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
#include <e_world.h>

int render_score = 0;
int render_high_score = 0;
Texture2D tile_atlas;
Shader tile_shader;

void e_render_init (void) {
  render_high_score = e_storage_load_value(STORAGE_POSITION_HIGH_SCORE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  tile_atlas = LoadTexture(TILE_ATLAS_PATH);
  tile_shader = LoadShader(0, OPENGL_TILE_SHADER_PATH);
  SetTargetFPS(60);
}

void e_render_shutdown (void) {
  UnloadShader(tile_shader);
  UnloadTexture(tile_atlas);
  CloseWindow();
}

void e_render_main_loop (int current_screen) {
  BeginDrawing();
  ClearBackground(BLACK);

  switch (current_screen){
    case LOGO:
      DrawText("BDR GAMES", 20, 20, 40, RAYWHITE);
      DrawText("Presents...", 20, 60, 20, RAYWHITE);
      break;
      
    case TITLE:
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
      DrawText("DIGSIM '94", 20, 20, 40, YELLOW);
      DrawText(TextFormat("HIGH SCORE: %i", render_high_score), 20, 70, 20, YELLOW);
      DrawText("Press Enter to start the game.", 20, 100, 20, YELLOW);
      DrawText("[Escape] -> Exit the game", 20, 120, 20, YELLOW);
      break;
      
  case GAMEPLAY:
      e_render_gameplay();
      break;
      
  case GAMEOVER:
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RED);
      DrawText("You are dead.", 20, 20, 40, WHITE);
      DrawText("Press Enter to save and return to the title screen.", 20, 60, 20, WHITE);
      break;
      
  case MENU:
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
      DrawText("MENU", 20, 20, 40, YELLOW);
      DrawText(TextFormat("SCORE: %i", render_score), 20, 70, 20, YELLOW);
      DrawText("Q: Resume game", 20, 100, 20, YELLOW);
      DrawText("T: Save and return to title", 20, 120, 20, YELLOW);
      break;
      
  default:
      break;      
  }
  
  EndDrawing();
}

void e_render_tile_from_atlas (int offset, int x_dest, int y_dest){
  int x_index = (offset % TILE_ATLAS_WIDTH_IN_TILES) * 16;
  int y_index = (offset / TILE_ATLAS_HEIGHT_IN_TILES) * 16;
  Rectangle source_rect = {x_index, y_index, TILE_WIDTH, TILE_HEIGHT};
  Rectangle dest_rect = {x_dest*(TILE_WIDTH * 4), y_dest*(TILE_HEIGHT * 4),
			 x_dest+(TILE_WIDTH * 4), y_dest+(TILE_HEIGHT * 4)};
  Vector2 origin = {0, 0};

  DrawTexturePro(tile_atlas, source_rect, dest_rect, origin, 0, RAYWHITE);
}

void e_render_gameplay (void) {
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
  //DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
  //DrawText("Press Q to enter the menu.", 20, 60, 20, MAROON);
  BeginShaderMode(tile_shader);
  for (int y = 0 ; y < 16 ; y++) {
    for (int x = 0 ; x < 16 ; x++){
      int tile = e_world_get_tile_at_pos(x, y);
      e_render_tile_from_atlas(tile, x, y);
    }
  }
  EndShaderMode();
}
