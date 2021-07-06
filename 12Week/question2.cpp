#include <iostream>
#include <time.h>
using namespace std;

int MAX(int* value,int n);
int MIN(int* value,int n);


int main() {
	int N=0, X = 0;
	int* value = NULL;
	int max = 0; int min = 0;
	int count = 0;
	int maxvalue = 0;
	cin >> N >> X;
	srand(time(NULL));
	value = new int[N];
	for (int i = 0; i < N; i++) {
		value[i] = rand() % 1001 + 1000;
		cout << value[i]<<" ";
	}
    cout<<endl;
	max = MAX(value,N);
	min = MIN(value,N);
	
	count = X / min;

	maxvalue = X+(max - min) * count;
	cout << maxvalue << endl;

	delete value;
	return 0;
}

int MAX(int* value, int n) {
	int maxindex = 0;
	for (int i = 1; i < n; i++) {
		if (value[i] > value[maxindex]) {
			maxindex = i;
		}
	}

	return value[maxindex];
}

int MIN(int* value,int n) {
	int minindex = 0;
	for (int i = 1; i < n; i++) {
		if (value[i] < value[minindex]) {
			minindex = i;
		}
	}

	return value[minindex];
}