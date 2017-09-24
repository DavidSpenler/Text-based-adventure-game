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
	string success_desc;
	map<string,bool> changes;
	int scene_change;
	map<string,bool> a_conditions;
	map<string,string> a_fails;
	string play_sequence(string);
	public:
		action(const string&,const string&,map<string,bool> c={},int=-1,map<string,bool> d={},map<string,string> f={});
		string init_result();
		string get_action_trigger();
		void set_action_trigger(string);
};

#endif
