#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <math>
#include <map>
#define INF 1000000
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
int V, E;
vector<vi> AdjMat;
vector<vi> p;

void transitive_warshall() {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				AdjMat[i][j] = AdjMat[i][j] | (AdjMat[i][k] & AdjMat[k][j]);
			}
		}
	}	
}

void minimax_warshall() {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				d[i][j] = min(d[i][j], max(d[i][k], d[k][j]));
			}
		}
	}		
}

void printPath(int i, int j) {
	if(i != j) printPath(i, p[i][j]);
	printf(" %d", j);
}

void floyd_warshall() {
	// p is last vertex before j in shortest path from i -> j
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			p[i][j] = i;
		}
	}
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				if (AdjMat[i][k] + AdjMat[k][j] < AdjMat[i][j]) {
					AdjMat[i][j] = AdjMat[i][k] + AdjMat[k][j];
					p[i][j] = p[k][j];
				}
			}
		}
	}
}