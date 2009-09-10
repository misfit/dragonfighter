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
  if (l0ttr->nowalkhead != NULL) {
    NOWALKNODE *temp;
    temp = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
    
    while (temp->next != NULL) {
      temp = l0ttr->nowalkhead;
      l0ttr->nowalkhead = l0ttr->nowalkhead->next;
      free (temp->block);
      free (temp);
    }
  }
  free (l0ttr);
}
