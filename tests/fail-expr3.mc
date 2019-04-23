int a
float b

preset void foo(int c, float d):
{
  int d
  float e
  b + a
  /* Error: float + int */
}

preset int main():
{
  return 0
}
