#include "common.h"

int inside(int x,int y,int left,int top,int right,int bottom) {
  if (x > left && x < right && y > top && y < bottom) return 1;
  else return 0;
}

BITMAP *grabframe(BITMAP *source, 
                  int width, int height, 
                  int startx, int starty, 
                  int columns, int frame)
{
  BITMAP *temp = create_bitmap(width,height);
  int x = startx + (frame % columns) * width;
  int y = starty + (frame / columns) * height;
  blit(source,temp,x,y,0,0,width,height);
  return temp;
}

