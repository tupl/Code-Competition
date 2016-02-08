#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <map>
#include <string>
#include <sstream>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
const int DFS_WHITE = -1;
const int DFS_BLACK = 1;
vi dfs_low, dfs_num, dfs_parent;
vector<bool> articulation_vertex;
int dfsNumberCounter;
int rootChildren, dfsRoot;

void articulationPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs_parent[v.first] = u;
			if (u == dfsRoot) rootChildren++;
			articulationPointAndBridge(v.first);
			if (dfs_low[v.first] >= dfs_num[u])
				articulation_vertex[u] = true;
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
		}
		else if (v.first != dfs_parent[u]) {
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
		}
	}
}

void graphPointEdge() {
	dfsNumberCounter = 0;
	articulation_vertex.assign(V, false);
	dfs_parent.assign(V, 0);
	dfs_num.assign(V, DFS_WHITE);
	dfs_low.assign(V, 0);
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			dfsRoot = i;
			rootChildren = 0;
			articulationPointAndBridge(i);
			articulation_vertex[dfsRoot] = (rootChildren > 1);
		}
	}
	int counter  = 0;
	for(int i = 0; i < V; ++i) {
		if (articulation_vertex[i]) {
			++counter;
		}
	}
	cout << counter << "\n";
}

void test() {
	ifstream fi;
	fi.open("test.txt");
	while(!fi.eof()) {
		fi >> V;
		if (V == 0) break;
		AdjList.clear();
		for(int i = 0; i < V; ++i) { vii tmp; AdjList.push_back(tmp); }
		string line;
		while(std::getline(fi, line)) {
			if (line.empty()) continue;
			istringstream iss(line);
			int cur, next;
			iss >> cur;
			if (cur != 0) {
				--cur;
				while (iss >> next) {
					--next;
					AdjList[cur].push_back(make_pair(next, 0));
					AdjList[next].push_back(make_pair(cur, 0));
				}
			} else {
				break;
			}
		}
		graphPointEdge();
	}
	fi.close();
}

int main() {
	test();
	return 0;
}