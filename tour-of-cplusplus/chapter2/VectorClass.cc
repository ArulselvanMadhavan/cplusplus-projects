
#include <iostream>
class Vector {
  private:
  double* elem;
  int sz;
  
  public:
  Vector(int s):elem{new double[s]},sz{s} {} //Construct a vector
  double& operator[](int i) { return elem[i]; }
  int size() { return sz; }
};

double read_and_sum(int s)
{
  Vector v(s);
  for(int i = 0; i != v.size(); ++i)
    std::cin >> v[i];
  double sum = 0;
  for(int i=0; i!=v.size(); ++i)
    sum += v[i];
  return sum;
}

int main()
{
  std::cout << read_and_sum(4);
  return 0;
}
