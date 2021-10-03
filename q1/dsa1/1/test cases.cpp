#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string ch;
  ifstream myfile("PhoneBook.txt");

  //myfile >> line;
  //cout << line;
  while (!myfile.eof()) 
	{
		
		myfile >> noskipws >> ch;	//reading from file
		cout << ch;	//printing
	}
  system("pause");
  return 0;
}
