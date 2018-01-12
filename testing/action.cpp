#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

#include "action.h"
#include "scenario.h"
#include "data.h"
#include "response.h"

using namespace std;

action::action(const string& a,vector<response> b) {
	action_trigger = a;
	responses = b;
}

string action::init_result() {
	typedef map<string,bool>::iterator it_type;
	/*for (it_type iterator = a_conditions.begin(); iterator != a_conditions.end(); iterator++) {
		if (conditions[iterator->first] != iterator->second) {
			string failure = a_fails[iterator->first];
			if (failure[0] == '|') {
				return play_sequence(failure);
			}
			else if (failure[0] == '#') {
				return play_death(failure);
			}
			else {
				return failure; 
			}
		}
	}*/
	bool valid;
	response* this_response;
	for (int i=0;i<responses.size();i++) {
		for (int i=0;i<responses.size();i++) {
			valid = true;
			for (it_type j=responses[i].conditions.begin();j!=responses[i].conditions.end();j++) {
				if (j->second != conditions[j->first]) {
					valid = false;
					break;	
				}
			}
		}
		if (valid) {
			this_response = &responses[i];
			break;		
		}
	}
	/*for (it_type iterator = changes.begin(); iterator != changes.end(); iterator++) {
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
	}*/
	for (it_type i = this_response->changes.begin(); i != this_response->changes.end(); i++) {
		conditions[i->first] = i->second;
	}

	if (this_response->response_text[0] == '|') {
		string last_line = play_sequence(this_response->response_text);
		if (this_response->scene_change == 0) {
			return last_line;	
		}		
	}
	
	if (this_response->scene_change != -1) {
		scenario_num = this_response->scene_change;
		return scenarios[scenario_num].describe_scene();
	}
	
	if (this_response->response_text[0] == '#') {
		return play_death(this_response->response_text);
	}
	return this_response->response_text;
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
		if (substring[0] == '#') {
			return play_death(substring);
		}
		else {
			return substring;
		}
}

string action::play_death(string text) {
	cout << text.substr(1,text.length()-1) << "(Press enter to continue)" << endl;
	string cont;
	getline(cin,cont);
	system("clear");
	scenario_num = -1;
	return "You are dead. Type 'restart' to start a new game. or load 1,2,3 to restore a saved game from one of three files";
}
