#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
vector<vii> AdjList;
int V, E;
const int DFS_WHITE = 0;
const int DFS_BLACK = 1;
const int DFS_GRAY = 2;
vi dfs_num;
vi dfs_parent;
bool hasCycle;
vi topoSort;

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

void graphCheck(int u) {
	dfs_num[u] = DFS_GRAY;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs_parent[v.first] = u;
			graphCheck(v.first);
		}
		else if (dfs_num[v.first] == DFS_GRAY) {
			if(v.first != dfs_parent[u]) {
				hasCycle = true;
				return;
			}
		}
		else if (dfs_num[v.first] == DFS_BLACK) {
			//forward cross edge
		}
	}
	dfs_num[u] = DFS_BLACK;
}

bool cycleCheck() {
	dfs_num.assign(V, DFS_WHITE);
	dfs_parent.assign(V, -1);
	hasCycle = false;
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			graphCheck(i);
		}
	}
	return hasCycle;
}

void solve() {
	cycleCheck();
	if ( hasCycle ) {
		cout << "IMPOSSIBLE\n";
	}
	else {
		topologicalSort();
		for(int i = 0; i < (int) topoSort.size(); ++i) {
			cout << topoSort[i] + 1 << "\n";
		}
	}
}

void test(string filePath) {
	ifstream input;
	input.open(filePath);
	input >> V >> E;
	for(int i = 0; i < V; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	for(int i = 0; i < E; ++i) {
		int from, to;
		input >> from >> to;
		--from;
		--to;
		AdjList[from].push_back(make_pair(to, 0));
	}
	input.close();
}

int main() {
	test("input.txt");
	solve();
	return 0;
}