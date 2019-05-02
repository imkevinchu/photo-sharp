#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imageArr.c"


void Brightness(struct ImageArr* img, int value) {

  for(int i = 0; i < (img->h)*(img->w); i++) {

    img->imgPixelData[i]->red = img->imgPixelData[i]->red + value < 255 ? img->imgPixelData[i]->red + value : 255;
    img->imgPixelData[i]->blue = img->imgPixelData[i]->blue + value < 255 ? img->imgPixelData[i]->blue + value : 255;
    img->imgPixelData[i]->green = img->imgPixelData[i]->green + value < 255 ? img->imgPixelData[i]->green + value : 255;

  }
  save("new.jpg", img);
}

void GrayScale(struct ImageArr* img) {

  for(int i = 0; i < (img->h)*(img->w); i++) {
    double gamma = 0;

    //compute the linear transform variable
    double red = img->imgPixelData[i]->red / 255;
    double green = img->imgPixelData[i]->green / 255;
    double blue = img->imgPixelData[i]->blue / 255;

    double c_linear = 0.2126*red + 0.7152*green + 0.0722*blue;

    //compute the nonlinear gamma correction variable
    if(c_linear <= 0.0031308) {
      gamma = 12.92 * c_linear;
    }
    else {
      gamma = 1.055 * pow(c_linear, 1/2.4) - 0.055;
    }

    //Set each RGB of a pixel to the conventional non-linear rep: gamma
    img->imgPixelData[i]->red = (int)(gamma * 255);
    img->imgPixelData[i]->green = (int)(gamma * 255);
    img->imgPixelData[i]->blue = (int)(gamma * 255);

  }
  save("new.jpg", img);

}

struct ImageArr *CropPercentage(struct ImageArr* img, double value) {
  double startdx, enddx, startdy, enddy;

  startdx = img->w;
  startdy = img->h;
  enddx = (double)((long)(startdx) * value / 100);
  enddy = (double)((long)(startdy) * value / 100);

  struct ImageArr *newImg = malloc(sizeof(struct ImageArr));

  for(int i = startdy - enddy / 2; i <= enddy - 1; i++) {

    for(int y = startdx - enddx / 2; y <= enddx - 1; y++) {
      newImg->imgPixelData[y][i] = img->imgPixelData[y][i];
    }
  }

  return newImg;

}

struct ImageArr *CropDimensions(struct ImageArr* img, double newstartdx, double newenddx, double newstartdy, double newenddy) {
  double w, h;

  double crop_w = newenddx - newstartdx + 1;
  double crop_h = newenddy - newstartdy + 1;

  //struct ImageArr *newImg = malloc((crop_h*crop_w) *sizeof(double));
  struct ImageArr *newImg = malloc(sizeof(struct ImageArr));
  for(int i = newstartdy; i <= newenddy; i++) {

    for(int y = newstartdx; y <= newenddx; y++) {
      newImg->imgPixelData[y][i] = img->imgPixelData[y][i];
    }
  }

  return newImg;
}



int main() {
  //struct ImageArr *img = malloc(sizeof(struct ImageArr));

  // img->h = 2.0;
  // img->w = 2.0;
  // img->imgPixelData[0][1].red = 10.0;
  // img->imgPixelData[0][1].green = 20.0;
  // img->imgPixelData[0][1].blue = 30.0;
  // img->imgPixelData[0][1].alpha = 40.0;
  // img->imgPixelData[0][0].red = 10.0;
  // img->imgPixelData[0][0].green = 20.0;
  // img->imgPixelData[0][0].blue = 30.0;
  // img->imgPixelData[0][0].alpha = 40.0;
  // img->imgPixelData[1][1].red = 10.0;
  // img->imgPixelData[1][1].green = 200.0;
  // img->imgPixelData[1][1].blue = 30.0;
  // img->imgPixelData[1][1].alpha = 40.0;
  // img->imgPixelData[1][0].red = 10.0;
  // img->imgPixelData[1][0].green = 20.0;
  // img->imgPixelData[1][0].blue = 30.0;
  // img->imgPixelData[1][0].alpha = 40.0;

  struct ImageArr *img;

  img = open("road.jpg");
  //printImageArr(img);

  //Brightness(img, 100);
  //GrayScale(img);
  img = CropPercentage(img, 60.0);
  save("new.jpg", img);

  //struct ImageArr *returnPointer;

  //returnPointer = CropDimensions(img, 2.0, 4.0, 2.0, 4.0);


  free(img);
  //free(returnPointer);


}
