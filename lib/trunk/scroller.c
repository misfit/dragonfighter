#include "common.h"

void scroll_window (void) {
  switch (hero->player->direction) {
  case RIGHT:
    /* limits the bounds of the scroll window to the current map. */
    scrollx += hero->player->xspeed;
    if (scrollx > scrollbmp->w-WIDTH) scrollx = scrollbmp->w - WIDTH;
    break;

  case LEFT:
    /* limits the bounds of the scroll window to the current map. */
    scrollx += hero->player->xspeed;
    if (scrollx < 0) scrollx = 0;
    break;

  case UP:
    /* limits the bounds of the scroll window to the current map. */
    scrolly += hero->player->yspeed;
    if (scrolly < 0) scrolly = 0;
    break;

  case DOWN:
    /* limits the bounds of the scroll window to the current map. */
    scrolly += hero->player->yspeed;
    if (scrolly > scrollbmp->h-HEIGHT) scrolly = scrollbmp->h - HEIGHT;
    break;
  }
}
