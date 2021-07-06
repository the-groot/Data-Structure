#include <iostream>
#include "WhoAmI.h"

int main() {
	WhoAmI obj1(1);
	WhoAmI obj2(2);
	WhoAmI obj3(3);

	obj1.ShowYourself();
	obj2.ShowYourself();
	obj3.ShowYourself();

	cout << "&obj1=" << &obj1 << endl;
	cout << "&obj2=" << &obj2 << endl;
	cout << "&obj3=" << &obj3 << endl;
return 0;
}