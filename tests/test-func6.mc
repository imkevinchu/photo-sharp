preset void foo():
{
}

preset int bar(int a, bool b, int c):
{ 
  return a + c 
}

preset int main():
{
  print(bar(17, false, 25))
  return 0
}
