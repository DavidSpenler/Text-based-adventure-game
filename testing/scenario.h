#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "action.h"

using namespace std;

#ifndef SCENARIO
#define SCENARIO

class scenario {
	string desc;
	vector<action> valid_actions;
	vector<string> segment(string);
	bool check_match(const string&,const string&);
	string print_inventory();
	vector<action> add_variances(vector<action>);
	string get_action_trigger(action);
	public:
		scenario(const string&,vector<action>);
		string describe_scene();
		string take_action(string);
};

#endif
