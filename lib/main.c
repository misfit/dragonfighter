#include "common.h"

int main (void) {
  setup_game();
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
}

void load_map (char *map) {
  if (strcmp (map, TTRL0) == 0) draw_ttrl0();
}
