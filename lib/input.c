#include "common.h"

void player_up (int blocked) {
  if (blocked == 0) player->xspeed = MAXSPEED;
  player->dir = 0;
}

void player_down (int blocked) {
  if (blocked == 0) player->xspeed = MAXSPEED;
  player->dir = 2;
}

void player_left (int blocked) {
  if (blocked == 0) player->xspeed = MAXSPEED;
  player->dir = 3;
}

void player_right (int blocked) {
  if (blocked == 0) player->xspeed = MAXSPEED;
  player->dir = 1;
}

void get_input (int blocked) {
  if (key[KEY_ESC])   gameover = 1;
  
  if (key[KEY_UP])    player_up (blocked);
  else if (key[KEY_RIGHT]) player_right (blocked);
  else if (key[KEY_DOWN])  player_down (blocked);
  else if (key[KEY_LEFT])  player_left (blocked);
  else player->xspeed = 0;
  rest(20);
}

