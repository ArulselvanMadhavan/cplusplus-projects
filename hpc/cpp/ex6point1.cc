// g++ -o ex6point1.o --std=c++17 ex6point1.cc
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

  struct hashFunction {
    size_t operator()(const std::tuple<int, int, int>&x) const{
      return std::get<0>(x) ^ std::get<1>(x) ^ std::get<2>(x);
    };
  };

// Function to print unordered set elements
void print(unordered_set<tuple<int, int,
           int>, hashFunction > &unorderedSetOfTuples)
{ 
  // Iterating over unorderedSetOfTuples elements
  for (auto currentTuple : unorderedSetOfTuples)
  {
    // Each element is a tuple itself
    tuple<int, int, int> tp = currentTuple;
  
    cout << "[ ";
  
    // Printing tuple elements
    cout << get<0>(tp) <<
      " , " << get<1>(tp) <<
      " , " << get<2>(tp) ;
    cout << " ]";
  
    cout << "\n";
  }
  
}

int main() {

    unordered_set<std::tuple<int, int, int>, hashFunction> triplets;
  int bound = 100;
  for(int u = 0; u < bound; u++){
    for(int v = 0; v < bound; v++){
      for(int w = 0; w < bound; w++){
        int result = (u * u + v * v + w * w);
        if(result == 100){
          std::tuple<int,int,int> uvw = std::make_tuple(u,v,w);
          std::tuple<int,int,int> vwu = std::make_tuple(v,w,u);
          std::tuple<int,int,int> wuv = std::make_tuple(w,u,v);
          if(triplets.count(uvw) > 0){
            continue;
          } else if(triplets.count(vwu) > 0){
            continue;
          } else if(triplets.count(wuv) > 0){
            continue;
          } else{
          triplets.insert(uvw);
          }
        }
      }
    }
  }

  print(triplets);
  return 0;
}
