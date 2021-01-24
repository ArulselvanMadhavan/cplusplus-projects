
#include <iostream>
#include <ostream>
using namespace std;

char raise_question() {
  char response;
  cout << "Print Asterisks(Y/N)?";
  cin >> response;
  return response;
}

int main() {

  int numAsterisks;

  cout << "Assignment#1";
  char response = raise_question();
  while (response != 'N') {
    cout << "How many asterisks?";
    cin >> numAsterisks;
    for (int i = 0; i < numAsterisks; i++) {
      cout << "*";
    }
    cout << endl;
    response = raise_question();
  }
  return 0;
}
