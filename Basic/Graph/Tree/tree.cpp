#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#define DFS_WHITE 0
#define DFS_BLACK 1
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
vector<vii> AdjList;
int V, E;
vi dfs_num; // mark the vertices
vi dfs_mark; // comes from what vertices

void dfs(int u) {
	dfs_num[u] = DFS_BLACK;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs_mark[v.first] = u;
			dfs(v.first);
		}
	}
}

// find the vertext that is farthest from s
ii tree_furthest(int s) {
	map<int, int> dist;
	queue<int> q; q.push(s);
	dist[s] = 0;
	while(!q.empty()) {
		int u  = q.front(); q.pop();
		for(int j = 0; j < (int)AdjList[u].size(); ++j) {
			ii v = AdjList[u][j];
			if (dist.find(v.first) == dist.end()) {
				dist[v.first] = dist[u] + v.second;
				q.push(v.first);
			}
		}
	}
	int maxV = -1, maxPath = 0;
	for(int i = 0; i < V; ++i) {
		if (maxPath < dist[i]) {
			maxPath = dist[i];
			maxV = i;
		}
	}
	ii rlt; rlt.first = maxV; rlt.second = maxPath;
	return rlt;
}

// diameter of a tree
ii tree_diameter() {
	int s = 0;
	ii s_x = tree_furthest(s);
	return tree_furthest(s_x.first);
}

//single source shortest path