#include <iostream>
struct Vector {
  int sz;
  double* elem;
};

void vector_init(Vector &v, int s)
{
  v.elem = new double[s]; // array of s double
  v.sz = s;
}

double read_and_sum(int s)
{
  Vector v;
  vector_init(v, s);
  for(int i=0; i!=s; ++i)
    std::cin >> v.elem[i];
  double sum = 0;
  for(int i=0; i!=s; ++i)
    sum += v.elem[i];
  return sum;
}

int main()
{
  double res = read_and_sum(3);
  std::cout << res;
  return 0;
}
