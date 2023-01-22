#include <iostream>
#include <vector>

void bubble_sort(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      int cur = arr[j];
      int next = arr[j + 1];
      if (cur > next) {
        arr[j + 1] = cur;
        arr[j] = next;
      }
    }
  }
}

int main(int argc, char **argv) {
  std::vector<int> arr = {3, 5, 1, 8, 2, 4, 5, 9, 11, 0};
  bubble_sort(arr.data(), 10);
  for (auto a : arr) {
    std::cout << a;
    std::cout << "\n";
  }
  return 0;
}
