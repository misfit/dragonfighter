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

/* map constants */
#define TILEW 32
#define TILEH 32
#define COLS 10
#define DOWN 0
#define UP 1
#define RIGHT 2
#define LEFT 3

/* game constants */
#define NORM_SPEED 2
#define HALF_SPEED NORM_SPEED/2
#define PLAINS_SPEED 4
#define MTN_SPEED PLAINS_SPEED*2

/* Tantagel Castle basement */
#define TCC_ACROSS 20
#define TCC_DOWN 15
#define TCCW TCC_ACROSS*TILEW
#define TCCH TCC_DOWN*TILEH
#define TCC 6
extern int TCC_L1[];
extern int TCCstartx;
extern int TCCstarty;

/* Tantagel Castle courtyard */
#define TCB_LALB 2
#define TCB_LAUB 3
#define TCB_UALB 4
#define TCB_UAUB 5
#define TCB_ACROSS 32
#define TCB_DOWN 32
#define TCBW TCB_ACROSS*TILEW
#define TCBH TCB_DOWN*TILEH
extern int TCBLALB[];
extern int TCB1startx;
extern int TCB1starty;
extern int TCB2startx;
extern int TCB2starty;
extern int TCB3startx;
extern int TCB3starty;

/* Tantagel Castle throneroom */
#define TCA_LA 0
#define TCA_UA 1
#define TCA_ACROSS 20
#define TCA_DOWN 15
#define TCAW TCA_ACROSS*TILEW
#define TCAH TCA_DOWN*TILEH
extern int TCALA[];
extern int TCAUA[];
extern int TCA1startx;
extern int TCA1starty;
extern int TCA2startx;
extern int TCA2starty;
extern int TCA3startx;
extern int TCA3starty;

/* Breconary */
#define BYA_L3L4 9
#define BYA_L3U4 12
#define BYA_U3L4 13
#define BYA_U3U4 14
#define BYB_ 10
#define BYC_ 11
#define BYA_ACROSS 32
#define BYA_DOWN 32
#define BYAW BYA_ACROSS*TILEW
#define BYAH BYA_DOWN*TILEH
#define BYB_ACROSS 20
#define BYB_DOWN 15
#define BYBW BYB_ACROSS*TILEW
#define BYBH BYB_DOWN*TILEH
#define BYC_ACROSS 20
#define BYC_DOWN 15
#define BYCW BYC_ACROSS*TILEW
#define BYCH BYC_DOWN*TILEH
extern int BYAL3L4[];
extern int BYAL3U4[];
extern int BYAU3L4[];
extern int BYAU3U4[];
extern int BYA1startx;
extern int BYA1starty;
extern int BYB[];
extern int BYC[];

/* Alefgard */
#define ALEFGARD_ACROSS 124
#define ALEFGARD_DOWN 124
#define ALEFGARDW ALEFGARD_ACROSS*TILEW
#define ALEFGARDH ALEFGARD_DOWN*TILEH
extern int ALEFGARDTCstartx;
extern int ALEFGARDTCstarty;
extern int ALEFGARDBYstartx;
extern int ALEFGARDBYstarty;
extern int ALEFGARD[];
#define ALEFGARD1 7 /* without landbridge */
#define ALEFGARD2 8 /* with the land bridge */

/* bitmaps */
BITMAP *bufferbmp;
BITMAP *scrollbmp;
BITMAP *tilesbmp;
BITMAP *playerupbmp[2];
BITMAP *playerdnbmp[2];
BITMAP *playerltbmp[2];
BITMAP *playerrtbmp[2];

/* typedefs */
typedef struct SPRITE {
  int x; /* x position of sprite's center */
  int y; /* y position of sprite's center */
  int direction;
  int width;
  int height;
  int xspeed;
  int yspeed;
  int curframe; /* current animation frame */
  int maxframe; /* number of animation frames */
  int framecount;
  int framedelay;
}SPRITE;

/* sprites */
SPRITE *player;

typedef struct MAP {
  int unlocked;
  int pointofentry;
  int pointofexit;
  int initflag;
  int idnumber;
}MAP;

/* maps */
MAP *currentmap;
MAP *tcala;
MAP *tcaua;
MAP *tcblalb;
MAP *tcblaub;
MAP *tcbualb;
MAP *tcbuaub;

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
BITMAP *grab_frame (BITMAP *source, int width, int height, int startx, 
		    int starty, int columns, int frame);
/*
 * Taken from Game Programming All in One 3rd ed.
 */
void get_input (void);
void draw_map (int map[]);
void setup_player (void);
void draw_player (void);
void animate_player (void);
void move_player (void);
void scroll_window (void);
void map_event_handler (void);
void map_handler (void);
void print_scroll_debug_messages (void);
void print_player_debug_messages (void);

#endif
