#include <cmath>
#include <iostream>

class Point {
private:
  double x,y;
  double r,theta;

public:
  Point(double x, double y) {
    x = x;
    y=y;
    r = sqrt(x*x+y*y);
    theta = atan2(y, x);
  };

  void print(){
    std::cout << r << "|" << theta << "\n";
  }
};

int main(){
  Point p = Point(4, 5);
  p.print();
}
