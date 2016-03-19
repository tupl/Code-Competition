#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#define SIZE 200
#define INF 1000000
using namespace std;
int AdjMat[SIZE][SIZE];
int V, E;

void reset() {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			AdjMat[i][j] = INF;
		}
	}
}

void floyd_warshall() {
	for(int k = 0; k < V; ++k)
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j) {
				AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);
			}
}

void test() {
	ifstream fi; fi.open("test.txt");
	int numTC = 1;
	while(!fi.eof()) {
		cout << "Test Set #" << numTC << "\n";
		++numTC;
		V = 20; reset();
		for(int i = 0; i < 19; ++i) {
			fi >> E;
			for(int j = 0; j < E; ++j) {
				int a; fi >> a; --a;
				AdjMat[i][a] = AdjMat[a][i] = 1;
			}
		}
		floyd_warshall();
		int tc; fi >> tc;
		for(int i = 0; i < tc; ++i) {
			int a, b; fi >> a >> b; --a; --b;
			cout << a + 1 << " to " << b + 1 << ": " << AdjMat[a][b] << "\n";
		}
		cout << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}