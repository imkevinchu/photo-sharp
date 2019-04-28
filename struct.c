#include <stdio.h>
#include <stdlib.h>

struct pixel {
  int red;
  int green;
  int blue;
};


struct pixel *makePix() {
  struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel)); 
  
  p->red = 255;
  p->green = 255;
  p->blue = 255;
  
  return p;

}

void printPix(struct pixel *pix) {

  printf("Red: %d\n", pix->red);
  printf("Green: %d\n", pix->green);
  printf("Blue: %d\n", pix->blue);
}

int main() {
  struct pixel *p = makePix();
  
  printPix(p);

  return 0;
}
