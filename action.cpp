#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

#include "action.h"
#include "scenario.h"
#include "data.h"

using namespace std;

action::action(const string& a,const string& b,map<string,bool> c, int d,map<string,bool> e,map<string,string> f) {
	action_trigger = a;
	success_desc = b;
	changes = c;
	scene_change = d;
	a_conditions = e;
	a_fails = f;
}

string action::init_result() {
	typedef map<string,bool>::iterator it_type;
	for (it_type iterator = a_conditions.begin(); iterator != a_conditions.end(); iterator++) {
		if (conditions[iterator->first] != iterator->second) {
			string failure = a_fails[iterator->first];
			if (failure[0] == '|') {
				return play_sequence(failure);
			}
			else {
				return failure; 
			}
		}
	}
	for (it_type iterator = changes.begin(); iterator != changes.end(); iterator++) {
		conditions[iterator->first]=iterator->second;
	}
	if (scene_change != -1) {
		scenario_num = scene_change;
		if (success_desc[0] != '|') {
			return scenarios[scenario_num].describe_scene();
		}
	}
	if (success_desc[0] == '|') {
		return play_sequence(success_desc);
	}
	else {
		return success_desc;
	}
}

string action::get_action_trigger() {
	return action_trigger;
}

void action::set_action_trigger(string act) {
	action_trigger = act;
}

string action::play_sequence(string text) {
		string substring = text.substr(1,text.size()-1);
		int mark = substring.find('|');
		while (mark != -1) {
			cout << substring.substr(0,mark) << endl << "(Press enter to continue)" << endl;
			string cont;
			getline(cin,cont);
			substring = substring.substr(mark+1,substring.size()-mark);
			mark = substring.find('|');
			system("clear");
		}
		return substring;

}