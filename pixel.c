#include <stdio.h>
#include <stdlib.h>

struct pixel {
  int red;
  int green;
  int blue;
  int alpha;
};

struct pixel *setPix(int r, int g, int b, int a) {
  struct pixel *p = (struct pixel *)malloc(sizeof(struct pixel));

  p->red = r;
  p->green = g;
  p->blue = b;
  p->alpha = a;

  return p;

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
