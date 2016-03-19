//@keyword: floyd_warshall, all_pair_shortest_path
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#define INF 1000000
#define SIZE 100
using namespace std;
int V, E;
int AdjMat[SIZE][SIZE];

void reset() {
	for(int i = 0; i < SIZE; ++i) {
		for(int j = 0; j < SIZE; ++j) {
			AdjMat[i][j] = INF;
		}
	}
}

int dist(int u) {
	int farthest = 0;
	// from 0 to 4
	for(int i = 0; i <= 4; ++i) {
		farthest = max(farthest, AdjMat[i][u]);
	}
	return farthest;
}

void floyd_warshall() {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);
			}
		}
	}
}

void test() {
	int nt; ifstream fi; fi.open("test.txt");
	fi >> nt;
	for(int tc = 0; tc < nt; ++tc) {
		fi >> V >> E;
		reset();
		for(int i = 0; i < E; ++i) {
			int x, y, w; fi >> x >> y >> w; --x, --y;
			AdjMat[x][y] = AdjMat[y][x] = w;
		}
		floyd_warshall();
		int best = INF;
		for(int i = 5; i < V; ++i) {
			int val = dist(i);
			if (val < best) {
				best = val;
			}
		}
		cout << "Map " << tc + 1 << ": ";
		if (best == INF) {
			cout << -1 << "\n";
		} else {
			cout << best << "\n";
		}
	}
	fi.close();
}

int main() {
	test();
	return 0;
}