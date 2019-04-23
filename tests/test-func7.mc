preset int a

preset void foo(int c):
{
  a = c + 42
}

preset int main():
{
  foo(73)
  print(a)
  return 0
}
