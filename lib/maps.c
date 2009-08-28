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

void draw_throneroom_map (void) {
  /**** Create virtual background ****/
  scroll = create_bitmap(MAPW, MAPH);
  tiles = load_bitmap("maptiles.bmp", NULL);
  for (tiley = 0; tiley < scroll->h; tiley+=TILEH){
    for (tilex = 0; tilex < scroll->w; tilex+=TILEW){
      draw_frame(tiles,scroll,tilex,tiley,TILEW,TILEH,0,0,COLS,map[n++]);
    }
  }
  destroy_bitmap(tiles);
}
