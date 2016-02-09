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
int cV;
map<string, int> si;
map<int, string> is;

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
		printf("SCC %d:\n", ++numSCC);
		while(true) {
			int v = S.back();
			S.pop_back();
			visited[v] = false;
			map<int, string>::iterator tmp = is.find(v);
			cout << tmp->second << " ";
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

int s2i(string tmp) {
	if (!si.count(tmp)) {
		si.insert(make_pair<string, int>(tmp, cV));
		is.insert(make_pair<int, string>(cV, tmp));
		++cV;
		return cV - 1;
	} else {
		map<string, int>::iterator v = si.find(tmp);
		return v->second;
	}
}

void test() {
	ifstream fi;
	fi.open("input.txt");
	bool grid[25][25];
	while(!fi.eof()) {
		fi >> V >> E;
		cV = 0;
		if (V == 0 || E == 0) break;
		si.clear(); is.clear(); AdjList.clear();
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				grid[i][j] = false;
			}
		}
		for(int i = 0; i < V; ++i) {
			vii tmp;
			AdjList.push_back(tmp);
		}
		for(int i = 0; i < E; ++i) {
			string from, to;
			int ifrom, ito;
			fi >> from >> to;
			ifrom = s2i(from);
			ito = s2i(to);
			if (!grid[ifrom][ito]) {
				AdjList[ifrom].push_back(make_pair(ito, 0));
				grid[ifrom][ito] = true;
			}
		}
		working_SCC();
		cout << "\n\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}