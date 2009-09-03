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

#define THRONE_ROOM 0
#define TANTAGEL_CASTLE_CYARD 1
#define TANTAGEL_CASTLE_BASEMT 2
#define TR0 0

#define GAMEOVER 0
#define ROAMING 1
#define TEST 2

/**** Global structs and variables ****/

typedef struct {
  struct NODE *next;
}NODE;

/*
 * Struct for the hero of the game. 
 */
typedef struct {
  /* Motion variables */
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
  /* Attributes variables */
  int currentlocation;
}HERO;

/*
 * Struct for tiles int the map.
 */
typedef struct {
  int left;
  int top;
  int right;
  int bottom;
  int width, height;
}BLOCK;

typedef struct {
  BLOCK *block;
  struct BLOCKNODE *next;
}BLOCKNODE;

typedef struct {
  int type;
  int id;
  BLOCK *block;
  struct NOWALKNODE *next;
}NOWALKNODE;

typedef struct {
  int map;
}MAP;

typedef struct {
  NOWALKNODE *nowalkshead;
}PLACE;

/**** Character bitmaps and sprites ****/

HERO *hero;
BITMAP *hero_left_images[2];
BITMAP *hero_right_images[2];
BITMAP *hero_up_images[2];
BITMAP *hero_down_images[2];
BITMAP *tempbitmap;
BITMAP *scroll;
BITMAP *tiles;

/* PLACE definitions
 * format is:
 * l = locked
 * u = unlocked
 * # = door number
 * full = [[l/u/][#]]...[name]
 */
PLACE *l0throneroom;
PLACE *u0throneroom;
PLACE *l1l2tantagel_courtyard;
PLACE *u1l2tantagel_courtyard;
PLACE *l1u2tantagel_courtyard;
PLACE *u1u2tantagel_courtyard;

int n; 

/* Position variables for laying tiles */
int tilex, tiley;
int scrollx, scrolly;
int gamestate;

/**** Function prototypes ****/

void initialize_game (int colordepth);

void setup_hero (void);

void cleanup_hero (void);

void cleanup_locked_thronerooom (void);

void cleanup_unlocked_throneroom (void);

BITMAP *grab_frame (BITMAP *source, int width, int height,
		   int startx, int starty, int columns, int frame);

void draw_frame (BITMAP *source, BITMAP *dest, int x, int y, int width,
		int height, int startx, int starty, int columns, int frame);

void cleanup (void);

int is_inside (int x, int y, int left, int top, int right, int bottom);

unsigned char get_input (PLACE *place);

void animate_hero (void);

void move_hero (void);

int check_collision (PLACE *place);

void add_nowalk (PLACE *place, NOWALKNODE *newnode);

BLOCK *create_new_block (void);

void draw_locked_throneroom (void);

void draw_unlocked_throneroom (void);

void draw_tantagel_courtyard (void);

PLACE *load_map (const unsigned char curlocation);

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

/* Maps
 * format is:
 * # = door numbers of unlocked doors on map.
 * name = variable name
 * full = [name][#]...
 */
#define LTR 0
#define LTRACROSS 24
#define LTRDOWN 24
#define DR1 0
int throneroommap0[] = {
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,0,0,0,0,0,0,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,0,1,0,0,1,0,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,2,2,2,10,2,2,2,2,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,11,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
};

#define UTR 1
#define UTRACROSS 24
#define UTRDOWN 24
int throneroommap[] = {
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,0,0,0,0,0,0,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,0,1,0,0,1,0,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,1,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,2,2,2,1,2,2,2,2,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,1,1,1,1,1,1,1,11,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
};

#define TCY 2
#define TCYACROSS 32
#define TCYDOWN 32
#define DR2 1
#define DR3 2
int tantagelcourtyard12[] = {
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  3,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,3,2,2,2,3,7,3,3,3,
  3,2,1,1,1,1,1,2,3,3,3,3,3,3,3,3,2,1,1,1,1,1,2,3,2,1,2,3,3,3,3,3,
  3,2,1,1,1,1,1,2,3,3,3,3,3,3,3,3,2,1,1,1,1,1,2,3,2,0,2,3,3,3,3,3,
  3,2,1,1,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,1,1,2,3,3,3,7,7,3,3,3,3,
  3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,7,7,7,3,3,3,3,3,
  3,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,
  3,2,2,2,2,2,1,2,1,1,1,1,1,1,1,1,2,2,2,10,2,2,2,2,2,1,2,2,2,3,3,3,
  3,2,1,1,1,2,1,2,13,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,
  3,2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,
  3,2,1,1,1,2,1,2,2,2,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,3,3,3,
  3,2,2,2,2,2,1,2,7,7,1,1,1,1,7,7,2,1,1,2,1,1,2,1,1,2,1,1,2,3,3,3,
  3,2,1,1,1,2,1,2,7,7,1,1,1,1,7,7,2,1,1,2,1,1,2,1,1,2,1,1,2,3,3,3,
  3,2,1,1,1,2,1,2,7,3,1,1,1,1,3,7,2,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,
  3,2,9,1,1,10,1,2,3,3,1,1,1,1,3,3,2,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,
  3,2,1,9,1,2,1,2,3,3,1,1,1,1,3,3,2,1,1,2,1,1,2,1,1,2,1,1,2,3,3,3,
  3,2,9,1,9,2,1,2,3,1,1,1,1,1,1,3,2,1,1,2,1,1,2,1,1,2,1,1,2,3,3,3,
  3,2,2,2,2,2,1,2,3,1,6,6,6,6,1,3,2,2,2,2,2,2,2,2,2,2,1,2,2,3,3,3,
  3,2,1,1,1,1,1,1,1,1,6,5,5,6,1,1,1,1,1,1,1,1,2,1,1,1,1,1,2,3,3,3,
  3,2,1,1,1,1,1,1,1,1,6,5,5,6,1,1,1,1,1,1,1,1,2,5,5,5,5,5,2,3,3,3,
  3,2,2,2,1,1,2,2,2,1,6,6,6,6,1,2,2,1,1,1,1,1,2,5,5,5,5,5,2,3,3,3,
  3,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,2,3,3,3,
  3,2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,2,2,2,2,1,1,2,1,1,1,1,1,2,6,3,3,
  3,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,6,3,3,
  3,2,1,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,2,6,6,6,6,6,6,6,3,3,
  3,2,1,6,6,1,1,2,1,2,1,1,1,1,2,1,1,2,2,2,2,2,2,6,6,6,6,6,6,6,3,3,
  3,2,6,6,6,6,1,1,1,2,1,1,1,1,2,1,1,2,1,1,2,1,2,6,6,6,6,6,6,6,3,3,
  3,2,6,6,6,6,1,1,1,2,2,1,1,2,2,1,1,1,1,1,0,1,2,6,6,6,6,6,6,6,3,3,
  3,2,6,6,6,6,6,1,1,2,1,1,1,1,2,1,1,2,1,1,2,1,2,6,6,6,6,6,6,6,3,3,
  3,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,6,6,6,6,6,6,6,3,3,
  3,6,6,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,11,3,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
};

unsigned int mapw = LTRACROSS*TILEW;
unsigned int maph = LTRDOWN*TILEH;

#endif
