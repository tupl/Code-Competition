//@keyword: all_pair_shortest_path, floyd_warshall, transitive_closure
/**
 * @summary: transitive closure of what can reached from cat, mouse
 * if any room can reach by both --> our room
 * After find closure of Cat,
 *	for each room that can be reachable from Cat
 *		remove all mouse-door lead to that room
 * set R[x][x] = 0 to let us find the cycle
 * if cat cannot go to mouse room and there is cycle to mouse room
 *	answer yes				
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#define SIZE 100
using namespace std;
int catMat[SIZE][SIZE];
int miceMat[SIZE][SIZE];
int rMiceCat[SIZE][SIZE];
int cat, mice, V;

void closure(int mt[SIZE][SIZE]) {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				mt[i][j] |= mt[i][k] & mt[k][j];
			}
		}
	}
}

void test() {
	int nt; ifstream fi; fi.open("test.txt");
	fi >> nt;
	for(int i = 0; i < nt; ++i) {
		fi >> V >> cat >> mice; --cat; --mice;
		memset(catMat, 0, sizeof(catMat)); memset(miceMat, 0, sizeof(miceMat));
		while(true){
			int a, b;
			fi >> a >> b; if (a == -1 && b == -1) break; --a, --b;
			catMat[a][b] = 1;
		}
		while(!fi.eof()) {
			int a, b;
			fi >> a >> b; --a, --b;
			miceMat[a][b] = 1;
		}
		memcpy(rMiceCat, miceMat, sizeof(miceMat));
		for(int i = 0; i < V; ++i) { catMat[i][i] = miceMat[i][i] = 1; }
		closure(catMat); closure(miceMat);
		bool ans1 = false, ans2 = false;
		for(int i = 0; i < V; ++i) {
			if (catMat[cat][i] & miceMat[mice][i]) {
				ans1 = true; break;
			}
		}
		// remove all reachable to closure of cat
		for(int i = 0; i < V; ++i) {
			if (catMat[cat][i]) {
				for(int j = 0; j < V; ++j) {
					rMiceCat[j][i] = 0;
				}
			}
			rMiceCat[i][i] = 0;
		}
		closure(rMiceCat);
		if (!catMat[cat][mice] && rMiceCat[mice][mice]) {
			ans2 = true;
		}
		if (ans1) { cout << "Y "; } else { cout << "N "; }
		if (ans2) { cout << "Y\n"; } else { cout << "N\n"; }
	}
	fi.close();
}

int main() {
	test();
	return 0;
}