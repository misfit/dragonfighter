#include "common.h"

void draw_map (int map[]) {
  int i = 0;

  for (tiley = 0; tiley < scrollbmp->h; tiley += TILEH) {
    for (tilex = 0; tilex < scrollbmp->w; tilex += TILEW) {
      draw_frame (tilesbmp, scrollbmp, tilex, tiley, TILEW, TILEH, 0, 0,
                  COLS, map[i++]);
    }
  }
}

int hash_position (void) {
  int rowmultiplier = 0;
  int column = 0;
  int index = 0;

  if (hero->player->y != 0) rowmultiplier = hero->player->y/TILEH;  
  if (hero->player->x != 0) column = hero->player->x/TILEW;
  return index = rowmultiplier*currentmap->width + column;
}

void map_handler (void) {
  /* find out which map to draw */
  switch (currentmap->idnumber) {
  case TCA_13:
    /* Initial game map. */
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (TCAW, TCAH);
      clear (scrollbmp);
      currentmap->lockeddoors = 0x1;
      currentmap->pointofentry = 0;
      currentmap->chests = 0x2;
      currentmap->width = TCA_ACROSS;
      currentmap->maplen = TCA_ACROSS*TCA_DOWN;
      currentmap->initflag = 0;
    }
    draw_map (TCA13);
    break;
    
  case TCA_12:
    switch (currentmap->pointofentry) {
    case 0:
      /* door was just unlocked */
      if (currentmap->initflag == 1) {
	currentmap->initflag = 0;
      }
      draw_map (TCA10);
      break;
      
    case 1:
      /* has entered from the courtyard */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCAW, TCAH);
	hero->player->x = TCA13startx;
	hero->player->y = TCA13starty;
	currentmap->initflag = 0;
      }
      draw_map (TCA10);
      break;
    }
    break;

  case 20:
    switch (currentmap->pointofentry) {
    case 0:
      /* player has entered from the throneroom */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCBW, TCBH);
	hero->player->x = TCB1startx;
	hero->player->y = TCB1starty;
	currentmap->initflag = 0;
      }
      draw_map (TCBLALB);
      break;

    case 1:
      /* player entered through the front gate */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCBW, TCBH);
	hero->player->x = TCB2startx;
	hero->player->y = TCB2starty;
	scrollx = 64;
	scrolly = 544;
	currentmap->initflag = 0;
      }
      draw_map (TCBLALB);
      break;

    case 2:
      /* player has entered from the basement */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCBW, TCBH);
	hero->player->x = TCB3startx;
	hero->player->y = TCB3starty;
	scrollx = 384;
	scrolly = 544;
	currentmap->initflag = 0;
      }
      draw_map (TCBLALB);
      break;
    }
    break;

  case TCC:
    /* only one possible case for entry */
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (TCCW, TCCH);
      clear (scrollbmp);
      hero->player->x = TCCstartx;
      hero->player->y = TCCstarty;
      scrollx = 0;
      scrolly = 0;
      currentmap->initflag = 0;
    }
    draw_map (TCC_L1);
    break;

  case ALEFGARD1:
    switch (currentmap->pointofentry) {
    case 0:
      /* player coming from Tantagel Castle */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (ALEFGARDW, ALEFGARDH);
	clear (scrollbmp);
	hero->player->x = ALEFGARDTCstartx;
	hero->player->y = ALEFGARDTCstarty;
	scrollx = 1300;
	scrolly = 1300;
	currentmap->initflag = 0;
      }
      break;

    case 1:
      /* player coming from Breconary */
      if (currentmap-> initflag == 1) {
	scrollbmp = create_bitmap (ALEFGARDW, ALEFGARDH);
	clear (scrollbmp);
	hero->player->x = ALEFGARDBYstartx;
	hero->player->y = ALEFGARDBYstarty;
	scrollx = 1300;
	scrolly = 1300;
	currentmap->initflag = 0;
      }
    }
    draw_map (ALEFGARD);
    break;

  case ALEFGARD2:
    break;

  case BYA_L3L4:
    switch (currentmap->pointofentry) {
    case 0:
      /* player entered through the gate */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (BYAW, BYAH);
	clear (scrollbmp);
	hero->player->x = BYA1startx;
	hero->player->y = BYA1starty;
	scrollx = 0;
	scrolly = 128;
	currentmap->initflag = 0;
      }
      break;
    case 1:
      /* player has come out of the items shop */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (BYAW, BYAH);
	clear (scrollbmp);
	hero->player->x = BYA2startx;
	hero->player->y = BYA2starty;
	scrollx = 384;
	scrolly = 412;
	currentmap->initflag = 0;
      }
      break;

    case 2:
      /* player has come out of the locked building */
      break;
    }
    draw_map (BYAL3L4);
    break;

  case BYB_:
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (BYBW, BYBH);
      clear (scrollbmp);
      hero->player->x = BYBstartx;
      hero->player->y = BYBstarty;
      scrollx = 0;
      scrolly = 0;
      currentmap->initflag = 0;
    }
    draw_map (BYB);
    break;

  case BYC_:
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (BYCW, BYCH);
      clear (scrollbmp);
      hero->player->x = BYCstartx;
      hero->player->y = BYCstarty;
      scrollx = 0;
      scrolly = 0;
      currentmap->initflag = 0;
    }
    draw_map (BYC);
    break;
  } /* end switch idnumber */
}
