#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
const int DFS_WHITE = 0;
const int DFS_BLACK = 1;
vector<vii> AdjList;
vi topoSort;
vi dfs_num;
int V, E;

void dfs2(int u) {
	dfs_num[u] = DFS_BLACK;
	for(int i = 0; i < (int)AdjList[u].size(); ++i) {
		ii v = AdjList[u][i];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs2(v.first);
		}
	}
	topoSort.push_back(u);
}

void topologicalSort() {
	topoSort.clear();
	dfs_num.assign(V, DFS_WHITE);
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			dfs2(i);
		}
	}
	reverse(topoSort.begin(), topoSort.end());
}

