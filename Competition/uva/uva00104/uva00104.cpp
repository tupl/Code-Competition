//@
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>
#define SIZE 25
using namespace std;
double exch[SIZE][SIZE];
int steps[SIZE][SIZE];
int 
int V;

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> V;
		memset(exch, 1.0, sizeof(exch));
		memset(steps, 100, sizeof(steps));
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				int tmp; fi >> tmp;
				if (j != i) {
					exch[i][j] = tmp;
				}
			}
		}


	}
	fi.close();
}