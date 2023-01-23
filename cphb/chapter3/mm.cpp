#include <iostream>
#include <vector>

const int INF = 1000;
const std::vector<int> coins = {1,3,4};

int solve(int x) {
  if(x < 0) return INF;
  if(x == 0) return 0;
  int best = INF;
  for(auto c : coins) {
    std::cout << c;
  }
  return 0;
}

int main(int argc, char** argv){
  std::cout << argc;
  std::cout << "\n";
  
}
