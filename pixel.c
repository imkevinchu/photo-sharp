#include <stdio.h>
#include <stdlib.h>

struct pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
};

struct pixel *setPix(int r, int g, int b, int a) {  
  struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel)); 

  p->red = (unsigned char)r;
  p->green = (unsigned char)g;
  p->blue = (unsigned char)b;
  p->alpha = (unsigned char)a;

  return p;

}

int RedPixel(struct pixel *p) {  

  p->red = 0;
  p->green = 0;
  p->blue = 255;
  p->alpha = 0;

  return 0;

}

struct pixel *makePix() {
  struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel)); 
  return p;

}

void printPix(struct pixel *pix) {

  printf("Red: %d\n", pix->red);
  printf("Green: %d\n", pix->green);
  printf("Blue: %d\n", pix->blue);
  printf("Alpha: %d\n", pix->alpha);
}

/*#ifdef BUILD_TEST
int main() {
  struct pixel *p;
  p = setPix(12, 3, 4, 10);  
  printPix(p);
  return 0;
}
#endif*/
