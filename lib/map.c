#include "common.h"

void load_map (int map, int entrance) {

  switch (map) {
  case TTRL0:
    draw_ttrl0();
    break;
    
  case TTRU0:
    teardown_ttrl0();
    draw_ttru0();
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
      if (iscollision == 1) {
	/* check to see what he hit */
	if (ttrl0nowalks[i]->type == DOOR) return 2;
	else return 1;
      }
    }
    break;

  case TTRU0:
    for (i = 0; i < TTRU0; i++) {
      iscollision = inside (player->mapx, player->mapy, ttru0nowalks[i]->left,
			    ttru0nowalks[i]->top, ttru0nowalks[i]->right,
			    ttru0nowalks[i]->bottom);
      if (iscollision == 1) 
	return 1;
    }
    break;
  }
  return 0;
}

BLOCK *create_new_block (int type) {
  BLOCK *newblk;
  newblk = (BLOCK*) malloc (sizeof (BLOCK));
  newblk->height = 32;
  newblk->width = 32;
  newblk->left = tilex - newblk->width;
  newblk->top = tiley - newblk->height;
  newblk->right = tilex + newblk->width;
  newblk->bottom = tiley + newblk->height;
  newblk->type = type;
  return newblk;
}

void draw_ttrl0 (void) {
  int i = 0;
  int j = 0;
  int type;
  
  if ((tiles = load_bitmap("maptiles.bmp", NULL)) == NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
    allegro_message ("Error loading maptiles.bmp file");
    return;
  }
  
  for (tiley = 0; tiley < scroll->h; tiley += TILEH) {
    for (tilex = 0; tilex < scroll->w; tilex += TILEW) {
      if (ttrl0[i] == DOOR || ttrl0[i] == STONE || ttrl0[i] == COUNTER ||
	  ttrl0[i] == STAIRSDOWNL) {
	if (ttrl0[i] == DOOR) type = DOOR;
	else if (ttrl0[i] == STONE) type = STONE;
	else if (ttrl0[i] == COUNTER) type = COUNTER;
	else if (ttrl0[i] == STAIRSDOWNL) type = STAIRSDOWNL;

	ttrl0nowalks[j] = create_new_block(type);
	j++;
      }
      blit (grabframe (tiles, TILEW, TILEH, 0, 0, COLS, ttrl0[i++]), 
	    scroll, 0, 0, tilex, tiley, TILEW, TILEH);
    }
  }
  destroy_bitmap(tiles);
}

void draw_ttru0 (void) {
  int i = 0;
  int j = 0;
  int type;
  
  if ((tiles = load_bitmap("maptiles.bmp", NULL)) == NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
    allegro_message ("Error loading maptiles.bmp file");
    return;
  }
  
  for (tiley = 0; tiley < scroll->h; tiley += TILEH) {
    for (tilex = 0; tilex < scroll->w; tilex += TILEW) {
      if (ttru0[i] == STONE || ttru0[i] == COUNTER || 
	  ttru0[i] == STAIRSDOWNL) {
	if (ttru0[i] == STONE) type = STONE;
	else if (ttru0[i] == COUNTER) type = COUNTER;
	else if (ttru0[i] == STAIRSDOWNL) type = STAIRSDOWNL;

	ttru0nowalks[j] = create_new_block (type);
	j++;
      }
      blit (grabframe (tiles, TILEW, TILEH, 0, 0, COLS, ttru0[i++]), 
	    scroll, 0, 0, tilex, tiley, TILEW, TILEH);
    }
  }
  destroy_bitmap(tiles);
}
