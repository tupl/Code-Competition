//@keyword: floyd_warshal, counting_path
/*
	If there is a cycle at k
	any i->k->j will have infinite
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#define SIZE 35
using namespace std;
typedef pair<int, int> ii;
int path[SIZE][SIZE];
int V, E;

void test() {
	ifstream fi; fi.open("test.txt");
	vector<ii> edges;
	while(!fi.eof()) {
		fi >> E; V = 0; edges.clear();
		for(int i = 0; i < E; ++i) {
			int x, y; fi >> x >> y;
			V = max(V, max(x, y));
			edges.push_back(ii(x, y));
		}
		++V;
		memset(path, 0, sizeof(path));
		for(int i = 0; i < E; ++i) {
			ii u = edges[i];
			path[u.first][u.second] = 1;
		}
		for(int k = 0; k < V; ++k) {
			for(int i = 0; i < V; ++i) {
				for(int j = 0; j < V; ++j) {
					path[i][j] += path[i][k] * path[k][j];
				}
			}
		}

        for(int k = 0; k < V; ++k) {
        	if (path[k][k]) {
				for(int i = 0; i < V; ++i) {
					for(int j = 0; j < V; ++j) {
						if (path[i][k] && path[k][j]) {
							path[i][j] = -1;
						}
					}
				}
        	}
        }

		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				cout << path[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}
