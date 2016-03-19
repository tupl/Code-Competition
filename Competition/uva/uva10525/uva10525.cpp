//@keyword floyd_warshall, all_pair_shortest_path, basic
#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#define INF 100000
#define SIZE 100
using namespace std;
int dist[SIZE][SIZE];
int times[SIZE][SIZE];
int V, E;

void reset() {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			dist[i][j] = times[i][j] = INF;
		}
	}
}

void floyd_warshall() {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					times[i][j] = times[i][k] + times[k][j];
				} else if (dist[i][j] == dist[i][k] + dist[k][j]) {
					if (times[i][j] > times[i][k] + times[k][j]) {
						times[i][j] = times[i][k] + times[k][j];
					}
				}
			}
		}
	}
}

void test() {
	ifstream fi; fi.open("test.txt");
	int numTest; fi >> numTest;
	for(int tc = 0; tc < numTest; ++tc) {
		fi >> V >> E; reset();
		for(int i = 0; i < E; ++i) {
			int x, y, d, t; fi >> x >> y >> t >> d; --x; --y;
			dist[x][y] = dist[y][x] = d;
			times[x][y] = times[y][x] = t;
		}
		floyd_warshall();
		int nq, myq_from, myq_to;
		fi >> nq;
		for(int i = 0; i < nq; ++i) {
			fi >> myq_from >> myq_to; --myq_from; --myq_to;
			if (dist[myq_from][myq_to] < INF) {
				cout << "Distance and time to reach destination is "
					 << dist[myq_from][myq_to] << " & "
					 << times[myq_from][myq_to] << ".\n";
			} else {
				cout << "No Path.\n";
			}
		}
		cout << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}
