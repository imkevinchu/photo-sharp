#include <stdio.h>

int hello(int x) {
  printf("hello world\n");
  return 0;
}

#ifdef BUILD_TEST
int main() {
  hello(1);
  return 0;
}
#endif
