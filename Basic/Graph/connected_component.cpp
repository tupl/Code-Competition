#include <algorithm>
#include <iostream>
#include <bitset>
#include <map>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
const int DFS_BLACK = 1;
const int DFS_WHITE = 0;
vector<vii> AdjList;

int numCC; // number of connected components
vi dfs_num;
int V, E; // number of vertices, edges

void dfs(int u) {
	dfs_num[u] = DFS_BLACK;
	printf("%d ", u);
	for(int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs(v.first);
		}
	}
}

void ccm() {
	numCC = 0;
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			printf("Component %d:", numCC), dfs(i), printf("\n");
			++numCC;
		}
	}
}

void test() {
	V = 4;
	for(int i = 0; i < 4; ++i) {
		dfs_num.push_back(DFS_WHITE);
	}
	for(int i = 0; i < 4; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	AdjList[0].push_back(make_pair(1, 0));
	AdjList[2].push_back(make_pair(3, 0));
}

int main() {
	test();
	ccm();
	return 0;
}