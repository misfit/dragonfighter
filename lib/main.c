/****
 * Copyright (C) Brian Moriya
 * brian.moriya@gmail.com
 *
 * This file is part of Dragon Fighter.
 * 
 * Dragon Fighter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dragon Fighter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dragon Fighter.  If not, see <http://www.gnu.org/licenses/>.
 ****/

#include "dragonfighter.h"

void initialize_game (int colordepth) {
  allegro_init();
  install_keyboard();
  install_timer();
  set_color_depth(colordepth);
  set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
  srand(time(NULL));
  
  scroll = create_bitmap(mapw, maph);
  clear(scroll);
}

void setup_hero (void) {
  int i;
  /**** load character bitmaps. ****/
  tempbitmap = load_bitmap("characters.bmp", NULL);
  for (i = 0; i < 2; i++){
    hero_down_images[i] = grab_frame(tempbitmap,16,16,0,0,16,i);
  }
  for (i = 2; i < 4; i++){
    hero_up_images[i-2] = grab_frame(tempbitmap,16,16,0,0,16,i);
  }
  for (i = 4; i < 6; i++){
    hero_right_images[i-4] = grab_frame(tempbitmap,16,16,0,0,16,i);
  }
  for (i = 6; i < 8; i++){
    hero_left_images[i-6] = grab_frame(tempbitmap,16,16,0,0,16,i);
  }
  destroy_bitmap(tempbitmap);
  hero = (HERO*) malloc (sizeof (HERO));
  hero->facing = LEFT;
  hero->x = 160;
  hero->y = 128;
  hero->framecount = 0;
  hero->currentframe = 0;
  hero->framedelay = 15;
  hero->maxframe = 1;
  hero->xspeed = 0;
  hero->yspeed = 0;
  hero->currentlocation = LTR;
}

void cleanup_hero (void) {
  for (n=0; n < 2; n++){
    destroy_bitmap(hero_down_images[n]);
    destroy_bitmap(hero_up_images[n]);
    destroy_bitmap(hero_right_images[n]);
    destroy_bitmap(hero_left_images[n]);
  }
  free (hero);
}

void cleanup_locked_throneroom (void) {
  if (l0throneroom->nowalkshead != NULL){
    NOWALKNODE *temp;
    temp = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
    
    while (temp->next != NULL) {
      temp = l0throneroom->nowalkshead;
      l0throneroom->nowalkshead = l0throneroom->nowalkshead->next;
      free (temp->block);
      free (temp);
    }
  }
  free (l0throneroom);
}

void cleanup_unlocked_throneroom (void) {
  if (u0throneroom->nowalkshead != NULL){
    NOWALKNODE *temp;
    temp = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
    
    while (temp->next != NULL) {
      temp = u0throneroom->nowalkshead;
      u0throneroom->nowalkshead = u0throneroom->nowalkshead->next;
      free (temp->block);
      free (temp);
    }
  }
  free (u0throneroom);
}

void cleanup_l1l2tantagel_castle (void) {
  if (l1l2tantagel_courtyard->nowalkshead != NULL){
    NOWALKNODE *temp;
    temp = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
    
    while (temp->next != NULL) {
      temp = l1l2tantagel_courtyard->nowalkshead;
      l1l2tantagel_courtyard->nowalkshead = \
	l1l2tantagel_courtyard->nowalkshead->next;
      free (temp->block);
      free (temp);
    }
  }
  free (l1l2tantagel_courtyard);

}

BITMAP *grab_frame (BITMAP *source, int width, int height,
		   int startx, int starty, int columns, int frame) {
  BITMAP *tempbitmap = create_bitmap(width, height);
  int x = startx + (frame % columns)*width;
  int y = starty + (frame/columns)*height;
  blit(source, tempbitmap, x, y, 0, 0, width, height);
  return tempbitmap;
}

void draw_frame (BITMAP *source, BITMAP *dest, int x, int y, int width,
		int height, int startx, int starty, int columns, int frame) {
  /* Calculate frame position. */
  int framex = startx + (frame%columns)*width;
  int framey = starty + (frame/columns)*height;
  /* Draw frame to destination bitmap. */
  masked_blit(source,dest,framex,framey,x,y,width,height);
}

void cleanup (void) {
  destroy_bitmap (scroll);
  allegro_exit();
}

int is_inside (int x, int y, int left, int top, int right, int bottom) {
  if (x > left && x < right && y > top && y < bottom) return 1;
  else return 0;
}

unsigned char get_input (PLACE *place) {
  /****
   * Returns 1 for game over.
   * Returns 0 for keep going.
   * Returns > 1 to indicate a new map is to be drawn.
   ****/
  int oldpx = hero->x;
  int oldpy = hero->y;
  int is_collision = 0;

  if (key[KEY_ESC]) return 1;
  
  is_collision = check_collision (place);
  if (is_collision == 1){
    hero->x = oldpx;
    hero->y = oldpy;
    if (hero->facing == DOWN){
      if (key[KEY_UP]){
	hero->facing = UP;
	hero->yspeed = 1;
	hero->y -= hero->yspeed;
      } else if (key[KEY_RIGHT]){ hero->y = oldpy-1;
      } else if (key[KEY_LEFT]){ hero->y = oldpy-1;
      }
    } 
    if (hero->facing == RIGHT){
      if (key[KEY_LEFT]){
	hero->facing = LEFT;
	hero->xspeed = 1;
	hero->x -= hero->xspeed;
      } else if (key[KEY_UP]){ hero->x = oldpx-1;
      } else if (key[KEY_DOWN]){ hero->x = oldpx-1;
      }
    }
    if (hero->facing == LEFT){
      if (key[KEY_RIGHT]){
	hero->facing = RIGHT;
	hero->xspeed = 1;
	hero->x += hero->xspeed;
      } else if (key[KEY_UP]){ hero->x = oldpx+1; 
      } else if (key[KEY_DOWN]){ hero->x = oldpx+1;
      }
    }
    if (hero->facing == UP){
      if (key[KEY_DOWN]){
	hero->facing = DOWN;
	hero->yspeed = 1;
	hero->y += hero->yspeed;
      } else if (key[KEY_RIGHT]){ hero->y = oldpy + 1;
      } else if (key[KEY_LEFT]){ hero->y = oldpy + 1;
      }
    }
    return 0;
    /* If the hero is at a door he can also open it. */
  } else if (is_collision == 2){
    if (key[KEY_X]){
      if (place == l0throneroom) {return 2;}
    }
  
  } else if (is_collision == 3) {
    if (key[KEY_X]){
      if (place == u0throneroom) {return 3;}
    }
  }  else {
    hero->yspeed = 1;
    hero->xspeed = 1;
    if (key[KEY_DOWN]){
      hero->facing = DOWN;
      hero->y += hero->yspeed;
    } else if (key[KEY_UP]){
      hero->facing = UP;
      hero->y -= hero->yspeed;
    } else if (key[KEY_RIGHT]){
      hero->facing = RIGHT;
      hero->x += hero->xspeed;
    } else if (key[KEY_LEFT]){
      hero->facing = LEFT;
      hero->x -= hero->xspeed;
    }
  }
  return 0;
}

void animate_hero (void) {
  if (hero->framecount++ > hero->framedelay){
    hero->framecount = 0;
    hero->currentframe++;
    if (hero->currentframe > hero->maxframe){ hero->currentframe = 0; }
  }
}

void move_hero (void) {
  switch (hero->facing) {
  case DOWN:
    if (hero->y > scroll->h - HEIGHT) hero->y = scroll->h - HEIGHT;
    acquire_screen();
    stretch_sprite(screen, hero_down_images[hero->currentframe], hero->x, 
		   hero->y, 32, 32);
    break;
    
  case UP:
    if (hero->y < 0) hero->y = 0;
    acquire_screen();
    stretch_sprite(screen, hero_up_images[hero->currentframe], hero->x, 
		   hero->y, 32, 32);
    break;
    
  case RIGHT:
    if (hero->x> scroll->w - WIDTH) hero->x = scroll->w - WIDTH;
    acquire_screen();
    stretch_sprite(screen, hero_right_images[hero->currentframe], hero->x,
		   hero->y, 32, 32);
    break;
    
  case LEFT:
    if (hero->x < 0) hero->x = 0;
    acquire_screen();
    stretch_sprite(screen, hero_left_images[hero->currentframe], hero->x, 
		   hero->y, 32, 32);
    break;
  }
  release_screen();  
}

int check_collision (PLACE *place) {
  int is_collision;
  NOWALKNODE *temp;
  temp = place->nowalkshead;
  while (temp != NULL && is_collision != 1){
    if ((is_collision = is_inside (hero->x*2, hero->y*2, temp->block->left, 
				  temp->block->top, temp->block->right,
				   temp->block->bottom)) == 1){
      if (temp->type == DOOR) {return 2;}
      else if (temp->type == STAIRSDOWNL) {return 3;}
      else {return 1;}
    }
    else {temp = temp->next;}
  }
  return 0;
}

void add_nowalk (PLACE *place, NOWALKNODE *newnode) {
  if (place->nowalkshead == NULL){
    newnode->next = NULL;
    place->nowalkshead = newnode;
  } else if (place->nowalkshead != NULL){
    newnode->next = place->nowalkshead;
    place->nowalkshead = newnode;
  }
}

BLOCK *create_new_block (void) {
  BLOCK *newblk;
  newblk = (BLOCK*) malloc (sizeof (BLOCK));
  newblk->height = 32;
  newblk->width = 32;
  newblk->left = tilex - newblk->width;
  newblk->top = tiley - newblk->height;
  newblk->right = tilex + newblk->width;
  newblk->bottom = tiley + newblk->height;
  return newblk;
}

void draw_locked_throneroom (void) {
  int n = 0;
  tiles = load_bitmap("maptiles.bmp", NULL);

  for (tiley = 0; tiley < scroll->h; tiley+=TILEH){
    for (tilex = 0; tilex < scroll->w; tilex+=TILEW){
      if (throneroommap0[n] == DOOR || 
	  throneroommap0[n] == STONE ||
	  throneroommap0[n] == COUNTER ||
	  throneroommap0[n] == STAIRSDOWNL){
	NOWALKNODE *newnwn;
	newnwn = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
	if (throneroommap0[n] == DOOR){
	  newnwn->id = DR1;
	  newnwn->type = DOOR;
	}
	if (throneroommap0[n] == STONE) {newnwn->type = STONE;}
	if (throneroommap0[n] == COUNTER) {newnwn->type = COUNTER;}
	if (throneroommap0[n] == STAIRSDOWNL) {newnwn->type = STAIRSDOWNL;}
	newnwn->block = create_new_block();
	add_nowalk (l0throneroom, newnwn);
      }
      draw_frame(tiles,scroll,tilex,tiley,TILEW,TILEH,0,0,COLS,
		 throneroommap0[n++]);
    }
  }
  destroy_bitmap(tiles);
}

void draw_unlocked_throneroom (void) {
  int n = 0;
  tiles = load_bitmap("maptiles.bmp", NULL);

  for (tiley = 0; tiley < scroll->h; tiley+=TILEH){
    for (tilex = 0; tilex < scroll->w; tilex+=TILEW){
      if (throneroommap[n] == STONE ||
	  throneroommap[n] == COUNTER ||
	  throneroommap[n] == STAIRSDOWNL){
	NOWALKNODE *newnwn;
	newnwn = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
	if (throneroommap[n] == STONE) {newnwn->type = STONE;}
	if (throneroommap[n] == COUNTER) {newnwn->type = COUNTER;}
	if (throneroommap[n] == STAIRSDOWNL) {newnwn->type = STAIRSDOWNL;}
	newnwn->block = create_new_block();
	newnwn->id = 0;
	add_nowalk (u0throneroom, newnwn);
      }
      draw_frame(tiles,scroll,tilex,tiley,TILEW,TILEH,0,0,COLS,
		 throneroommap[n++]);
    }
  }
  destroy_bitmap (tiles); 
}

void draw_tantagel_courtyard (void) {
  int n = 0;
  tiles = load_bitmap("maptiles.bmp", NULL);
  destroy_bitmap (scroll);
  mapw = TCYACROSS*TILEW;
  maph = TCYDOWN*TILEH;
  scroll = create_bitmap (mapw, maph);
  clear (scroll);
  for (tiley = 0; tiley < scroll->h; tiley+=TILEH){
    for (tilex = 0; tilex < scroll->w; tilex+=TILEW){
      if (tantagelcourtyard12[n] == STONE ||
	  tantagelcourtyard12[n] == COUNTER || 
	  tantagelcourtyard12[n] == DOOR ||
	  tantagelcourtyard12[n] == WATER ||
	  tantagelcourtyard12[n] == STAIRSUPL ||
	  tantagelcourtyard12[n] == STAIRSDOWNL) {
	NOWALKNODE *newnwn;
	newnwn = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
	if (tantagelcourtyard12[n] == STONE) {newnwn->type = STONE;}
	if (tantagelcourtyard12[n] == COUNTER) {newnwn->type = COUNTER;}
	if (tantagelcourtyard12[n] == STAIRSUPL) {newnwn->type = STAIRSUPL;}
	if (tantagelcourtyard12[n] == STAIRSDOWNL) newnwn->type = STAIRSDOWNL;
	if (tantagelcourtyard12[n] == DOOR) {
	  newnwn->type = DOOR;
	  if (n == 244) newnwn->id = DR2;
	  if (n == 454) newnwn->id = DR3;
	}
	newnwn->block = create_new_block();
	add_nowalk (l1l2tantagel_courtyard, newnwn);
      }
      draw_frame(tiles,scroll,tilex,tiley,TILEW,TILEH,0,0,COLS,
                 tantagelcourtyard12[n++]);
    }
  }
  destroy_bitmap (tiles);
}

PLACE *load_map (const unsigned char curlocation) {
  switch (curlocation) {
  case LTR:
    l0throneroom = (PLACE*) malloc (sizeof (PLACE));
    l0throneroom->nowalkshead = NULL;
    draw_locked_throneroom();
    return l0throneroom;

  case UTR:
    u0throneroom = (PLACE*) malloc (sizeof (PLACE));
    u0throneroom->nowalkshead = NULL;
    draw_unlocked_throneroom();
    return u0throneroom;

  case TCY:
    l1l2tantagel_courtyard = (PLACE*) malloc (sizeof (PLACE));
    l1l2tantagel_courtyard->nowalkshead = NULL;
    draw_tantagel_courtyard();
    return l1l2tantagel_courtyard;
  }
}

int main (void) {
  PLACE *current;
  gamestate = TEST;
  initialize_game(24);
  setup_hero();
  current = load_map (LTR);

  /**** main loop ****/
  while (1) {
    if (gamestate == ROAMING){
      if (get_input (current) == 1) gamestate = GAMEOVER;
      
      else gamestate = ROAMING;
      blit(scroll, screen, hero->x, hero->y, 0, 0, WIDTH-1, HEIGHT-1);
      animate_hero();
      move_hero();
      rest(10);
      
    } else if (gamestate == GAMEOVER){
      if (current == l0throneroom) {cleanup_locked_throneroom();}
      else if (current = u0throneroom) {cleanup_unlocked_throneroom();}
      else if (current = l1l2tantagel_courtyard) cleanup_l1l2tantagel_castle();
      cleanup_hero();
      destroy_bitmap (scroll);
      allegro_exit();
      return 0;
      
    } else if (gamestate == TEST) {
      switch (get_input (current)) {
      case 0:
	break;
	
      case 1:
	gamestate = GAMEOVER;
	break;
	
      case 2:
	cleanup_locked_throneroom();
	current = load_map (UTR);
	break;

      case 3:
	cleanup_unlocked_throneroom();
	hero->x = (9*32)/2;
	hero->y = (8*32)/2;
	current = load_map (TCY);
	break;
      }
      blit(scroll, screen, hero->x, hero->y, 0, 0, WIDTH-1, HEIGHT-1);
      animate_hero();
      move_hero();
      rest(10);
    }
  } /* end of while 1 */
}
END_OF_MAIN()
