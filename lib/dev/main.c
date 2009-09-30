/****
 * Main program file for Dragon Fighter.
 * Copyright (c) 2009 Brian S. Moriya
 * See LICENSE and COPYING for important license information.
 ****/

#include "common.h"

int main (void) {
  /* initialize the game. */
  setup_allegro (MODE, WIDTH, HEIGHT, 16);
  setup_bmps();
  scrollx = 0;
  scrolly = 0;
  
  draw_TCBLALB();

  while (!key[KEY_ESC]) {
    /* Testing scrolling input */
    if (key[KEY_RIGHT])
      if ((scrollx+=1) > scrollbmp->w-WIDTH) scrollx = scrollbmp->w - WIDTH;
    if (key[KEY_LEFT]) if ((scrollx-=1) < 0) scrollx = 0;
    if (key[KEY_DOWN])
      if ((scrolly+=1) > scrollbmp->h-HEIGHT) scrolly = scrollbmp->h - HEIGHT;
    if (key[KEY_UP]) if ((scrolly-=1) < 0) scrolly = 0;
    /* end of test code. */
    blit (scrollbmp, bufferbmp, scrollx, scrolly, 0, 0, WIDTH-1, HEIGHT-1);
    
    acquire_screen();
    blit (bufferbmp, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
    release_screen();
    
    rest (20);
  }
  destroy_bmps();
  allegro_exit();
  return 0;
}
END_OF_MAIN()

void setup_allegro (int mode, int screenw, int screenh, int cdepth) {
  allegro_init();
  install_keyboard();
  install_timer();
  srand (time (NULL));
  set_color_depth (cdepth);
  set_gfx_mode (mode, screenw, screenh, 0, 0);
}

void setup_bmps (void) {
  bufferbmp = create_bitmap (WIDTH, HEIGHT);
  scrollbmp = create_bitmap (TCBW, TCBH);
  tilesbmp = load_bitmap ("maptiles.bmp", NULL);
}

void destroy_bmps (void) {
  destroy_bitmap (bufferbmp);
  destroy_bitmap (scrollbmp);
  destroy_bitmap (tilesbmp);
}

void draw_frame (BITMAP *source, BITMAP *destination, int x, int y, int width,
                int height, int startx, int starty, int columns, int frame) {
  /* calculate frame position */
  int framex = startx + (frame%columns)*width;
  int framey = starty + (frame/columns)*height;
  /* draw frame to destination bitmap. */
  masked_blit (source, destination, framex, framey, x, y, width, height);
}

void draw_TCBLALB (void) {
  int i = 0;
  for (tiley = 0; tiley < scrollbmp->h; tiley += TILEH) {
    for (tilex = 0; tilex < scrollbmp->w; tilex += TILEW) {
      draw_frame (tilesbmp, scrollbmp, tilex, tiley, TILEW, TILEH, 0, 0,
                  COLS, TCBLALB[i++]);
    }
  }
}
