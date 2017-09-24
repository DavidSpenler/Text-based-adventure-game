#include <string>
#include <vector>
#include <iostream>

#include "scenario.h"
#include "action.h"
#include "data.h"

using namespace std;

typedef map<string,string>::iterator it_type;


scenario::scenario(const string& a, vector<action> b) {
	desc = a;
	valid_actions = add_variances(b);
	valid_actions.insert(valid_actions.end(),universal_fails.begin(),universal_fails.end());
}
	 
vector<action> scenario::add_variances(vector<action> a) {
	
	vector<action> actions;
	vector<action> new_actions;	
	for (int x;x<a.size();++x) {
		if (a[x].get_action_trigger().find('(') != -1) {
			new_actions.push_back(a[x]);
		}
		else {
			actions.push_back(a[x]);
		}
	}
	int mark,start,mid,end,next;

	for (int i=0;i<a.size();++i) {
		
		string action_trigger = a[i].get_action_trigger();
		if (action_trigger.find('(') == -1) {
			actions.push_back(a[i]);
			continue;
		}

		mark = 0;
		start = action_trigger.find('(',mark);
		string a_root = action_trigger.substr(0,start);
		new_actions = {a[i]};
		new_actions[0].set_action_trigger(a_root);
		while (start != -1) {
			cout << "check" << endl;
			start = action_trigger.find('(',mark);
			mid = action_trigger.find('/',start);
			end = action_trigger.find(')',mid);
			next = action_trigger.find('(',end);
			string option_1 = action_trigger.substr(start+1,mid-(start+1));
			string option_2 = action_trigger.substr(mid+1,end-(mid+1));
			string shoot_a = action_trigger.substr(end+1,next-(end+1));
			cout << action_trigger << endl;
			cout << start << endl << mid << endl << end << endl;
			cout << option_1 << endl << option_2 << endl << shoot_a << endl;
			mark = end;
			start = next;
			vector<action> cache_actions = new_actions;
			new_actions = {};
			for (int x=0;x<cache_actions.size();++x) {
				string base_sequence = cache_actions[x].get_action_trigger();
				cache_actions[x].set_action_trigger(base_sequence+option_1+shoot_a);
				new_actions.push_back(cache_actions[x]);
				cache_actions[x].set_action_trigger(base_sequence+option_2+shoot_a);
				new_actions.push_back(cache_actions[x]);
			}
		}
		for (int i=0;i<new_actions.size();++i) {
			actions.push_back(new_actions[i]);
			cout << new_actions[i].get_action_trigger() << endl;
		}
	}
	return actions;
}

string scenario::describe_scene() {
	return valid_actions[0].init_result();	
}

string scenario::print_inventory() {
	string line;
	int line_num = 0;
	for (it_type iterator=inventory.begin();iterator != inventory.end();iterator++) {
		if (conditions["has_"+iterator->first] == true) {
			if (line_num >= 3) {
				cout << endl;
				line_num = 0;
			}
			cout << iterator->first+string(20-iterator->first.size(),' ');
			++line_num;
		}
	}
	return "\n";
}

string scenario::take_action(string action) {
	vector<string> action_words = segment(action);
	string core_action;
	bool matched = false;
	for (int i=0;i<action_words.size();++i) {
		matched = false;
		for (int i2=0;i2<synonyms.size();++i2) {
			for (int i3=0;i3<synonyms[i2].size();++i3) {
				if (synonyms[i2][i3] == action_words[i]) {
					core_action+=(synonyms[i2][0]+" ");
					matched = true;
				}
			}
		}
		if (i == 0 && not matched) {
			return "'"+action_words[0]+"' not recognized. Type 'help for assistance.'";
		}
	}
	core_action = core_action.substr(0,core_action.size()-1);
	cout << "'" << action << "', read as '" << core_action << "'" << endl;
	if (check_match(core_action,"*look inventory") == true) {
		return print_inventory();
	}
	for (it_type iterator = inventory.begin();iterator != inventory.end();iterator++) {
		if (core_action == "look "+iterator->first && conditions["has_"+iterator->first] == true) {
			return inventory[iterator->first];
		}
	}
	for (int i=0;i<valid_actions.size();++i) {
		if (check_match(core_action,valid_actions[i].get_action_trigger()) == true) {
			string response = valid_actions[i].init_result();
			return response;
		}
	}
	return "Command not recognized, type 'help' for assistance";
}

vector<string> scenario::segment(string action) {
	int mark = 0;
	int spaces = 0;

	while (mark != -1) {
		mark = action.find(" ",mark+1);
		++spaces;
	}
	
	vector<string> words;

	mark = 0;
	int num = 0;
	int size = 0;
	string action_copy = action;
	while (mark != -1) {
		size = action_copy.size();
		mark = action_copy.find(" ");
		string word = action_copy.substr(0,mark);
		words.push_back(word);
		action_copy = action_copy.substr(mark+1,(size-mark));

	}
	return words;
}

bool scenario::check_match(const string& action,const string& match) {
	vector<string> words_action = segment(action);
	vector<string> words_match = segment(match);
	vector<string> & words_largest = (words_action.size() >= words_match.size()) ? words_action : words_match;
	vector<string> & words_smallest = (words_action.size() < words_match.size()) ? words_action : words_match;
	int diff = words_largest.size()-words_smallest.size();
	for (int a=0;a<diff;++a) {
		if (words_smallest.size() > 0 && words_smallest[0] == "<any>") {
			words_smallest.push_back("<any>");
		}
		else {
			words_smallest.push_back("<filler>");
		}
	}
	for (int z=0;z<words_largest.size();++z) {
		if (words_action[z] == words_match[z]) {
			continue;
		}
		else if (words_match[z][0] == '*') {
			if (words_action[z] == words_match[z].substr(1,words_match[z].size()-1)) {
				continue;
			}
			else {
				words_action.insert(words_action.begin()+z/*-1*/,"<filler>");
			}
		}
		else if (words_match[z] == "<any>") {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}
