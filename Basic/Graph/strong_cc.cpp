#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int DFS_WHITE = -1;
const int DFS_BLACK = 0;
vector<vii> AdjList;
vector<bool> visited;
vi dfs_low, dfs_num;
int dfsNumberCounter;
int numSCC;
vi S;
int V, E;

void tarjanSCC(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
	S.push_back(u);
	visited[u] = true;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE)
			tarjanSCC(v.first);
		if (visited[v.first])
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
	}
	if (dfs_low[u] == dfs_num[u]) {
		printf("SCC %d:", ++numSCC);
		while(true) {
			int v = S.back();
			S.pop_back();
			visited[v] = false;
			cout << " " << v;
			if (u == v) break;
		}
		cout << "\n";
	}
}

void working_SCC() {
	dfs_num.assign(V, DFS_WHITE);
	dfs_low.assign(V, 0);
	visited.assign(V, false);
	dfsNumberCounter = numSCC = 0;
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE)
			tarjanSCC(i);
	}
}

void test() {
	ifstream fi;
	fi.open("strong_cc.txt");
	fi >> V >> E;
	for(int i = 0; i < V; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	for(int i = 0; i < E; ++i) {
		int from, to;
		fi >> from >> to;
		AdjList[from].push_back(make_pair(to, 0));
	}
	working_SCC();
	fi.close();
}

int main() {
	test();
	return 0;
}