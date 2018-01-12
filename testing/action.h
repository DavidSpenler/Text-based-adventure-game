#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

using namespace std;

#ifndef ACTION
#define ACTION

#include "response.h"

class action {
	string action_trigger;
	vector<response> responses;
	string play_death(string);
	string play_sequence(string);
	public:
		action(const string&,vector<response>);
		void set_action_trigger(string);
		string get_action_trigger();
		string init_result();
};

#endif
