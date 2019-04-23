preset int foo(int a, bool b, int c):
{
}

preset void bar(int a, void b, int c):
{
}
/* Error: illegal void formal b */

preset int main():
{
  return 0
}
