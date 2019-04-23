preset int a
preset bool b

preset void foo(int c, bool d):
{
  int d
  bool e
  b + a
  /* Error: bool + int */
}

preset int main():
{
  return 0
}
