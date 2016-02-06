// Claw Decomposition
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <fstream>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
map<int, int> dist; 

bool bipartite_check(int s) {
	queue<int> q; q.push(s);
	dist[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < (int) AdjList[u].size(); ++i) {
			ii v = AdjList[u][i];
			if(!dist.count(v.first)) {
				dist[v.first] = 1 - dist[u];
				q.push(v.first);
			} else if (dist[v.first] == dist[u]) {
				return false;
			}
		}
	}
	return true;
}

bool full_check() {
	for(int i = 0; i < V; ++i) {
		if (!dist.count(i)) {
			bool rlt = bipartite_check(i);
			if (!rlt) return false;
		}
	}
	return true;
}

void test() {
	ifstream fi;
	fi.open("input1.txt");
	int grid[300][300];
	fi >> V;
	while(!fi.eof()) {
		int i, j;
		fi >> i >> j;
		if (i != 0 && j != 0) {
			--i; --j;
			grid[i][j] = 1;
		}
	}
	for(int i = 0; i < V; ++i) { vii tmp; AdjList.push_back(tmp); }
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			if (grid[i][j] == 1) {
				AdjList[i].push_back(make_pair(j, 0));
			}
		}
	}
	bool rlt = full_check();
	cout << ((rlt) ? "YES\n" : "NO\n");
	fi.close();
}

int main() {
	test();
	return 0;
}