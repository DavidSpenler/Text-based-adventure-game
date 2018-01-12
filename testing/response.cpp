using namespace std;

typedef map<string,bool>::iterator it;

response::response(string a,map<string,bool> b,map<string,bool> c,int d) {
	response_text = a;
	conditions = b;
	changes = c;
	scene_change = d;	
}

void response::build_condition_code() {
	int condition_code;
	file.seekp(0);
	it i = conditions.begin();
		for (unsigned int j=0;j<sizeof(int)*8;j++) {
			if (i==conditions.end()) {
				break;
			}
			if (i->second == true) {
				condition_code|=(1 << j);
			}
			else {
			}
			i++;
		}
	}
}
