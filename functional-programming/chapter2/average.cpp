#include <iostream>
#include <vector>
#include <numeric>

double average_score(const std::vector<int>& scores)
{
  return std::accumulate(scores.cbegin(), scores.cend(), 0) / (double) scores.size();
}

int main()
{
  std::vector<int> v{1,2,3};
  double res = average_score(v);
  std::cout << res;
  return 0;
}
