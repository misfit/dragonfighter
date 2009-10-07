#include "common.h"

void get_input (void) {
  if (key[KEY_RIGHT]) {
    player->direction = RIGHT;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2){
      player->xspeed = PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->xspeed = NORM_SPEED;
    
  } else if (key[KEY_LEFT]) {
    player->direction = LEFT;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2) {
      player->xspeed = -PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->xspeed = -NORM_SPEED;
    
  } else if (key[KEY_DOWN]) {
    player->direction = DOWN;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2) {
      player->yspeed = PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->yspeed = NORM_SPEED;
    
  } else if (key[KEY_UP]) {
    player->direction = UP;
    if (currentmap->idnumber == ALEFGARD1 || 
	currentmap->idnumber == ALEFGARD2) {
      player->yspeed = -PLAINS_SPEED;
      player->framedelay = 5;
    }
    else player->yspeed = -NORM_SPEED;
    
  } else {
    player->xspeed = 0;
    player->yspeed = 0;
  }
}
