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

int main (void) {
  int gameover = 0;
  initialize_game(24);
  setup_hero();
  draw_throneroom_map();

  /**** main loop ****/
  while (!gameover) {
    if (keypressed()) gameover = get_input();

    /* draw scroll window */
    acquire_screen();
    blit(scroll, screen, hero->x, hero->y, 0, 0, WIDTH-1, HEIGHT-1);
    release_screen();
    
    animate_hero();
    move_hero();
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
