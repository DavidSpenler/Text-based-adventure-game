#include <string>
#include <vector>
#include <map>
#include <utility>

#include "scenario.h"

using namespace std;

extern vector< vector<string>> synonyms;
extern map<string,bool> conditions;
extern vector<scenario> scenarios;
extern int scenario_num;
extern vector<action> universal_fails;
extern map<string,string> inventory;
