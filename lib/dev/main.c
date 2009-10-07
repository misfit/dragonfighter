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
  
  tcala = (MAP*)malloc (sizeof (MAP));
  tcala->unlocked = 0;
  tcala->pointofentry = 0;
  tcala->pointofexit = 0;
  tcala->initflag = 1;
  tcala->idnumber = TCA_LA;
  
  /* point global currentmap variable at the current map. */
  currentmap = tcala;
  
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

void setup_allegro (int mode, int screenw, int screenh, int cdepth) {
  allegro_init();
  install_keyboard();
  install_timer();
  srand (time (NULL));
  set_color_depth (cdepth);
  set_gfx_mode (mode, screenw, screenh, 0, 0);
}

void setup_bmps (void) {
  int i;
  BITMAP *tempbmp;

  bufferbmp = create_bitmap (WIDTH, HEIGHT);
  tilesbmp = load_bitmap ("maptiles.bmp", NULL);

  /* load bitmaps for the player animations */
  tempbmp = load_bitmap ("chars.bmp", NULL);
  for (i = 0; i < 2; i++) {
    playerdnbmp[i] = grab_frame (tempbmp, 32, 32, 0, 0, 32, i);
    playerupbmp[i] = grab_frame (tempbmp, 32, 32, 0, 0, 32, i+2);
    playerrtbmp[i] = grab_frame (tempbmp, 32, 32, 0, 0, 32, i+4);
    playerltbmp[i] = grab_frame (tempbmp, 32, 32, 0, 0, 32, i+6);
  }
  destroy_bitmap (tempbmp);
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

BITMAP *grab_frame (BITMAP *source, int width, int height, int startx,
		    int starty, int columns, int frame) {
  BITMAP *tempbmp = create_bitmap (width, height);
  int x = startx + (frame%columns)*width;
  int y = starty + (frame/columns)*height;
  blit (source, tempbmp, x, y, 0, 0, width, height);
  return tempbmp;
}

void get_input (void) {
  if (key[KEY_RIGHT]) {
    player->direction = RIGHT;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2){
      player->xspeed = PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->xspeed = NORM_SPEED;
    
  } else if (key[KEY_LEFT]) {
    player->direction = LEFT;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2) {
      player->xspeed = -PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->xspeed = -NORM_SPEED;
    
  } else if (key[KEY_DOWN]) {
    player->direction = DOWN;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2) {
      player->yspeed = PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->yspeed = NORM_SPEED;
    
  } else if (key[KEY_UP]) {
    player->direction = UP;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2) {
      player->yspeed = -PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->yspeed = -NORM_SPEED;
    
  } else {
    player->xspeed = 0;
    player->yspeed = 0;
  }
}

void draw_map (int map[]) {
  int i = 0;

  for (tiley = 0; tiley < scrollbmp->h; tiley += TILEH) {
    for (tilex = 0; tilex < scrollbmp->w; tilex += TILEW) {
      draw_frame (tilesbmp, scrollbmp, tilex, tiley, TILEW, TILEH, 0, 0,
                  COLS, map[i++]);
    }
  }
}

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

void map_event_handler (void) {
  switch (currentmap->idnumber) {
  case TCA_LA:
    /* unlock the door in the room */
    if (player->x == TCA2startx && player->y == TCA2starty) {
      currentmap->idnumber = TCA_UA;
      currentmap->initflag = 0;
      currentmap->pointofentry = 0;
    }
    break;

  case TCA_UA:
    /* Send player to the courtyard when he goes to the stairs */
    if (player->x == TCA3startx+32 && player->y == TCA3starty) {
      currentmap->idnumber = TCB_LALB;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    }
    break;

  case TCB_LALB:
    /* send player back to the unlocked throneroom */
    if (player->x == TCB1startx-32 && player->y == TCB1starty) {
      currentmap->idnumber = TCA_UA;
      currentmap->initflag = 1;
      currentmap->pointofentry = 1;

    } else if (player->x == 960 && player->y == 960) {
      currentmap->idnumber = TCC;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    
    } else if ((player->x == 352 || player->x == 384) && player->y == 992) {
      currentmap->idnumber = ALEFGARD1;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
      
    }
    break;

  case TCC:
    if (player->x == 160 && player->y == 224) {
      currentmap->idnumber = TCB_LALB;
      currentmap->initflag = 1;
      currentmap->pointofentry = 2;
    }
    break;
  } /* end switch idnumber */
}

void map_handler (void) {
  /* find out which map to draw */
  switch (currentmap->idnumber) {
  case TCA_LA:
    /* only one possible case for entry */
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (TCAW, TCAH);
      currentmap->initflag = 0;
    }
    draw_map (TCALA);
    break;

  case TCA_UA:
    switch (currentmap->pointofentry) {
    case 0:
      /* door was just unlocked */
      if (currentmap->initflag == 1) {
	currentmap->initflag = 0;
      }
      draw_map (TCAUA);
      break;
      
    case 1:
      /* has entered from the courtyard */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCAW, TCAH);
	player->x = TCA3startx;
	player->y = TCA3starty;
	currentmap->initflag = 0;
      }
      draw_map (TCAUA);
      break;
    }
    break;

  case TCB_LALB:
    switch (currentmap->pointofentry) {
    case 0:
      /* player has entered from the throneroom */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCBW, TCBH);
	player->x = TCB1startx;
	player->y = TCB1starty;
	currentmap->initflag = 0;
      }
      draw_map (TCBLALB);
      break;

    case 2:
      /* player has entered from the basement */
      if (currentmap->initflag == 1) {

	scrollbmp = create_bitmap (TCBW, TCBH);
	player->x = TCB3startx;
	player->y = TCB3starty;
	scrollx = 384;
	scrolly = 544;
	currentmap->initflag = 0;
      }
      draw_map (TCBLALB);
      break;
    }
    break;

  case TCC:
    /* only one possible case for entry */
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (TCCW, TCCH);
      clear (scrollbmp);
      player->x = TCCstartx;
      player->y = TCCstarty;
      scrollx = 0;
      scrolly = 0;
      currentmap->initflag = 0;
    }
    draw_map (TCC_L1);
    break;

  case ALEFGARD1:
    /* player coming from Tantagel Castle */
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (ALEFGARDW, ALEFGARDH);
      clear (scrollbmp);
      player->x = ALEFGARDTCstartx;
      player->y = ALEFGARDTCstarty;
      scrollx = 1300;
      scrolly = 1300;
      currentmap->initflag = 0;
    }
    draw_map (ALEFGARD);
    break;

  case ALEFGARD2:
    break;
  } /* end switch idnumber */
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
