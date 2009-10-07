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

void map_handler (void) {
  /* find out which map to draw */
  switch (currentmap->idnumber) {
  case TCA_LA:
    /* only one possible case for entry */
    if (currentmap->initflag == 1) {
      scrollbmp = create_bitmap (TCAW, TCAH);
      currentmap->initflag = 0;
    }
    draw_map (TCALA);
    break;

  case TCA_UA:
    switch (currentmap->pointofentry) {
    case 0:
      /* door was just unlocked */
      if (currentmap->initflag == 1) {
	currentmap->initflag = 0;
      }
      draw_map (TCAUA);
      break;
      
    case 1:
      /* has entered from the courtyard */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCAW, TCAH);
	player->x = TCA3startx;
	player->y = TCA3starty;
	currentmap->initflag = 0;
      }
      draw_map (TCAUA);
      break;
    }
    break;

  case TCB_LALB:
    switch (currentmap->pointofentry) {
    case 0:
      /* player has entered from the throneroom */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCBW, TCBH);
	player->x = TCB1startx;
	player->y = TCB1starty;
	currentmap->initflag = 0;
      }
      draw_map (TCBLALB);
      break;

    case 1:
      /* player entered through the front gate */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (TCBW, TCBH);
	player->x = TCB2startx;
	player->y = TCB2starty;
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
	player->x = TCB3startx;
	player->y = TCB3starty;
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
      player->x = TCCstartx;
      player->y = TCCstarty;
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
	player->x = ALEFGARDTCstartx;
	player->y = ALEFGARDTCstarty;
	scrollx = 1300;
	scrolly = 1300;
	currentmap->initflag = 0;
      }
      break;
    }
    draw_map (ALEFGARD);
    break;

  case ALEFGARD2:
    break;

  case BYA:
    switch (currentmap->pointofentry) {
    case 0:
      /* player entered through the gate */
      if (currentmap->initflag == 1) {
	scrollbmp = create_bitmap (BYAW, BYAH);
	clear (scrollbmp);
	player->x = BYA1startx;
	player->y = BYA1starty;
	scrollx = 0;
	scrolly = 128;
	currentmap->initflag = 0;
      }
      break;
    }
    draw_map (BRECONARYL3L4);
    break;

  case BYB:
    break;

  case BYC:
    break;
  } /* end switch idnumber */
}
