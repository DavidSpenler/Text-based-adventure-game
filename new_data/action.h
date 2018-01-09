#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

using namespace std;

#ifndef ACTION
#define ACTION

class action {
	string action_trigger;
	vector<response> responses;
	public:
		action(const string&,vector<responses>);

#endif
