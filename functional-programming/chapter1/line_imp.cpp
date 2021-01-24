#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>


int count_lines(const std::string& filename)
{
  std::ifstream in(filename);
  return std::count(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(),'\n');
}

std::vector<int>
count_lines_in_files(const std::vector<std::string>& files)
{
  std::vector<int> results;
  char c = 0;

  for (const auto& file:files) {
    int line_count = 0;
    std::ifstream in(file);
    while(in.get(c)){
      if(c == '\n'){
        line_count++;
      }
    }
    results.push_back(line_count);
  }
  return results;
}

int main()
{
  std::vector<std::string> v;
  v.push_back("test.txt");
  std::cout << count_lines_in_files(v).front();
}
