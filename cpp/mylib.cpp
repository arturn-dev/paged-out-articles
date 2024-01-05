#include "mylib.h"

bool A::insert(int x, std::string str)
{
  if (x < 0)
    return false;

  v.push_back({ x, str });

  return true;
}

bool A::empty()
{
  return v.empty();
}