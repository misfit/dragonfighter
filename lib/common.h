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

#ifndef _COMMON_H
#define _COMMON_H

#include <stdlib.h>
#include <allegro.h>

#define MODE GFX_AUTODETECT_WINDOWED /* for set_gfx_mode call */
#define WIDTH 768 /* total width of the game window */
#define HEIGHT 720 /* total height of the game window */

/**** constants relating to the player character ****/
#define MAXSPEED 4 /* Normal speed the player walks at */
#define HILLSPEED 2 /* Speed over rough terrain */

/**** map constants ****/
#define TILEW 32 /* Width of the tiles used for the map */
#define TILEH 32 /* Height of the tiles used for the map */
#define TILES 13 /* How many tiles are on the spritesheet */
#define COLS 10  /* How many columns of tiles are on the spritesheet */
/* Correspond to position on the spritesheet and in the map array */
#define COUNTER 0
#define BRICK 1
#define STONE 2
#define GRASS 3
#define ROOF 4
#define BARRIER 5
#define WATER 6
#define STAIRSDOWNR 8
#define CHEST 9
#define DOOR 10
#define STAIRSDOWNL 11
#define STAIRSUPR 12
#define STAIRSUPL 13
/* specific maps */
#define TTRL0 "tantthronerooml0.fmp"  /* First map in the game */
#define TTRL0_ACROSS 24 /* Tiles across the first map spans */
#define TTRL0_DOWN 22   /* Tiles down the first map spans */
#define TTRL0W TTRL0_ACROSS*TILEW /* Pixels across the first map spans */
#define TTRL0H TTRL0_DOWN*TILEH   /* Pixels down the first map spans */

/**** game state constants ****/
#define GAMEOVER 0
#define ROAMING 1
#define TEST 2

/**** Global structs and variables ****/

/* player character */
typedef struct {
  int direction;
  int x, y;
  int width, height;
  int speed;
  int xdelay, ydelay;
  int xcount, ycount;
  int currentframe;
  int maxframe;
  int framecount;
  int framedelay;
}PLAYER;
PLAYER *hero;

/* Struct for tiles in the map. */
typedef struct {
  int left;
  int top;
  int right;
  int bottom;
  int width, height;
}BLOCK;

/**** bitmaps ****/
BITMAP *hero_left_bmps[2];
BITMAP *hero_right_bmps[2];
BITMAP *hero_up_bmps[2];
BITMAP *hero_down_bmps[2];
BITMAP *scroll; /* virtual background buffer */
BITMAP *buffer; /* double buffer */

/* PLACE definitions
 * format is:
 * l = locked
 * u = unlocked
 * # = door number
 * full = [[l/u/][#]]...[name]
 
PLACE *l0throneroom;
PLACE *u0throneroom;
PLACE *l1l2tantagel_courtyard;
PLACE *u1l2tantagel_courtyard;
PLACE *l1u2tantagel_courtyard;
PLACE *u1u2tantagel_courtyard;
*/

/**** global variables ****/
int tilex, tiley;
int scrollx, scrolly;
int startx, starty;
int gamestate;
extern int ttrl0[];

/**** Function prototypes ****/
void setup_game (void);
/*
 * Does necessary initializations for starting the game.
 */

void setup_player (void);
/*
 * Performs necessary initializations for setting up the player.
 */

void teardown_player (void);
/*
 * Tearsdown player.
 */

void teardown_game (void);
/*
 * Tearsdown the game.
 */

BITMAP *grabframe (BITMAP *source, int width, int height,
                  int startx, int starty, int columns, int frame);
/*
 * Extracts an image from a spritesheet.
 */

void draw_ttrl0 (void);
/*
 * Draws the throne room with the locked door.
 */

void load_map (char *map);
/*
 * Loads the given map.
 */

int main (void);
/*
 * Main function and game loop.
 */

#endif
