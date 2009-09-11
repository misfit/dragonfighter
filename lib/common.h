#ifndef _COMMON_H
#define _COMMON_H

#include <stdlib.h>
#include <allegro.h>

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 512
#define HEIGHT 480
#define MAXSPEED 4
#define BULLETSPEED 10
#define TILEW 32
#define TILEH 32
#define TILES 21
#define COLS 10
#define SCROLLW WIDTH
#define SCROLLH HEIGHT

#define COUNTER 1
#define BRICK 2
#define STONE 3
#define GRASS 4
#define ROOF 5
#define BARRIER 6
#define WATER 7
#define STAIRSDOWNR 8
#define CHEST 9
#define DOOR 10
#define STAIRSDOWNL 11
#define STAIRSUPR 12
#define STAIRSUPL 13

#define TTRL0 0
#define TTRU0 1
#define TTR_ACROSS 24
#define TTR_DOWN 22
#define TTRW TTR_ACROSS * TILEW
#define TTRH TTR_DOWN * TILEH
#define TTRXOFFSET 0
#define TTRWOFFSET -265
#define TTRYOFFSET 0
#define TTRHOFFSET -240

/**** typedef structs ****/
/*
 * struct for game sprites.
 */
typedef struct {
  int dir, alive;
  int x,y;
  int mapx, mapy;
  int width,height;
  int xspeed,yspeed;
  int xdelay,ydelay;
  int xcount,ycount;
  int curframe,maxframe,animdir;
  int framecount,framedelay;
}SPRITE;
SPRITE *player;

typedef struct {
  int left;
  int top;
  int right;
  int bottom;
  int width, height;
}BLOCK;

/* unwalkable block arrays */
BLOCK *ttrl0nowalks[54];
BLOCK *ttru0nowalks[53];

/**** global variables ****/
int gameover;
int scores;
int scrollx, scrolly;
int startx, starty;
int tilex, tiley;

extern int ttrl0[];

BITMAP *player_up_bmps[2];
BITMAP *player_down_bmps[2];
BITMAP *player_left_bmps[2];
BITMAP *player_right_bmps[2];
BITMAP *buffer;
BITMAP *tiles;
BITMAP *scroll;

/**** function prototypes ****/
void animate_player (void);
/*
 * Adjusts sprite variables for animation.
 */

void draw_player (void);
/*
 * Draws player to the buffer with call to blit.
 */

void move_player (int location);
/*
 * Moves the player in the scroll window.
 */

void player_up (void);
/*
 * Move the player towards the top of the screen.
 */

void player_down (void);
/*
 * Move the player towards the bottom of the screen.
 */

void player_left (void);
/*
 * Move the player towards the left side of the screen.
 */

void player_right (void);
/*
 * Move the player towards the right side of the screen.
 */

void get_input (void);
/*
 * Keyboard input hanler.
 */

void setup_game (void);
/*
 * Sets up the game. Main only needs to call this function.
 */

void setup_player (void);
/*
 * Loads bitmaps for the player images and initializes all related variables.
 */

void setup_screen (void);
/*
 * Sets up the screen and the first scene of the game.
 */

void teardown_game (void);
/*
 * Undoes setup game.
 */

void teardown_player (void);
/*
 * Undoes setup player.
 */

void teardown_screen (void);
/*
 * Undoes setup_screen.
 */

void teardown_ttrl0 (void);
/*
 * Undoes draw_ttrl0.
 */

int inside (int,int,int,int,int,int);
/*
 * Performs collision checking on 2 rectangular regions.
 */

BITMAP *grabframe(BITMAP *, int, int, int, int, int, int);
/*
 * Grabs a tile from a spritesheet.
 */

void scroll_ttr (void);
/*
 * Handles scrolling in the throneroom.
 */

void load_map (int location);
/*
 * Loads the map requested by location constant.
 */

int check_collisions (int map);
/*
 * Goes through the list of nowalks and determines if the player has hit one.
 */

BLOCK *create_new_block (void);
/*
 * Returns a block object for the drawing functions.
 */

void draw_ttrl0 (void);
/*
 * Draws the throneroom with the door locked and builds the collidable tile
 * list.
 */

#endif
