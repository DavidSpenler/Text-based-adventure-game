#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

using namespace std;

#ifndef RESPONSE
#define RESPONSE

struct response {
	string response;
	vector<map<string,bool>> conditions;
	vector<map<string,bool>> changes;
	int scene_change;
	response(string,vector<map<string,bool>><vector<map<string,bool>>,int);
};

#endif
