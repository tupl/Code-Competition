#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <map>
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
bool grid[1001][1001];

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
			if (dfs_low[v.first] > dfs_num[u]) {
				// this is a bridge (u, v.first)
				// cout << u + 1 << ", " << v.first + 1 << "\n";
				grid[u][v.first] = true;
				grid[v.first][u] = true;
			}
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
}

void test() {
	ifstream fi;
	fi.open("test.txt");

	while(true) {
		vii saved;
		fi >> V >> E;
		if (V == 0 || E == 0) break;
		AdjList.clear();
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				grid[i][j] = false;
			}
		}
		for(int i = 0; i < V; ++i) { vii tmp; AdjList.push_back(tmp); }
		for(int i = 0; i < E; ++i) {
			int from, to;
			fi >> from >> to;
			--from;
			--to;
			saved.push_back(make_pair(from, to));
			AdjList[from].push_back(make_pair(to, 0));
			AdjList[to].push_back(make_pair(from, 0));
		}
		graphPointEdge();
		for(int i = 0; i < (int)saved.size(); ++i) {
			ii tmp = saved[i];
			int u = tmp.first;
			int v = tmp.second;
			if (grid[u][v]) {
				cout << u + 1 << " " << v + 1 << "\n";
				cout << v + 1 << " " << u + 1 << "\n";
			} else {
				cout << u + 1 << " " << v + 1 << "\n";
			}
		}
		cout << "#\n";
	}
}

int main() {
	test();
	return 0;
}