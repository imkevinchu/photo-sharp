//Define the pixel class and associated 
//functions

struct pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
};

//Both are constructors -- make pix does not bother to 
//set RGBA values, while setPix initializes them to the 
//given values
struct pixel *makePix();
struct pixel *setPix(int r, int g, int b, int a);
void freePix(struct pixel*p);

//Modifiers to set the given pixel to a 
//Red, Blue, or Green
int RedPixel(struct pixel *p);
int GreenPixel(struct pixel *p);
int BluePixel(struct pixel *p);

void SetRGB(struct pixel* p, int r, int g, int b, int a);
void ModRGB(struct pixel* p, int redMod, int greenMod, int blueMod, int alphaMod);

void SetRed(struct pixel*p, int r);
void SetGreen(struct pixel*p, int g);
void SetBlue(struct pixel*p, int b);
void SetAlpha(struct pixel*p, int a);

void modRed(struct pixel*p, int rmod);
void modGreen(struct pixel*p, int gmod);
void modBlue(struct pixel*p, int bmod);
void modAlpha(struct pixel*p, int amod);

//Pixel editing functions
int PixelSaturate(struct pixel* px, int l);

//Printing function
void printPix(struct pixel *pix);
