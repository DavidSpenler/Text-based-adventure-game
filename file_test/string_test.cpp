#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
	vector<string> list = {"apple","orange","banana"};
	for (int i=0;i<list.size();i++) {
		cout << list[i] << endl;
	}
	return 0;
}
