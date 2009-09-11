#include "common.h"

void teardown_game (void) {
  teardown_player();
  teardown_screen();
  allegro_exit();
}

void teardown_player (void) {
  int i;
  
  for (i = 0; i < 2; i++) {
    destroy_bitmap (player_up_bmps[i]);
    destroy_bitmap (player_down_bmps[i]);
    destroy_bitmap (player_right_bmps[i]);
    destroy_bitmap (player_left_bmps[i]);
  }
  free (player);
}

void teardown_screen (void) {
  destroy_bitmap (scroll);
  destroy_bitmap (buffer);
}

void teardown_ttrl0 (void) {
  int i;
  for (i = 0; i < TTRL0NW; i++) free (ttrl0nowalks[i]);
}
