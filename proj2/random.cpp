#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv){
	ofstream ofs;
	ofs.open("random.txt", ofstream::out);
	int n = 0, q = atoi(argv[1]);
	for(int i = 0;i<q;i++){
		n = rand() % q + 1;
		ofs << n << endl;
	}

	ofs.close();
	return 0;
}
