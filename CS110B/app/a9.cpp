

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
using namespace std;

string readline;
int players_count() {
  cout << "How many players do you want to sort?" << endl;
  int numPlayers;
  getline(cin, readline);
  stringstream(readline) >> numPlayers;
  return numPlayers;
}

int players_interaction() {
  int numPlayers = players_count();
  while (numPlayers < 2) {
    cout << "Invalid Input: Players count should be greater than 1" << endl;
    numPlayers = players_count();
  }
  cout << "Sorting Players: " << numPlayers << endl;
  return numPlayers;
}

struct Player {
  string name;
  int score;
};

Player updatePlayer() {
  string name;
  int score;
  cout << "Enter Player name: ";

  getline(cin, readline);
  name = readline;

  cout << "\nEnter Score:";
  getline(cin, readline);

  stringstream(readline) >> score;
  return Player{name, score};
}

int main() {
  cout << "Assignment#9" << endl;
  int numPlayers = players_interaction();
  Player players[numPlayers];
  for (int i = 0; i < numPlayers; i++) {
    Player p = updatePlayer();
    players[i] = p;
  }
  for (int i = 0; i < numPlayers; i++) {
    cout << players[i].name << players[i].score << "\n";
  }
  return 0;
}
