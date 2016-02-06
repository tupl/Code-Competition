#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
#include <string>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
vector<vii> AdjList;
int V, E;
typedef DFS_WHITE 0;
typedef DFS_BLACK 1;
typedef DFS_GRAY 2;
vi dfs_num;
vi dfs_parent;

void graphCheck(int u) {
	dfs_num[u] = DFS_GRAY;
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs_parent[v.first] = u;
			graphCheck(v.first);
		}
		else if (dfs_num[v.first] == DFS_GRAY) {
			if(v.first == dfs_parent[u]) {
				// forward edge
			}
			else
			{
				// back edge
			}
		}
		else if (dfs_num[v.first] == DFS_BLACK) {
			// forward cross edge
		}
	}
	dfs_num[u] = DFS_BLACK;
}


void edge_type() {
	dfs_num.assign(V, DFS_WHITE);
	dfs_parent.assign(V, -1);
	for(innt i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			graphCheck(i);
		}
	}
}