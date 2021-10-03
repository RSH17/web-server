#include<iostream>
#include<cstring>
using namespace std;

struct hashTable{
    int key;
    string value;
    bool isEmpty=true;
    hashTable *next;
};

class Contacts{
    int num;        //number of entries
    hashTable *phoneBook;
public:
    Contacts():phoneBook(NULL){
    }
    
    int hashing(int n,int phoneNumber){
        int len,sum=0;
        len = sizeof(phoneNumber)/4;
        int temp[len+1];
        //calculating hash value
        for(int i=0;i<len;i++){
            sum=sum+temp[i];
        }
        return (sum%n);
    }
    void searchContact(int phoneNumber){
        int check;
        string name;
        check=hashing(num,phoneNumber);

        if(phoneBook[check].next==NULL){        //if there is no collision seen in the current block.
            if(phoneBook[check].key==phoneNumber){
                cout<<"Phone number: "<<phoneBook[check].key<<endl;
                cout<<"Name: "<<phoneBook[check].value<<endl;
            }
            else{
                cout<<"Not found"<<endl;
            }
        }

        else{                                   //if collision is seen in the current block.
            hashTable *temp=&(phoneBook[check]);
            while(temp!=NULL){
                if(temp->key==phoneNumber){
                    cout<<"Phone number: "<<temp->key<<endl;
                    cout<<"Name: "<<temp->value<<endl;
                    break;
                }
                else
                    temp=temp->next;
            }
            if(temp==NULL)
                cout<<"0"<<endl;
        }
    }
    
    ~Contacts(){
        delete []phoneBook;
    }
};
int main(){
    int phoneNumber;
    int n;
    Contacts d1;
    cout<<"Enter number: "<<endl<<endl;
    string ch;
	const string fileName="PhoneBook.txt";
	
	
	//open file
	file.open(fileName,ios::in);
	if(!fileName)
	{
		cout<<"Error in opening file!!!"<<endl;
		return -1; //return from main
	}
	ifstream myfile("PhoneBook.txt");
	//read and print file content
	while (!myfile.eof()) 
	{
		file >> noskipws >> ch;	//reading from file
		d1.searchContact(phoneNumber);
	//	cout << ch;	//printing
	}
}
	//close the file
	file.close();
}
