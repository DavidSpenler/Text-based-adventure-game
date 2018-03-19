#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <initializer_list>

#include "action.h"
#include "scenario.h"
#include "data.h"

using namespace std;

action::action(const string& a,const string& b,map<string,bool> c, int d,vector<pair<string,bool>> e,map<string,string> f, int g) {
	action_trigger = a;
	success_desc = b;
	changes = c;
	scene_change = d;
	a_conditions = e;
	a_fails = f;
	a_score  = g;
}

string action::init_result() {
	typedef map<string,bool>::iterator it_type;
	string response = success_desc;
	bool valid = true;
	for (unsigned int i=0; i < a_conditions.size(); i++) {
		if (conditions[a_conditions[i].first] != a_conditions[i].second) {
			response = a_fails[a_conditions[i].first];
			valid = false;
		}
	}
	if (valid) {
		for (it_type iterator = changes.begin(); iterator != changes.end(); iterator++) {
			conditions[iterator->first]=iterator->second;
		}
		if (scene_change != -1) {
			scenario_num = scene_change;
		}
		score+=a_score;
		a_score = 0;
	}
	if (response[0] == '#') {
		cout << "Dungeon Quest" << "\tScore: " << score << "/48\n" << endl;
		return play_death(response);
	}
	if (response[0] == '|') {
		if (scene_change != -1 && valid) {
			response = play_sequence(response+"|");
		}
		else {
			response = play_sequence(response);
		}
	}
	if (scene_change != -1 && valid) {
		return scenarios[scenario_num].describe_scene();
	}
	else {
		cout << "Dungeon Quest" << "\tScore: " << score << "/48\n" << endl;
		return response;
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
			cout << "Dungeon Quest" << "\tScore: " << score << "/48\n" << endl;
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
	cout << text.substr(1,text.length()-1) << endl << "(Press enter to continue)" << endl;
	string cont;
	getline(cin,cont);
	system("clear");
	cout << "Dungeon Quest" << "\tScore: " << score << "/48\n" << endl;
	scenario_num = 21;
	return "You are dead. Type 'restart' to start a new game. or load 1,2,3 to restore a saved game from one of three files";
}
