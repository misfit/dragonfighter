#include "common.h"


void setup_player (void) {
  hero = (HERO*)malloc (sizeof (HERO));
  hero->player = (SPRITE*)malloc (sizeof (SPRITE));
  /* center the player in the scroll window facing left, unmoving */
  hero->player->x = TCA13startx;
  hero->player->y = TCA13starty;
  hero->player->direction = LEFT;
  hero->player->width = 32;
  hero->player->height = 32;
  hero->player->xspeed = 0;
  hero->player->yspeed = 0;
  hero->player->curframe = 0;
  hero->player->maxframe = 1;
  hero->player->framecount = 0;
  hero->player->framedelay = 8;
  hero->keys = 0;
  hero->gold = 0;
  hero->experience = 0;
}

void draw_player (void) {
  switch (hero->player->direction) {
  case DOWN:
    draw_sprite (scrollbmp, playerdnbmp[hero->player->curframe],
		 hero->player->x, hero->player->y);
    break;

  case UP:
    draw_sprite (scrollbmp, playerupbmp[hero->player->curframe],
		 hero->player->x, hero->player->y);
    break;

  case LEFT:
    draw_sprite (scrollbmp, playerltbmp[hero->player->curframe],
		 hero->player->x, hero->player->y);
    break;

  case RIGHT:
    draw_sprite (scrollbmp, playerrtbmp[hero->player->curframe],
		 hero->player->x, hero->player->y);
    break;
  }
}

void animate_player (void) {
  /* prevent animation if the sprite is not moving. */
  if (hero->player->xspeed != 0 || hero->player->yspeed != 0) {
    
    /* animate the sprite */
    if (hero->player->framecount++ > hero->player->framedelay) {
      hero->player->framecount = 0;
      hero->player->curframe++;
      if (hero->player->curframe > hero->player->maxframe) 
	hero->player->curframe = 0;
    }
  }
}

void move_player (void) {
  switch (hero->player->direction) {
  case DOWN:
    if (hero->player->y < scrollbmp->h-32) hero->player->y += 
					     hero->player->yspeed;
    break;

  case UP:
    if (hero->player->y > scrolly) hero->player->y += hero->player->yspeed;
    break;

  case LEFT:
    if (can_move(currentmap->idnumber) != 0)
      if (hero->player->x > scrollx) hero->player->x += hero->player->xspeed;
    break;

  case RIGHT:
    if (can_move(currentmap->idnumber) != 0)
      if (hero->player->x < scrollbmp->w-32) hero->player->x += 
					       hero->player->xspeed;
    break;
  }
}

int can_move (int mapid) {
  switch (currentmap->idnumber) {
  case TCA_13:
    switch (is_collision (TCA13)) {
    case 1:
      return 0;
      break;

    case 3:
      return 0;
      break;

    case 10:
      return 0;
      break;

    default:
      break;
    }
  }
  return 1;
}
