/****
 * Main header file for Dragon Fighter. 
 * Copyright (c) 2009 Brian S. Moriya
 * See LICENSE and COPYING for licence information.
 ****/

#ifndef _COMMON_H
#define _COMMON_H

#include <allegro.h>

/* Allegro constants */
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480

/* scrolling constants */
#define SCROLL_STEP 8

/* map constants */
#define TILEW 32
#define TILEH 32
#define COLS 10

/* Tantagel castle courtyard */
#define TCB_ACROSS 32
#define TCB_DOWN 32
#define TCBW TCB_ACROSS*TILEW
#define TCBH TCB_DOWN*TILEH
extern int TCBLALB[];

/* bitmaps */
BITMAP *bufferbmp;
BITMAP *scrollbmp;
BITMAP *tilesbmp;

/* position variables */
int scrollx;
int scrolly;
int tilex, tiley;

/* function prototypes */

void setup_allegro (int mode, int screenw, int screenh, int cdepth);
void setup_bmps (void);
void destroy_bmps (void);
void draw_frame (BITMAP *source, BITMAP *destination, int x, int y, int width, 
		int height, int startx, int starty, int columns, int frame);
/*
 * Taken from Game Programming All in One 3rd ed.
 */
void draw_TCBLALB (void);

#endif
