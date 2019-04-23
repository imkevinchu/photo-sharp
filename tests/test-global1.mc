preset int a
preset int b

preset void printa():
{
  print(a)
}

preset void printbb():
{
  print(b)
}

preset void incab():
{
  a = a + 1
  b = b + 1
}

preset int main():
{
  a = 42
  b = 21
  printa()
  printbb()
  incab()
  printa()
  printbb()
  return 0
}
