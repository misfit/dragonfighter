#include "common.h"

void setup_game (void) {
  allegro_init(); 
  install_keyboard(); 
  install_timer();
  srand(time(NULL));
  setup_screen();
  setup_player();
}

void setup_player (void) {
  BITMAP *temp;
  
  /* initialize attributes */
  player = (SPRITE*) malloc (sizeof (SPRITE));
  player->x = 0;
  player->y = 0;
  player->xspeed = 0;
  player->dir = 3;
  player->curframe = 0;
  player->maxframe = 1;
  player->framecount = 0;
  player->framedelay = 5;
  player->animdir = 0;
  
  /* load images */
  int i;
  temp = load_bitmap ("characters.bmp", NULL);
  for (i = 0; i < 2; i++) {
    player_down_bmps[i] = grabframe (temp, 32, 32, 0, 0, 32, i);
    player_up_bmps[i] = grabframe (temp, 32, 32, 0, 0, 32, i+2);
    player_right_bmps[i] = grabframe (temp, 32, 32, 0, 0, 32, i+4);
    player_left_bmps[i] = grabframe (temp, 32, 32, 0, 0, 32, i+6);
  }
  destroy_bitmap(temp);
  
  /* center the sprite in the scroll window. */
  player->x = SCROLLW/2;
  player->y = SCROLLH/2;
}

void setup_screen (void) {
  
  set_color_depth (24);
  
  if ((set_gfx_mode (MODE, WIDTH, HEIGHT, 0, 0)) != 0) {
    allegro_message (allegro_error);
    return;
  }
  
  if ((scroll = create_bitmap (TTRW, TTRH)) == NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
    allegro_message ("Error creating virtual background");
    return;
  }
  
  if ((buffer = create_bitmap(WIDTH, HEIGHT)) == NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
    allegro_message ("Error creating double buffer");
    return;
  }
  
  load_map (TTRL0);

  /* position player. */
  scrollx = 0;
  scrolly = 0;
  
  /* position the scroll window */
  startx = 0;
  starty = 0;
}
