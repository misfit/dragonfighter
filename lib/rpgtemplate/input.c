#include "common.h"

void player_up (void) {
  player->xspeed = MAXSPEED;
  player->dir = 0;
}

void player_down (void) {
  player->xspeed = MAXSPEED;
  player->dir = 2;
}

void player_left (void) {
  player->xspeed = MAXSPEED;
  player->dir = 3;
}

void player_right (void) {
  player->xspeed = MAXSPEED;
  player->dir = 1;
}

void get_input (void) {
  if (key[KEY_ESC])   gameover = 1;
  
  if (key[KEY_UP])    player_up();
  else if (key[KEY_RIGHT]) player_right();
  else if (key[KEY_DOWN])  player_down();
  else if (key[KEY_LEFT])  player_left();
  else player->xspeed = 0;
  rest(20);
}

