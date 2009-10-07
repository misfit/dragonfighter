#include "common.h"

void map_event_handler (void) {
  switch (currentmap->idnumber) {
  case TCA_LA:
    /* unlock the door in the room */
    if (player->x == TCA2startx && player->y == TCA2starty) {
      currentmap->idnumber = TCA_UA;
      currentmap->initflag = 0;
      currentmap->pointofentry = 0;
    }
    break;

  case TCA_UA:
    /* Send player to the courtyard when he goes to the stairs */
    if (player->x == TCA3startx+32 && player->y == TCA3starty) {
      currentmap->idnumber = TCB_LALB;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    }
    break;

  case TCB_LALB:
    /* send player back to the unlocked throneroom */
    if (player->x == TCB1startx-32 && player->y == TCB1starty) {
      currentmap->idnumber = TCA_UA;
      currentmap->initflag = 1;
      currentmap->pointofentry = 1;

    } else if (player->x == 960 && player->y == 960) {
      currentmap->idnumber = TCC;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    
    } else if ((player->x == 352 || player->x == 384) && player->y == 992) {
      currentmap->idnumber = ALEFGARD1;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
      
    }
    break;

  case TCC:
    if (player->x == 160 && player->y == 224) {
      currentmap->idnumber = TCB_LALB;
      currentmap->initflag = 1;
      currentmap->pointofentry = 2;
    }
    break;

  case ALEFGARD1:
    if (player->x == 1440 && player->y == 1440) {
      currentmap->idnumber = TCB_LALB;
      currentmap->initflag = 1;
      currentmap->pointofentry = 1;
      player->framedelay = 8;
    
    } else if (player->x == 1600 && player->y == 1376) {
      currentmap->idnumber = BYA;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    }
    break;

  } /* end switch idnumber */
}
