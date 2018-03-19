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

int main() {
	
	save_data(0);
	
	system("clear");

	string action;	

	cout << scenarios[scenario_num].describe_scene() << endl << endl;

	while (true) {
		cout << "What will you do next? >>>";
		getline(cin, action);
		system("clear");
		cout << scenarios[scenario_num].take_action(action) << endl;
		sleep(1);
		cout << endl;
	}
}
