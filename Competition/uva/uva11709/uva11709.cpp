#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include <sstream>
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
map<string, int> si;

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
		++numSCC;
		while(true) {
			int v = S.back();
			S.pop_back();
			visited[v] = false;
			if (u == v) break;
		}
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
	fi.open("input.txt");
	while(!fi.eof()) {
		fi >> V >> E;
		string line;
		AdjList.clear();
		si.clear();
		getline(fi, line);
		for(int i = 0; i < V; ++i) {
			vii tmp;
			AdjList.push_back(tmp);
			getline(fi, line);
			si[line] = i;
		}
		for(int i = 0; i < E; ++i) {
			string line1, line2;
			int from, to;
			getline(fi, line1);
			getline(fi, line2);
			from = si[line1];
			to = si[line2];
			AdjList[from].push_back(make_pair(to, 0));
		}
		working_SCC();
		cout << numSCC << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}