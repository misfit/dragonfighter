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
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 512
#define HEIGHT 480
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
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
  int facing;
}SPRITE;

typedef struct BLOCK {
  int left;
  int top;
  int right;
  int bottom;
  int width, height;
}BLOCK;

/**** Character bitmaps and sprites ****/

SPRITE *hero;

#define UNWALKABLES 54
BLOCK *unwalkables[UNWALKABLES];

BITMAP *hero_left_images[2];
BITMAP *hero_right_images[2];
BITMAP *hero_up_images[2];
BITMAP *hero_down_images[2];
BITMAP *tempbitmap;
BITMAP *scroll;
BITMAP *tiles;

int n; /* Index variable for looping. */

/* Position variables for laying tiles */
int tilex, tiley;
int scrollx, scrolly;


/**** Function prototypes ****/

void initialize_game (int colordepth);

void setup_hero (void);

BITMAP *grab_frame (BITMAP *source, int width, int height,
		   int startx, int starty, int columns, int frame);

void draw_frame (BITMAP *source, BITMAP *dest, int x, int y, int width,
		int height, int startx, int starty, int columns, int frame);

void cleanup (void);

int is_inside (int x, int y, int left, int top, int right, int bottom);

int get_input (void);

void animate_hero (void);

void move_hero (void);

void draw_locked_throneroom_map (void);

#endif
