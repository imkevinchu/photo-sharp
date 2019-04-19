// C++ code for opening, cropping, and saving an image using ImageMagick

#include <Magick++.h> 
#include <iostream> 

using namespace std; 
using namespace Magick; 

int main(int argc,char **argv) 
{ 
  InitializeMagick(*argv);

  Image image;
  try { 
    image.read( "test.png" );

    // (width, height, xOffset, yOffset)
    image.crop( Geometry(200,200, 0, 0) );

    image.write( "image.png" ); 
  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    } 
  return 0; 
}