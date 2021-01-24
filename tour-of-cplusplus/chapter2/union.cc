
#include <iostream>
#include <string>
#include <variant>

enum Type {ptr, num};

class Node{
  private:
  int id;

  public:
  Node(int i): id {i} {}
  int getid() { return id;}
};

union Value {
  Node* p;
  int i;
};

struct Entry {
  std::string name;
  std::variant<Node *, int> v;
  // variant<Node*, int> v;
};


void f(Entry* pe)
{ 
  if(std::holds_alternative<int>(pe -> v))
    std::cout << std::get<int>(pe -> v);
}

int main()
{
  
  return 0;
}
