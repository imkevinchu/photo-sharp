#include <stdio.h>

struct pixel {
  int red;
  int green;
  int blue;
};

struct pixel makePix() {
  struct Pixel *p = (struct Pixel *)malloc(sizeof(struct Pixel)); 
  
  p->red = 255;
  p->green = 255;
  p->blue = 255;

}

void printPix(struct pixel *pix) {

  printf("Red: %d\n", pix->red);
  printf("Green: %d\n", pix->green);
  printf("Blue: %d\n", pix->blue);
}

int main() {
  struct pixel p = { 255, 255, 255 };
  
  printPix(&p);

  return 0;
}
