#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  ifstream myfile("hey.txt");

  myfile >> line;
  cout << line;
  system("pause");
  return 0;
}
