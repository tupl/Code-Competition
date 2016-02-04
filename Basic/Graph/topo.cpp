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

void test() {
	V = 8;
	for(int i = 0; i < V; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	AdjList[0].push_back(make_pair(1, 0)); AdjList[0].push_back(make_pair(2, 0));
	AdjList[1].push_back(make_pair(3, 0)); AdjList[1].push_back(make_pair(2, 0));
	AdjList[2].push_back(make_pair(3, 0)); AdjList[2].push_back(make_pair(5, 0));
	AdjList[3].push_back(make_pair(4, 0));
	AdjList[7].push_back(make_pair(6, 0));
	topologicalSort();
	for(int i = 0; i < (int) topoSort.size(); ++i) {
		cout << topoSort[i] << " ";
	}
	cout << "\n";
}

int main() {
	test();
	return 0;
}