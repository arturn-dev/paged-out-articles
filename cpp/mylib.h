#include <vector>
#include <string>

struct S {
  int x;
  std::string str;
};

class A
{
  std::vector<S> v;

public:
  bool insert(int x, std::string str);
  bool empty();
};