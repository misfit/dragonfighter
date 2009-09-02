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

#define GAMEOVER 0
#define ROAMING 1
#define TEST 2

int main (void) {
  gamestate = ROAMING;
  initialize_game(24);
  setup_locked_throneroom();
  setup_hero();
  /*  setup_tantagel_castle(); */

  /**** main loop ****/
  while (1) {
    if (gamestate == ROAMING){
      if (keypressed()) {
	if (key[KEY_ESC]) gamestate = GAMEOVER;
	
	blit(scroll, screen, hero->x, hero->y, 0, 0, WIDTH-1, HEIGHT-1);
	animate_hero();
	move_hero();
	rest(10);
      }
      
    } else if (gamestate == GAMEOVER){
      cleanup_locked_throneroom();
      cleanup_hero();
      destroy_bitmap (scroll);
      allegro_exit();
      return 0;
      
    } else if (gamestate == TEST) {
      clear_bitmap(screen);
      cleanup_hero();
      rest(1000);
      setup_hero();
      gamestate = ROAMING;
    }
  } /* end of while 1 */
}
END_OF_MAIN()
