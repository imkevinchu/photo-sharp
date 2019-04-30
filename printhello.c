#include <stdio.h>



void printhello(int x)
{
  printf("Hello World");
}


#ifdef BUILD_HELLO
int main()
{
  printhello();

  return 0;

}
#endif
