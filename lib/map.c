#include "common.h"

void load_map (int map) {
  int i;

  switch (map) {
  case TTRL0:    
    draw_ttrl0();
    break;
  }
}

int check_collisions (int map) {
  int collisiontype, iscollision;
  int i;
  
  switch (map) {
  case TTRL0:
    for (i = 0; i < TTRL0NW; i++) {
      iscollision = inside (player->mapx, player->mapy, ttrl0nowalks[i]->left,
			    ttrl0nowalks[i]->top, ttrl0nowalks[i]->right,
			    ttrl0nowalks[i]->bottom);
      if (iscollision == 1) 
	return 1;
    }
    break;
  }
  return 0;
}

BLOCK *create_new_block (void) {
}

void draw_ttrl0 (void) {
  int i = 0;
  int j = 0;
  
  if ((tiles = load_bitmap("maptiles.bmp", NULL)) == NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
    allegro_message ("Error loading maptiles.bmp file");
    return;
  }
  
  for (tiley = 0; tiley < scroll->h; tiley += TILEH) {
    for (tilex = 0; tilex < scroll->w; tilex += TILEW) {

      if (ttrl0[i] == DOOR || ttrl0[i] == STONE || ttrl0[i] == COUNTER ||
      ttrl0[i] == STAIRSDOWNL) {
	BLOCK *newblk;
	newblk = (BLOCK*) malloc (sizeof (BLOCK));
	newblk->height = 32;
	newblk->width = 32;
	newblk->left = tilex - newblk->width;
	newblk->top = tiley - newblk->height;
	newblk->right = tilex + newblk->width;
	newblk->bottom = tiley + newblk->height;
	ttrl0nowalks[j] = newblk;
	j++;
      }
      blit (grabframe (tiles, TILEW, TILEH, 0, 0, COLS, ttrl0[i++]), 
	    scroll, 0, 0, tilex, tiley, TILEW, TILEH);
    }
  }
  destroy_bitmap(tiles);
}
