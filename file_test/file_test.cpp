#include <fstream>
#include <iostream>
#include <map>

#include "data.h"

using namespace std;

map<string,bool> conditions = {
	{"a",false},
	{"b",true},
	{"c",false},
	{"d",true},
	{"e",true},
	{"f",true},
	{"g",false},
	{"h",false},
	{"i",true},
	{"ab",true}
};

int scenario_num = 3;

typedef map<string,bool>::iterator it;

void load_data() {
	fstream file("test.bin",ios::in|ios::binary);
	if (!file.is_open()) {
		cout << "Error while opening file" << endl;	
	}
	else {
		char byte;
		file.seekg(0);
		it i=conditions.begin();
		while (i!=conditions.end()) {
			file.read(&byte,sizeof(char));	
			for (unsigned int j=0;j<sizeof(char);j++) {
				if (i == conditions.end()) {
					break;
				}
				if ((byte & 1<<j) == 1) {
					i->second = true;
					cout << 1;
				}
				else {
					i->second = false;
					cout << 0;
				}	
				i++;
			}
		}
		file.read((char*) &scenario_num,sizeof(int));
		file.close();
		cout << ":" << scenario_num << endl;
	}
}

void save_data() {
	fstream file("test.bin",ios::out|ios::binary);
	if (!file.is_open()) {
		cout << "Error while opening file" << endl;
	}
	else {
		char byte;
		//int i = 0;
		file.seekp(0);
		it i = conditions.begin();
		while (i!=conditions.end()) {
			byte = 0; 
			for (unsigned int j=0;j<sizeof(char);j++) {
				if (i==conditions.end()) {
					break;
				}
				if (i->second == true) {
					cout << 1;
					byte|=(1 << j);
				}
				else {
					cout << 0;
				}
				cout << i->first;
				i++;
			}
			file.write(&byte,sizeof(char));
		}
		file.write((char*) &scenario_num,sizeof(int));
		file.close();
		cout << ":" << scenario_num << endl;
	}
}

int main() {
	save_data();
	load_data();
	save_data();
	load_data();
	return 0;
}
