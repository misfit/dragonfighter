#include "common.h"

void load_map (int map) {
  switch (map) {
  case TTRL0:
    l0ttr = (PLACE*) malloc (sizeof (PLACE));
    l0ttr->nowalkhead = NULL;
    draw_ttrl0();
    break;
  }
}

int check_collisions (PLACE *place) {
  int collisiontype;
  NOWALKNODE *temp;
  
  temp = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
  temp = place->nowalkhead;

  while (temp != NULL && collisiontype != 1) {
    collisiontype = inside (player->x, player->y, 
			    temp->block->left, temp->block->top, 
			    temp->block->right, temp->block->bottom);
    /* if collision is detected,determine the type */
    if (collisiontype == 1) {
      if (temp->type == DOOR) return 2;
      else if (temp->type == STAIRSDOWNL) return 3;
      else if (temp->type == STAIRSUPL) return 4;
      else if (temp->type == STAIRSDOWNR) return 5;
      else if (temp->type == STAIRSUPR) return 6;
      else return 1;
      
    } else temp = temp->next;
  }
  free (temp);
  return 0;
}

void add_nowalk (PLACE *place) {

}

BLOCK *create_new_block (void) {
  BLOCK *newblk;
  newblk = (BLOCK*) malloc (sizeof (BLOCK));
  newblk->height = 32;
  newblk->width = 32;
  newblk->left = tilex - newblk->width;
  newblk->top = tiley - newblk->height;
  newblk->right = tilex + newblk->width;
  newblk->bottom = tiley + newblk->height;
  return newblk;
}

void draw_ttrl0 (void) {
  int i = 0;

  if ((tiles = load_bitmap("maptiles.bmp", NULL)) == NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
    allegro_message ("Error loading maptiles.bmp file");
    return;
  }
  
  for (tiley = 0; tiley < scroll->h; tiley += TILEH) {
    for (tilex = 0; tilex < scroll->w; tilex += TILEW) {
      if (ttrl0[i] == DOOR || ttrl0[i] == STONE || ttrl0[i] == COUNTER ||
	  ttrl0[i] == STAIRSDOWNL) {
	NOWALKNODE *newnwn;
	newnwn = (NOWALKNODE*) malloc (sizeof (NOWALKNODE));
	if (ttrl0[i] == DOOR) {
	  newnwn->id = 1;
	  newnwn->type = DOOR;
	}
	if (ttrl0[i] == STONE) newnwn->type = STONE;
	if (ttrl0[i] == COUNTER) newnwn->type = COUNTER;
	if (ttrl0[i] == STAIRSDOWNL) newnwn->type = STAIRSDOWNL;
	newnwn->block = create_new_block();
	add_nowalk (l0ttr, newnwn);
      }
      blit (grabframe (tiles, TILEW, TILEH, 0, 0, COLS, ttrl0[i++]), 
	    scroll, 0, 0, tilex, tiley, TILEW, TILEH);
    }
  }
  destroy_bitmap(tiles);
}
