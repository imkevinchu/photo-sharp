#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ImageArr {
  double h;
  double w;
  struct pixel **imgPixelData;
};

struct pixel {
  double red;
  double green;
  double blue;
  double alpha;
};

void Brightness(struct ImageArr* img, double value) {

  for(int i = 0; i < img->h; i++) {

    for(int y = 0; y< img->w; y++) {
      img->imgPixelData[i][y].red = img->imgPixelData[i][y].red + value < 255 ? img->imgPixelData[i][y].red + value : 255;
      img->imgPixelData[i][y].green = img->imgPixelData[i][y].green + value < 255 ? img->imgPixelData[i][y].green + value : 255;
      img->imgPixelData[i][y].blue = img->imgPixelData[i][y].blue + value < 255 ? img->imgPixelData[i][y].blue + value : 255;
    }
  }
}

void GrayScale(struct ImageArr* img) {

  for(int i = 0; i < img->h; i++) {

    for(int y = 0; y< img->w; y++) {
      double gamma = 0.0;

      //compute the linear transform variable
      double red = img->imgPixelData[i][y].red / 255.0;
      double green = img->imgPixelData[i][y].green / 255.0;
      double blue = img->imgPixelData[i][y].blue / 255.0;

      double c_linear = 0.2126*red + 0.7152*green + 0.0722*blue;

      //compute the nonlinear gamma correction variable
      if(c_linear <= 0.0031308) {
        gamma = 12.92 * c_linear;
      }
      else {
        gamma = 1.055 * pow(c_linear, 1/2.4) - 0.055;
      }

      //Set each RGB of a pixel to the conventional non-linear rep: gamma
      img->imgPixelData[i][y].red = gamma * 255;
      img->imgPixelData[i][y].green = gamma * 255;
      img->imgPixelData[i][y].blue = gamma * 255;

    }
  }

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
  struct ImageArr *img = malloc(sizeof(struct ImageArr));

  img->h = 2.0;
  img->w = 2.0;
  img->imgPixelData[0][1].red = 10.0;
  img->imgPixelData[0][1].green = 20.0;
  img->imgPixelData[0][1].blue = 30.0;
  img->imgPixelData[0][1].alpha = 40.0;
  img->imgPixelData[0][0].red = 10.0;
  img->imgPixelData[0][0].green = 20.0;
  img->imgPixelData[0][0].blue = 30.0;
  img->imgPixelData[0][0].alpha = 40.0;
  img->imgPixelData[1][1].red = 10.0;
  img->imgPixelData[1][1].green = 200.0;
  img->imgPixelData[1][1].blue = 30.0;
  img->imgPixelData[1][1].alpha = 40.0;
  img->imgPixelData[1][0].red = 10.0;
  img->imgPixelData[1][0].green = 20.0;
  img->imgPixelData[1][0].blue = 30.0;
  img->imgPixelData[1][0].alpha = 40.0;

  //Brightness(img, 30.0);
  GrayScale(img);

  //struct ImageArr *returnPointer;

  //returnPointer = CropDimensions(img, 2.0, 4.0, 2.0, 4.0);


  printf("%f\n", img->imgPixelData[0][0].green);
  printf("%f\n", img->imgPixelData[0][0].blue);
  printf("%f\n", img->imgPixelData[0][0].red);

  free(img);
  //free(returnPointer);


}
