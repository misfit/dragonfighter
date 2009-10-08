#include "common.h"


void setup_player (void) {
  player = (SPRITE*)malloc (sizeof (SPRITE));
  /* center the player in the scroll window facing down, unmoving */
  player->x = TCA12startx;
  player->y = TCA12starty;
  player->direction = LEFT;
  player->width = 32;
  player->height = 32;
  player->xspeed = 0;
  player->yspeed = 0;
  player->curframe = 0;
  player->maxframe = 1;
  player->framecount = 0;
  player->framedelay = 8;
}

void draw_player (void) {
  switch (player->direction) {
  case DOWN:
    draw_sprite (scrollbmp, playerdnbmp[player->curframe],
		 player->x, player->y);
    break;

  case UP:
    draw_sprite (scrollbmp, playerupbmp[player->curframe],
		 player->x, player->y);
    break;

  case LEFT:
    draw_sprite (scrollbmp, playerltbmp[player->curframe],
		 player->x, player->y);
    break;

  case RIGHT:
    draw_sprite (scrollbmp, playerrtbmp[player->curframe],
		 player->x, player->y);
    break;
  }
}

void animate_player (void) {
  /* prevent animation if the sprite is not moving. */
  if (player->xspeed != 0 || player->yspeed != 0) {
    
    /* animate the sprite */
    if (player->framecount++ > player->framedelay) {
      player->framecount = 0;
      player->curframe++;
      if (player->curframe > player->maxframe) player->curframe = 0;
    }
  }
}

void move_player (void) {
  switch (player->direction) {
  case DOWN:
    if (player->y < scrollbmp->h-32) player->y += player->yspeed;
    break;

  case UP:
    if (player->y > scrolly) player->y += player->yspeed;
    break;

  case LEFT:
    if (player->x > scrollx) player->x += player->xspeed;
    break;

  case RIGHT:
    if (player->x < scrollbmp->w-32) player->x += player->xspeed;
    break;
  }
}
