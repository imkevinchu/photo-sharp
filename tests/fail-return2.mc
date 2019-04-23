preset void foo():
{
  if (true):
  {
    return 42
    /* Should return void */
  }
  else:
  {
    return
  }
}

preset int main():
{
  return 42
}
