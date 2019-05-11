//header file for the ImageStack and ImageLayer classes
//and associated funcitons


//Struct declarations -- ImageLayer is a helper struct
struct ImageLayer {
    short h;
    short w;
    struct pixel **imgPixelData;
};

struct ImageStack {
    int top;
    struct ImageLayer **imgArray;
};

//Access functions
struct pixel *getPixel(struct ImageStack *img, int index);
int ImageSize(struct ImageStack *img);

//Stack functions
void pushLayer(struct ImageStack *img, struct ImageLayer *lay);
struct ImageLayer *popLayer(struct ImageStack *img);

//Create and free layers
void freeImageStack(struct ImageStack *stack);
void freeLayer(struct ImageLayer *lay);
struct ImageLayer *newImageLayer(int hi, int wi);
struct ImageStack *newImageStack();

//Opening and saving image files
struct ImageLayer *openFile(char *fileName);
struct ImageStack *open(char *fileName);
int save(char const *filename, struct ImageStack *img);

//Print pixels in an image
void PrintImage(struct ImageStack *img);

//Functions which interface with codegen and the library
void ImageContrast(struct ImageStack *img, int lev);
void ImageSaturate(struct ImageStack *img, int lev);
void ImageRotate90(struct ImageStack *img);
void ImageAddNoise(struct ImageStack *img, double var, double mean);
void ImageKelvin(struct ImageStack *img, double lev);
void ImageReflectY(struct ImageStack *img);
void ImageReflectX(struct ImageStack *img);
void ImageTint(struct ImageStack *img, int lev);
void ImageCrop(struct ImageStack *img, double p);





