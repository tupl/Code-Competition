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

void dfs_all() {
	for(int i = 0; i < (int) dfs_num.size(); ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			dfs(i);
		}
	}
}

void test() {
	for(int i = 0; i < 4; ++i) {
		dfs_num.push_back(DFS_WHITE);
		dfs_mark.push_back(-1);
	}
	for(int i = 0; i < 4; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	AdjList[0].push_back(make_pair(1, 0));
	AdjList[2].push_back(make_pair(3, 0));
}


void print_rlt() {
	for(int i = 0; i < 4; ++i) {
		printf("%d -> %d\n", dfs_mark[i], i);
	}
}

int main() {
	test();
	dfs_all();
	print_rlt();
	return 0;
}