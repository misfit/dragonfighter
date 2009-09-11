#include "common.h"
#include <stdio.h>

void animate_player (void) {
  if (++player->framecount > player->framedelay) {
    player->framecount = 0;
    player->curframe++;
    if (player->curframe > player->maxframe) player->curframe = 0;
  }
}

void draw_player (void) {
  int x = player->x-15;
  int y = player->y-15;

  switch (player->dir) {
    /* up */
  case 0:
    draw_sprite (buffer, player_up_bmps[player->curframe], x, y);
    break;

    /* right */
  case 1:
    draw_sprite (buffer, player_right_bmps[player->curframe], x, y);
    break;

    /* down */
  case 2:
    draw_sprite (buffer, player_down_bmps[player->curframe], x, y);
    break;
  
    /* left */
  case 3:
    draw_sprite (buffer, player_left_bmps[player->curframe], x, y);
    break;
  }
}

int move_player (int location) {
  int dir = player->dir;
  int speed = player->xspeed;
  int collisiontype;
  
  switch (dir) {
  case 0:
    scrolly -= speed;
    player->mapy -=speed;
    break;
  case 1:
    scrollx += speed;
    player->mapx += speed;
    break;
  case 2:
    scrolly += speed;
    player->mapy += speed;
    break;
  case 3:
    scrollx -= speed;
    player->mapx -= speed;
    break;
  }
  
  switch (location) {
  case TTRL0:
    scroll_ttr();
    collisiontype = check_collisions (TTRL0);
    if (collisiontype == 1) {
      player->xspeed = 0;
      return 1;
    }
    break;
  }
  return 0;
}