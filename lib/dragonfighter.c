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
#include "maps.h"

void initialize_game (int colordepth) {
  allegro_init();
  install_keyboard();
  install_timer();
  set_color_depth(colordepth);
  set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
  srand(time(NULL));
  scrollx = 160;
  scrolly = 128;
  scroll = create_bitmap(MAPW, MAPH);
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
  hero = malloc(sizeof(SPRITE));
  hero->facing = LEFT;
  hero->x = 160;
  hero->y = 128;
  hero->framecount = 0;
  hero->currentframe = 0;
  hero->framedelay = 15;
  hero->maxframe = 1;
  hero->xspeed = 0;
  hero->yspeed = 0;
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
  for (n=0; n < 2; n++){
    destroy_bitmap(hero_down_images[n]);
    destroy_bitmap(hero_up_images[n]);
    destroy_bitmap(hero_right_images[n]);
    destroy_bitmap(hero_left_images[n]);
  }
  destroy_bitmap (scroll);
  free (hero);
  for (n=0; n < 1; n++)
    free (lockeddoors[n]);
  allegro_exit();
}

int is_inside (int x, int y, int left, int top, int right, int bottom) {
  if (x > left && x < right && y > top && y < bottom) return 1;
  else return 0;
}

int get_input (void) {
  int gameover = 0;
  int oldpx = hero->x;
  int oldpy = hero->y;

  if (key[KEY_ESC]) return gameover = 1;

  if (is_inside (hero->x*2, hero->y*2, 
		 lockeddoors[0]->left, lockeddoors[0]->top,
		 lockeddoors[0]->right, lockeddoors[0]->bottom) == 1){
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
      } else if (key[KEY_UP] || key[KEY_DOWN]){ hero->x = oldpx-1;
      } else if (key[KEY_DOWN]){ hero->x = oldpx-1;
      }
    }
    if (hero->facing == LEFT){
      if (key[KEY_RIGHT]){
	hero->facing = RIGHT;
	hero->xspeed = 1;
	hero->x += hero->xspeed;
      }
    }
    if (hero->facing == UP){
      if (key[KEY_DOWN]){
	hero->facing = DOWN;
	hero->yspeed = 1;
	hero->y += hero->yspeed;
      }
    }
  } else {
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
  return gameover;
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

void draw_throneroom_map (void) {
  tiles = load_bitmap("maptiles.bmp", NULL);
  for (tiley = 0; tiley < scroll->h; tiley+=TILEH){
    for (tilex = 0; tilex < scroll->w; tilex+=TILEW){
      if (throneroommap[n] == DOOR){
	lockeddoors[0] = malloc(sizeof(BLOCK));
	lockeddoors[0]->height = 32;
	lockeddoors[0]->width = 32;
	lockeddoors[0]->left = tilex - lockeddoors[0]->width;
	lockeddoors[0]->top = tiley - lockeddoors[0]->height;
	lockeddoors[0]->right = tilex + lockeddoors[0]->width;
	lockeddoors[0]->bottom = tiley + lockeddoors[0]->height;
      }
      draw_frame(tiles,scroll,tilex,tiley,TILEW,TILEH,0,0,COLS,
		 throneroommap[n++]);
     }
  }
  destroy_bitmap(tiles);
}
