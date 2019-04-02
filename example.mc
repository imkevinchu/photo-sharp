int a;
int b;
a = 18;
b = 9;

while (a != b) {
  if (b < a) a = a - b;
  else b = b - a;
}

a = a;
