#include <iostream>
//#include <string>
#include <cstring>
using namespace std;

#define SIZE 6
class Stack{
	char data_[SIZE];
	char top_;
public:
	Stack() {
			top_=0;
	}

	bool empty() {
			return top_==0;
	}
	bool full(){
		return top_==SIZE;
	}

	void push(int val){
		if(full()){
			cout << "Error : Stack Full.." << endl;
			return;
		}
		data_[top_++] = val;
	}
	char pop(){
		if(empty()){
			cout << "Error : Stack Empty.." << endl;
			return 0;
		}
		return data_[--top_];
	}


};

int main() {
	Stack st;

	cout << "Empty? " << st.empty() << endl;


    char s[7] = "string";
    cin >> s;
    cout << "Pushing...\n" << endl;
    for(int i = 0; i < strlen(s); i++){
        st.push(s[i]);
	}

    cout << "Full? " << st.full() << endl;
    cout << "Poping...\n" << endl;

	for(int i = 0; i < strlen(s); i++){
        cout << "We pulled the numer: " << st.pop() << endl;
	}

		cout << "\nEmpty? " << st.empty() << endl;

	//cout << "We pulled the numer: " << st.pop() << endl;
	//cout << "We pulled the numer: " << st.pop() << endl;
//Domashno ->String__stack podavame string na stack-a i da oburnem vuprosniq string

	return 0;
}
