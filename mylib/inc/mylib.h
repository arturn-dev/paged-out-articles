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
  A(size_t size);

  bool insert(int x, std::string str);
  bool empty() const;
  std::string getStrRepr() const;
};