preset int foo():
{
}

preset int bar():
{
  int a
  void b
  /* Error: illegal void local b */
  bool c

  return 0
}

preset int main():
{
  return 0
}
