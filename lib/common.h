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
#define TREE 8
#define STAIRSDOWNR 9
#define CHEST 10
#define DOOR 11
#define STAIRSDOWNL 12
#define STAIRSUPR 13
#define STAIRSUPL 14
#define SAND 15
#define WEAPONS 16
#define ARMOR 17
#define INN 18
#define BRIDGEH 19
#define BRIDGEV 20

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
#define TTRL0NW 54
#define TTRU0NW 53

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
SPRITE *kinglorik;

typedef struct {
  int left;
  int top;
  int right;
  int bottom;
  int width, height;
  int type;
}BLOCK;

/* unwalkable block arrays */
BLOCK *ttrl0nowalks[TTRL0NW];
BLOCK *ttru0nowalks[TTRU0NW];

/**** global variables ****/
int gameover;
int scrollx, scrolly;
int startx, starty;
int tilex, tiley;
int currentlocation;
/**** maps ****/
extern int ttrl0[];
extern int ttru0[];

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

int move_player (int location);
/*
 * Moves the player in the scroll window. returns error code for collision.
 */

int navigate_maps (int entrypoint);
/*
 * Handles map changes as the player navigates through the game.
 */

void player_up (int blocked);
/*
 * Move the player towards the top of the screen.
 */

void player_down (int blocked);
/*
 * Move the player towards the bottom of the screen.
 */

void player_left (int blocked);
/*
 * Move the player towards the left side of the screen.
 */

void player_right (int blocked);
/*
 * Move the player towards the right side of the screen.
 */

void get_input (int blocked);
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

void teardown_ttru0 (void);
/*
 * Undoes draw_ttru0.
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

void load_map (int map, int entrypoint);
/*
 * Loads the map requested by location constant.
 */

int check_collisions (int map);
/*
 * Goes through the list of nowalks and determines if the player has hit one.
 */

BLOCK *create_new_block (int type);
/*
 * Returns a block object for the drawing functions.
 */

void draw_ttrl0 (void);
/*
 * Draws the throneroom with the door locked and builds the collidable tile
 * list.
 */

void draw_ttru0 (void);
/*
 * Draws the throneroom with the door unlocked and builds the collidable tile
 * list.
 */

#endif
