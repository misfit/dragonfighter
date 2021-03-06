#include "common.h"

void get_input (void) {
  /**** regular motion key handling ****/
  if (key[KEY_RIGHT]) {
    hero->player->direction = RIGHT;
    hero->player->xspeed = NORM_SPEED;
    
  } else if (key[KEY_LEFT]) {
    hero->player->direction = LEFT;
    hero->player->xspeed = -NORM_SPEED;
    
  } else if (key[KEY_DOWN]) {
    hero->player->direction = DOWN;
    hero->player->yspeed = NORM_SPEED;
    
  } else if (key[KEY_UP]) {
    hero->player->direction = UP;
    hero->player->yspeed = -NORM_SPEED;
    
  } else {
    hero->player->xspeed = 0;
    hero->player->yspeed = 0;
  }

  /**** action button pressed ****/
  if (key[KEY_X]) {
    switch (currentmap->idnumber) {
    case TCA_13:
      /* hero is in position to open chest */
      
      break;
    }
  }
}
