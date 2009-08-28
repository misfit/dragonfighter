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
  destroy_bitmap(scroll);
  allegro_exit();
}

int is_inside (int x, int y, int left, int top, int right, int bottom) {
  if (x > left && x < right && y > top && y < bottom) return 1;
  else return 0;
}
