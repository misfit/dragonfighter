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


int main (void) {
  int currentframe = 0;
  int framedelay = 15;
  int maxframe = 1;
  
  initialize_game(24);
  setup_hero();
  
  /**** Create virtual background ****/
  scroll = create_bitmap(MAPW, MAPH);
  tiles = load_bitmap("maptiles.bmp", NULL);
  for (tiley = 0; tiley < scroll->h; tiley+=TILEH){
    for (tilex = 0; tilex < scroll->w; tilex+=TILEW){
      draw_frame(tiles,scroll,tilex,tiley,TILEW,TILEH,0,0,COLS,map[n++]);
    }
  }
  destroy_bitmap(tiles);

  /**** main loop ****/
  while (!key[KEY_ESC]){
    if (key[KEY_DOWN]){
      hero->facing = DOWN;
      hero->y += 1;
    } else if (key[KEY_UP]){
      hero->facing = UP;
      hero->y -= 1;
    } else if (key[KEY_RIGHT]){
      hero->facing = RIGHT;
      hero->x += 1;
    } else if (key[KEY_LEFT]){
      hero->facing = LEFT;
      hero->x -= 1;
    }

    /* draw scroll window */
    acquire_screen();
    blit(scroll, screen, hero->x, hero->y, 0, 0, WIDTH-1, HEIGHT-1);
    release_screen();

    switch (hero->facing) {
    case DOWN:
      /**** Move the hero down on the screen ****/
      
      /**** draw the sprite at the new location. ****/
      if (hero->framecount++ > framedelay){
	/* 
	 * Increment the current animation frame, if it is greater than the
	 * maximum frames for animation, then reset the current frame to 0.
	 */
	hero->framecount = 0;
	currentframe++;
	if (currentframe > maxframe){ currentframe = 0; }
      }
      acquire_screen();
      stretch_sprite(screen, hero_down_images[currentframe], hero->x, hero->y,
		     32, 32);
      break;

    case UP:
      /**** Move the hero up on the screen ****/
      if (hero->framecount++ > framedelay){
	hero->framecount = 0;
	currentframe++;
	if (currentframe > maxframe){ currentframe = 0; }
      }
      acquire_screen();
      stretch_sprite(screen, hero_up_images[currentframe], hero->x, hero->y,
		     32, 32);
      break;

    case RIGHT:
      /**** Move the hero right on the screen ****/
      if (hero->framecount++ > framedelay){
	hero->framecount = 0;
	currentframe++;
	if (currentframe > maxframe){ currentframe = 0; }
      }
      acquire_screen();
      stretch_sprite(screen, hero_right_images[currentframe], hero->x,hero->y, 
		     32, 32);
      break;

    case LEFT:
    /**** Move the hero left on the screen ****/
      if (hero->framecount++ > framedelay){
        hero->framecount = 0;
        currentframe++;
        if (currentframe > maxframe){ currentframe = 0; }
      }
      acquire_screen();
      stretch_sprite(screen, hero_left_images[currentframe], hero->x, hero->y,
		     32, 32);
      break;
    }

    release_screen();
    rest(10);
  }
  /**** Cleanup ****/
  for (n=0; n < 2; n++){
    destroy_bitmap(hero_down_images[n]);
    destroy_bitmap(hero_up_images[n]);
    destroy_bitmap(hero_right_images[n]);
    destroy_bitmap(hero_left_images[n]);
  }
  destroy_bitmap(scroll);
  allegro_exit();
  return 0;
}
END_OF_MAIN()


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
