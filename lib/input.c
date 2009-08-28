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

int get_input (void) {
  int gameover = 0;
  if (key[KEY_ESC]) gameover = 1;
  if (key[KEY_DOWN]){
    hero->yspeed = 1;
    hero->facing = DOWN;
    hero->y += hero->yspeed;
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
  return gameover;
}
