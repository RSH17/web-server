#include<iostream>
#include<cstring>
using namespace std;

struct hashTable{
    int key;
    string value;
    hashTable *next;
};

class Contacts{
    int num;        //number of entries.
    hashTable *phoneBook;
public:
    Contacts():phoneBook(NULL){
    }
    
    void ins(){
    	string name;
        int index;
        int phoneNumber;
        cout<<"enter number of entries: ";
        cin>>num;
        phoneBook=new hashTable[num];
        cout<<"Enter phone number & Name respectively:"<<endl;
        for(int i=0;i<num;i++){
            cin>>phoneNumber>>name;
            index=hashing(num,phoneNumber);
            if(phoneBook[index].isEmpty){        //if the slot is empty(no collision).
                phoneBook[index].key=phoneNumber;
                phoneBook[index].value=name;
                phoneBook[index].isEmpty=false;     //it is now filled.
                phoneBook[index].next=NULL;
            }
            else{           //in case of collision.
                hashTable *temp=&(phoneBook[index]);
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                temp->next=new hashTable;
                temp->next->key=phoneNumber;
                temp->next->value=name;
                temp->next->isEmpty=false;
                temp->next->next=NULL;
            }
        }
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
                cout<<"0"<<endl;
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
    d1.ins();
    cout<<"Enter number of telephone numbers you want to search: ";
    cin>>n;
    cout<<"Enter number: "<<endl<<endl;
    for(int i=1;i<=n;i++){
        cin>>phoneNumber;
        d1.searchContact(phoneNumber);
        cout<<endl;
    }
}
