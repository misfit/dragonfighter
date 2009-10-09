#include "common.h"

int is_collision (int map[]) {
  int playerleft = hero->player->x;
  int playerright = hero->player->x+hero->player->width;
  int playertop = hero->player->y;
  int playerbottom = hero->player->y+hero->player->height;
  int tileleft;
  int tileright;
}

void map_event_handler (void) {
  /* detect collisions */
  switch (currentmap->idnumber) {
  case TCA_13:
    /* hero gets the left chest */
    
    /* hero gets the right chest */

    /* hero unlocks the door */
    
    
    /* unlock the door in the room 
    if (player->x == TCA2startx && player->y == TCA2starty) {
      currentmap->idnumber = TCA_11;
      currentmap->initflag = 0;
      currentmap->pointofentry = 0;
      }*/
    break;

  case TCA_11:
    /* Send player to the courtyard when he goes to the stairs 
    if (player->x == TCA3startx+32 && player->y == TCA3starty) {
      currentmap->idnumber = TCB_LALB;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
      }*/
    break;

  case 20:
    /* send player back to the unlocked throneroom 
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
      
      }*/
    break;
    /*
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
      currentmap->idnumber = BYA_L3L4;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    }
    break;

  case ALEFGARD2:
    break;
    */
  case BYA_L3L4:
    /* player has walked out the front gate */
    if (hero->player->x == 0) {
      currentmap->idnumber = ALEFGARD1;
      currentmap->initflag = 1;
      currentmap->pointofentry = 1;

    } else if (hero->player->x == 736 && hero->player->y == 768) {
      currentmap->idnumber = BYC_;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;

    } else if (hero->player->x == 704 && hero->player->y == 224) {
      currentmap->idnumber = BYB_;
      currentmap->initflag = 1;
      currentmap->pointofentry = 0;
    }
    break;
  } /* end switch idnumber */
}
