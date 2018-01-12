#include <string>

using namespace std;

#ifndef NEWMAP
#define NEWMAP

class new_map {
	string first;
	bool second;
	public:
		new_map(string,bool);
		string get_first();
		bool get_second();
};

#endif
