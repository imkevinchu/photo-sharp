preset void foo(int a, bool b):
{
}

preset int main():
{
  foo(42, true)
  foo(42, true, false)
  /* Wrong number of arguments */
}
