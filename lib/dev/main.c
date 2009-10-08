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
  setup_player();
  scrollx = 0;
  scrolly = 0;
  
  currentmap = (MAP*)malloc (sizeof (MAP));
  currentmap->lockeddoors = 0x1;
  currentmap->pointofentry = 0;
  currentmap->pointofexit = 0;
  currentmap->initflag = 1;
  currentmap->idnumber = TCA_13;
  currentmap->chests = 0x2;
    
  map_handler();

  while (!key[KEY_ESC]) {
    get_input();
    move_player();
    scroll_window();
    animate_player();
    map_event_handler();
    map_handler();
    draw_player();
    blit (scrollbmp, bufferbmp, scrollx, scrolly, 0, 0, WIDTH-1, HEIGHT-1);
    print_scroll_debug_messages();
    print_player_debug_messages();

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

void print_scroll_debug_messages (void) {
  textprintf_ex (bufferbmp, font, 0, 0, makecol (255,255,255), -1,
		 "Scroll Window Position:");
  textprintf_ex (bufferbmp, font, 0, 10, makecol (255,255,255), -1,
		 "tl = (%d,%d)", scrollx, scrolly);
  textprintf_ex (bufferbmp, font, 0, 20, makecol (255,255,255), -1,
		 "center = (%d,%d)", scrollx+WIDTH/2, scrolly+HEIGHT/2);
}

void print_player_debug_messages (void) {
  textprintf_ex (bufferbmp, font, 200, 0, makecol (255,255,255), -1,
		 "Player Position:");
  textprintf_ex (bufferbmp, font, 200, 10, makecol (255,255,255), -1,
		 "tl = (%d,%d)", hero->player->x, hero->player->y);
}
