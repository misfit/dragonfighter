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
  currentmap->unlocked = 0;
  currentmap->pointofentry = 0;
  currentmap->pointofexit = 0;
  currentmap->initflag = 1;
  currentmap->idnumber = TCA_LA;
    
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



void setup_player (void) {
  player = (SPRITE*)malloc (sizeof (SPRITE));
  /* center the player in the scroll window facing down, unmoving */
  player->x = TCA1startx;
  player->y = TCA1starty;
  player->direction = DOWN;
  player->width = 32;
  player->height = 32;
  player->xspeed = 0;
  player->yspeed = 0;
  player->curframe = 0;
  player->maxframe = 1;
  player->framecount = 0;
  player->framedelay = 8;
}

void draw_player (void) {
  switch (player->direction) {
  case DOWN:
    draw_sprite (scrollbmp, playerdnbmp[player->curframe],
		 player->x, player->y);
    break;

  case UP:
    draw_sprite (scrollbmp, playerupbmp[player->curframe],
		 player->x, player->y);
    break;

  case LEFT:
    draw_sprite (scrollbmp, playerltbmp[player->curframe],
		 player->x, player->y);
    break;

  case RIGHT:
    draw_sprite (scrollbmp, playerrtbmp[player->curframe],
		 player->x, player->y);
    break;
  }
}

void animate_player (void) {
  /* prevent animation if the sprite is not moving. */
  if (player->xspeed != 0 || player->yspeed != 0) {
    
    /* animate the sprite */
    if (player->framecount++ > player->framedelay) {
      player->framecount = 0;
      player->curframe++;
      if (player->curframe > player->maxframe) player->curframe = 0;
    }
  }
}

void move_player (void) {
  switch (player->direction) {
  case DOWN:
    if (player->y < scrollbmp->h-32) player->y += player->yspeed;
    break;

  case UP:
    if (player->y > scrolly) player->y += player->yspeed;
    break;

  case LEFT:
    if (player->x > scrollx) player->x += player->xspeed;
    break;

  case RIGHT:
    if (player->x < scrollbmp->w-32) player->x += player->xspeed;
    break;
  }
}

void scroll_window (void) {
  switch (player->direction) {
  case RIGHT:
    /* limits the bounds of the scroll window to the current map. */
    scrollx += player->xspeed;
    if (scrollx > scrollbmp->w-WIDTH) scrollx = scrollbmp->w - WIDTH;
    break;

  case LEFT:
    /* limits the bounds of the scroll window to the current map. */
    scrollx += player->xspeed;
    if (scrollx < 0) scrollx = 0;
    break;

  case UP:
    /* limits the bounds of the scroll window to the current map. */
    scrolly += player->yspeed;
    if (scrolly < 0) scrolly = 0;
    break;

  case DOWN:
    /* limits the bounds of the scroll window to the current map. */
    scrolly += player->yspeed;
    if (scrolly > scrollbmp->h-HEIGHT) scrolly = scrollbmp->h - HEIGHT;
    break;
  }
}

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
		 "tl = (%d,%d)", player->x, player->y);
  textprintf_ex (bufferbmp, font, 200, 20, makecol (255,255,255), -1,
		 "speed = (%d,%d)", player->xspeed, player->yspeed);
}
