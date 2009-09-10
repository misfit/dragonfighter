#include "common.h"

int ttrl0[TTRL0W*TTRL0H] = {
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,2,2,2,2,2,2,2,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,1,1,1,1,1,1,2,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,1,2,1,1,2,1,2,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,2,2,2,2,2,2,2,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,2,2,2,2,2,2,2,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,2,2,2,2,2,2,2,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,3,3,3,11,3,3,3,3,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,2,2,2,2,2,2,2,12,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
};

int main (void) {
  setup_game();
  teardown_game();
  return 0;
}
END_OF_MAIN()

void setup_game (void) {
  allegro_init();
  install_keyboard();
  install_timer();
  srand (time (NULL));
  
  set_color_depth (24);
  set_gfx_mode (MODE, WIDTH, HEIGHT, 0, 0);
  scroll = create_bitmap (TTRL0W, TTRL0H);
  buffer = create_bitmap (WIDTH, HEIGHT);

  load_map (TTRL0);

  scrollx = 0;
  scrolly = 0;

  startx = 0;
  starty = 0;
}

void teardown_game (void) {
  destroy_bitmap (scroll);
  destroy_bitmap (buffer);
  allegro_exit();
}

BITMAP *grabframe (BITMAP *source,
                   int width, int height,
		   int startx, int starty,
		   int columns, int frame) {
  BITMAP *temp = create_bitmap(width,height);
  int x = startx + (frame % columns) * width;
  int y = starty + (frame / columns) * height;
  blit(source,temp,x,y,0,0,width,height);
  return temp;
}

void draw_ttrl0 (void) {
  int i = 0;
  BITMAP *tiles = load_bitmap ("maptiles.bmp", NULL);

  for (tiley = 0; tiley < scroll->h; tiley += TILEH) {
    for (tilex = 0; tilex < scroll->w; tilex += TILEW) {
      blit (grabframe (tiles, TILEW+1, TILEH+1, 0, 0, COLS, ttrl0[i++]),
	    scroll, 0, 0, tilex, tiley, TILEW, TILEH);
    }
  }
  destroy_bitmap (tiles);
}

void load_map (char *map) {
  if (strcmp (map, TTRL0) == 0) draw_ttrl0();
}
