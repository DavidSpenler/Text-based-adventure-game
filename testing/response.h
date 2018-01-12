#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

using namespace std;

#ifndef RESPONSE
#define RESPONSE

struct response {
	string response_text;
	map<string,bool> conditions;
	map<string,bool> changes;
	int scene_change;
	int condition_code;
	response(string,map<string,bool>,map<string,bool>,int);
	void build_condition_code();
};

#endif
