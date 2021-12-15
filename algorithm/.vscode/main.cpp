#include <iostream>
#include <string>

using namespace std;

int main() {
	
	int T;
	cin >> T;
	int a, b;
	int** result;
	result = (int**)malloc(sizeof(int) * T);
	for (int i = 0; i < T; i++) {
		result[i] = (int*)malloc(sizeof(int)*10);
	}
	


	for (int i = 0; i < T; i++) {
		cin >> a;
		cin >> b;

		if (a == 1) {
			if (b == 2) {
				result[i][0] ='B';
			}

			else if (b == 3) {
				result[i][0] = 'A';
			}
		}
		else if (a == 2) {

			if (b == 1) {
				result[i][0] = 'A';
			}

			else if (b == 3) {
				result[i][0] = 'B';
			}
		}
		else if (a == 3) {
			if (b == 1) {
				result[i][0] = 'B';
			}
			else if (b == 2) {
				result[i][0] = 'A';
			}
		}

	}

	for (int i = 0; i < T; i++) {
		printf("#%d %c\n", i + 1,result[i][0]);
	}


	return 0;
}



