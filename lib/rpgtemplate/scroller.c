#include "common.h"

void scroll_ttr (void) {
  if (scrollx < TTRXOFFSET) {
    scrollx = TTRXOFFSET;
    player->xspeed = 0;
    
  } else if (scrollx > scroll->w - SCROLLW/2+TTRWOFFSET) {
    scrollx = scroll->w - SCROLLW/2+TTRWOFFSET;
    player->xspeed = 0;
  }
  if (scrolly < TTRYOFFSET) {
    scrolly = TTRYOFFSET;
    player->xspeed = 0;
    
  } else if (scrolly > scroll->h - SCROLLH/2+TTRHOFFSET) {
    scrolly = scroll->h - SCROLLH/2+TTRHOFFSET;
    player->xspeed = 0;
  }
}
