#include <iostream>
#include <string>
using namespace std;

int main() {
	int a[26] = { 0 };
	int b[26] = { 0 };
	int a_index = 0; 
	int b_index = 0;

	string A, B;
	cin >> A;
	cin >> B;
	
	for (int i = 0; i < A.length(); i++) {
		 a_index= A[i] - 'a';
		 a[a_index]++;
	}

	for (int i = 0; i < B.length(); i++) {
		b_index = B[i] - 'a';
		b[b_index]++;
	}

	if (A.length() != B.length()) {
		cout << "no"<<endl;
		return 0;
	}
	else {
		for (int i = 0; i < 26; i++) {
			if (a[i] != b[i]) {
				cout << "no"<<endl;
				return 0;
			}
		}
	}


	cout << "yes"<<endl;;
	return 0;
}