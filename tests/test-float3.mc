void testfloat(float a, float b):
{
  print(a + b)
  print(a - b)
  print(a * b)
  print(a / b)
  print(a == b)
  print(a == a)
  print(a != b)
  print(a != a)
  print(a > b)
  print(a >= b)
  print(a < b)
  print(a <= b)
}

int main():
{
  float c
  float d

  c = 42.0
  d = 3.14159

  testfloat(c, d)

  testfloat(d, d)

  return 0
}
