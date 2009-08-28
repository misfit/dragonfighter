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

#ifndef _DRAGONFIGHTER_H
#define _DRAGONFIGHTER_H

#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>

#define GAMENAME "Dragon Fighter"

#define GAMENAME "Dragon Fighter"
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 512
#define HEIGHT 480
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define FWD 1
#define BWD -1
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
/**** For map drawing ****/
#define TILEW 32
#define TILEH 32
#define COLS 10
#define MAP_ACROSS 24
#define MAP_DOWN 24
#define MAPW MAP_ACROSS*TILEW
#define MAPH MAP_DOWN*TILEH


/**** Global structs and variables ****/

typedef struct SPRITE {
  int x, y;
  int width, height;
  int xspeed, yspeed;
  int xdelay, ydelay;
  int xcount, ycount;
  int currentframe;
  int maxframe;
  int animdirection;
  int framecount;
  int framedelay;
}SPRITE;

/**** Character bitmaps and sprites ****/

SPRITE thehero;
SPRITE *hero;
BITMAP *hero_left_images[2];
BITMAP *hero_right_images[2];
BITMAP *hero_up_images[2];
BITMAP *hero_down_images[2];
BITMAP *tempbitmap;
BITMAP *scroll;
BITMAP *tiles;

int n; /* Index variable for looping. */

/* Position variables. */
int tilex, tiley;

/**** Function prototypes ****/

BITMAP *grab_frame (BITMAP *source, int width, int height,
		   int startx, int starty, int columns, int frame);
/****
 * Function to grab a single frame out of a spritesheet image.
 ****/

void draw_frame (BITMAP *source, BITMAP *dest, int x, int y, int width,
		int height, int startx, int starty, int columns, int frame);
/****
 * Same as the grab frame function except it draws the bitmap directly.
 ****/

void initialize_game(int colordepth);
/****
 * Initializes allegro stuff.
 ****/

#endif
