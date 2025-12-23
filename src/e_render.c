// render.c
// handles rendering
// 
// 
// created: 19/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// external libraries
#include <raylib.h>

// internal headers
#include <e_storage.h>
#include <e_render.h>
#include <e_world.h>
#include <player.h>

int render_score = 0;
int render_high_score = 0;
Texture2D tile_atlas;
Texture2D player_sprite;
Shader tile_shader;

void e_render_init (void) {
  render_high_score = e_storage_load_value(STORAGE_POSITION_HIGH_SCORE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  tile_atlas = LoadTexture(TILE_ATLAS_PATH);
  player_sprite = LoadTexture(PLAYER_SPRITESHEET_PATH);
  tile_shader = LoadShader(0, OPENGL_TILE_SHADER_PATH);
  SetTargetFPS(60);
}

void e_render_shutdown (void) {
  UnloadShader(tile_shader);
  UnloadTexture(player_sprite);
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

void e_render_tile_from_atlas (Texture2D texture, int offset, int x_dest, int y_dest){  
  int x_index = (offset % TILE_ATLAS_WIDTH_IN_TILES) * TILE_WIDTH;
  int y_index = (offset / TILE_ATLAS_HEIGHT_IN_TILES) * TILE_HEIGHT;

  Rectangle source_rect = {x_index, y_index, TILE_WIDTH, TILE_HEIGHT};
  
  Rectangle dest_rect = {(x_dest*SCALED_TILE_WIDTH)+(SCALED_TILE_WIDTH/2),
			 (y_dest*SCALED_TILE_HEIGHT)+(SCALED_TILE_HEIGHT/4),
			 SCALED_TILE_WIDTH, SCALED_TILE_HEIGHT};
  Vector2 origin = {0, 0};

  DrawTexturePro(texture, source_rect, dest_rect, origin, 0, WHITE);
}

void e_render_gameplay (void) {
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    
  BeginShaderMode(tile_shader);

  // TODO: differentiate between blocks and tiles + allow for multiple blocks on a single tile.
  int x_pos = player_get_info().x_pos;
  int y_pos = player_get_info().y_pos;
  int x_facing = player_get_info().x_facing;
  int y_facing = player_get_info().y_facing;

  // get visible area
  int x_view_min = fmax(0, x_pos - VIEW_RADIUS);
  int x_view_max = fmin(15, x_pos + VIEW_RADIUS);
  int y_view_min = fmax(0, y_pos - VIEW_RADIUS);
  int y_view_max = fmin(15, y_pos + VIEW_RADIUS);

  // render visible area
  for (int view_y = y_view_min ; view_y <= y_view_max ; view_y++) {
    for (int view_x = x_view_min ; view_x <= x_view_max ; view_x++){
      int tile = e_world_get_tile_at_pos(view_x, view_y);
      
      e_render_tile_from_atlas(tile_atlas,
			       tile,
			       (view_x-x_pos) + VIEW_RADIUS + 1,
			       (view_y-y_pos) + VIEW_RADIUS);
    }
  }

  // render player sprite
  e_render_tile_from_atlas(player_sprite, 0, 4, 3);
  // render block highlighter

  if (x_facing + y_facing == 0) {
    EndShaderMode();
    return;
  }
  
  if (e_world_get_tile_at_pos(x_pos+x_facing, y_pos+y_facing) > 0) {
    e_render_tile_from_atlas(player_sprite, 4, 4+x_facing, 3+y_facing);
  } else {
    e_render_tile_from_atlas(player_sprite, 5, 4+x_facing, 3+y_facing);
  }
    
  EndShaderMode();
}
