#include <sstream>

#include "mylib.h"

A::A(size_t size)
{
  v.reserve(size);
}

bool A::insert(int x, std::string str)
{
  if (x < 0)
    return false;

  v.push_back({ x, str });

  return true;
}

bool A::empty() const
{
  return v.empty();
}

std::string A::getStrRepr() const
{
  using std::stringstream;
  stringstream ss;

  if (v.empty())
  {
    ss << "{}";
    return ss.str();
  }

  ss << "{";

  bool first = true;
  for (const auto& elem : v)
  {
    if (first)
      first = false;
    else
      ss << ", ";

    ss << elem.x << ": \"" << elem.str << "\"";
  }

  ss << "}";

  return ss.str();
}