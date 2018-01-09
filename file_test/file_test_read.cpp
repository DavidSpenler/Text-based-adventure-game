#include <fstream>
#include <iostream>

using namespace std;

int main() {
	int x;
	fstream file("datafile.bin",ios::in|ios::binary);
	if (file.is_open()) {
		file.read((char*)&x,sizeof(x));	
	}
	file.close();
	cout << x << endl;
	return 0;
}
