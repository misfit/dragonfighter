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
  gamestate = 0;

  initialize_game(24);
  setup_hero();
  setup_tantagel_castle();

  /**** main loop ****/
  while (!gameover) {
    if (gamestate == 0){
      if (keypressed()) gameover = get_input(throneroom);
    }
    /* draw scroll window */
    acquire_screen();
    blit(scroll, screen, hero->x, hero->y, 0, 0, WIDTH-1, HEIGHT-1);
    release_screen();
    
    animate_hero();
    move_hero();
    
    rest(10);
  }
  cleanup_hero();
  cleanup();
  return 0;
}
END_OF_MAIN()
