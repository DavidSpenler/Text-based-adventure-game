#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>

#include "scenario.h"
#include "data.h"

using namespace std;


int main() {
	system("clear");

	string action;	

	cout << scenarios[scenario_num].describe_scene() << endl;
	while (true) {
		//sleep(1);
		cout << "What will you do next? >>>";
		getline(cin, action);
		//sleep(1);
		//system("clear");
		cout << scenarios[scenario_num].take_action(action) << endl;
		sleep(1);
	}
}
