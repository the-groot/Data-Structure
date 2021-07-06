#include <iostream>

using namespace std;

class WhoAmI {
public:
	int id;

	WhoAmI(int id_arg);
	void ShowYourself() const;
};


WhoAmI::WhoAmI(int id_arg) {
	id = id_arg;
}

void WhoAmI::ShowYourself() const {
	cout << "{ID=" << id <<"this="<<this << endl;
}