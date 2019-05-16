//Header file for the Photo# Image editing functions

//Helper structure for the HSL function
struct HSL
{
        float H;
        float S;
        float L;
};

//Helper functions
float Min(float a, float b);
float Max(float a, float b);

//Editing functions -- all malloc a new layer to return, and 
//do not modify the original
struct ImageLayer* Contrast(struct ImageLayer* img, int level);
struct ImageLayer* Saturate(struct ImageLayer* img, int l);
struct ImageLayer* Rotate90(struct ImageLayer *img);
struct ImageLayer* ReflectY(struct ImageLayer *m);
struct ImageLayer* ReflectX(struct ImageLayer *m);
struct ImageLayer *addNoise(struct ImageLayer *Im, float var, float mean);
struct ImageLayer *Tint(struct ImageLayer *img, int level);
struct ImageLayer *Crop(struct ImageLayer *img, float pct);
struct ImageLayer *Kelvin(struct ImageLayer *img, float K);
struct ImageLayer *Brightness(struct ImageLayer *img, int amt);

void GradContrast(struct ImageGradient *grad, int level);
void GradHSL(struct ImageGradient *grad, int factor, int hsl, int channel);
void GradToLayer(struct ImageStack *s, struct ImageGradient *grad);

struct HSL *RGBToHSL(struct pixel* rgb);
float HueToRGB(float v1, float v2, float vH);
struct pixel *HSLToRGB(struct HSL *hsl);
struct ImageLayer* HSL(struct ImageLayer *m, int factor, int hsl, int channel);


