//Gauge Zidlick generate-map.cpp
//Project 4 generate-map.cpp - create a program that makes an NxN map

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]){
	srand(time(0));
	vector<char> myvec{'d','i','j','k','s','t','r','a'};
	ofstream file;
	int n = 10;
	file.open("map.txt");
	file << myvec.size() << endl;
	for(unsigned int i = 0;i<myvec.size();i++){
		file << myvec[i] << " " << 1 + rand() % 19 << endl;
	}
	file << n << " " << n << endl;
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n;j++){
			file << myvec[(rand()%6)] << " ";
		}
		file << endl;
	}
	file << "0 0" << endl;
	file << n-1 << " " << n-1 << endl;
	file.close();
	return 0;

}
