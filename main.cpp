#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>

#include "scenario.h"
#include "data.h"
#include "files.h"

typedef map<string,bool>::iterator it;

using namespace std;

void write_data() {
	typedef map<string,bool>::iterator it_sb;
	typedef map<string,string>::iterator it_ss;

	fstream file("data.dat",ios::out|ios::binary);	
	file.seekp(0,ios::beg);
	if (!file.is_open()) {
		cout << "Error while opening file" << endl;
	}
	else {
		//file.read((*char)actions_size,sizeof(int));
		size_t synonyms_size  = synonyms.size();
		size_t universal_fails_size  = universal_fails.size();
		size_t scenarios_size = scenarios.size();

		size_t conditions_size = conditions.size();
		size_t inventory_size = inventory.size();
		

		file.write((char*)&synonyms_size,sizeof(int));
		file.write((char*)&universal_fails_size,sizeof(int));
		file.write((char*)&scenarios_size,sizeof(int));

		file.write((char*)&conditions_size,sizeof(int));
		file.write((char*)&inventory_size,sizeof(int));

		file.write((char*)&synonyms[0],synonyms_size);
		file.write((char*)&universal_fails[0],universal_fails_size);
		file.write((char*)&scenarios[0],scenarios_size);

		it_sb i1 = conditions.begin();
		it_ss i2 = inventory.begin();

		while (i1 != conditions.end()) {
			file.write((char*)&i1->first,sizeof(string));
			file.write((char*)&i1->second,sizeof(bool));
			i1++;
		}
		while (i2 != inventory.end()) {
			file.write((char*)&i2->first,sizeof(string));
			file.write((char*)&i2->second,sizeof(string));
			i2++;
		}
	}
}


int main() {
	
	//write_data();
	load_data();

	save_data(0);
	
	system("clear");

	string action;	

	cout << scenarios[scenario_num].describe_scene();

	while (true) {
		//sleep(1);
		cout << "What will you do next? >>>";
		getline(cin, action);
		//sleep(1);
		system("clear");
		cout << scenarios[scenario_num].take_action(action) << endl;
		sleep(1);
		cout << endl;
	}
}
