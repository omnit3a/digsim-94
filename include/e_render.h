#ifndef E_RENDER_H_
#define E_RENDER_H_

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WINDOW_TITLE "digsim '94"
#define TILE_ATLAS_PATH "assets/tiles.png"
#define TILE_ATLAS_WIDTH_IN_TILES 16
#define TILE_ATLAS_HEIGHT_IN_TILES 16
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define SCALED_TILE_WIDTH (TILE_WIDTH * 4)
#define SCALED_TILE_HEIGHT (TILE_HEIGHT * 4)
#define OPENGL_TILE_SHADER_PATH "assets/shaders/tile_shader.fs"

#define VIEW_RADIUS 3
#define VIEW_RADIUS_WITH_TORCH 5

enum game_screen_e{
  LOGO,
  TITLE,
  GAMEPLAY,
  GAMEOVER,
  MENU
};

void e_render_init (void);
void e_render_shutdown (void);

void e_render_main_loop (int current_screen);

void e_render_tile_from_atlas (int offset, int x_dest, int y_dest);
void e_render_gameplay (void);


#endif
