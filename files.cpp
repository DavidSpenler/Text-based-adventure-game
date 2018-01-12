#include <fstream>
#include <iostream>
#include <map>

#include "data.h"

using namespace std;

typedef map<string,bool>::iterator it;

void load_data(int num) {
	string file_name = "file"+to_string(num)+".save";
	int num_bytes = 0;
	fstream file(file_name,ios::in|ios::binary);
	file.seekg(0,ios::beg);
	if (!file.is_open()) {
		cout << "Error while opening file" << endl;	
	}
	else {
		char byte;
		//int i = 0;
		it i=conditions.begin();
		while (i!=conditions.end()) {
			num_bytes++;
			file.read(&byte,sizeof(char));	
			for (unsigned int j=0;j<sizeof(char)*8;j++) {
				if (i != conditions.end()) {
					if ((byte & 1<<j) != 0) {
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
		}
		file.read((char*) &scenario_num,sizeof(int));
		file.close();
		cout << ":" << scenario_num << endl;
		cout << num_bytes << "s bytes used" << endl;
	}
}

void save_data(int num) {
	string file_name = "file"+to_string(num)+".save";
	int num_bytes = 0;
	fstream file(file_name,ios::out|ios::binary);
	file.seekp(0,ios::end);
	if (!file.is_open()) {
		cout << "Error while opening file" << endl;
	}
	else {
		char byte;
		it i = conditions.begin();
		while (i!=conditions.end()) {
			num_bytes++;
			byte = 0; 
			for (unsigned int j=0;j<sizeof(char)*8;j++) {
				if (i!=conditions.end()) {
					if (i->second == true) {
						cout << 1;
						byte|=(1 << j);
					}
					else {
						cout << 0;
					}
					i++;
				}
			}
			file.write(&byte,sizeof(char));
		}
		file.write((char*) &scenario_num,sizeof(int));
		file.close();
		cout << ":" << scenario_num << endl;
		cout << num_bytes << "s bytes used" << endl;
	}
}
