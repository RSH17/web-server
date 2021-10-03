#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main () {
	int phoneNumber;
    int n;	
    string name;
    string line;
    int num;

  ifstream myfile("PhoneBook.txt");

  while (!myfile.eof()) 
	{
	cout<<"Enter number of telephone numbers you want to search: ";
    cin>>n;
    cout<<"Enter number: "<<endl<<endl;
    for(int i=1;i<=n;i++){
        cin>>phoneNumber;
        myfile>>noskipws>>num;
            if(num==phoneNumber){
            	myfile>>noskipws>>line;
                cout<<"Phone number: "<<num<<endl;
                cout<<"Name: "<<line<<endl;
            }
            else{
                cout<<"0"<<endl;
            }
        	cout<<endl;
		}
	}
  return 0;
}
