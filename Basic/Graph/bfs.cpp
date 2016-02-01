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
vi bfs_mark;

map<int, int> dist;

void bfs(int s) {
	queue<int> q; q.push(s);
	dist[s] = 0;
	while(!q.empty()) {
		int u  = q.front();
		q.pop();
		for(int j = 0; j < (int)AdjList[u].size(); ++j) {
			ii v = AdjList[u][j];
			if (dist.find(v.first) == dist.end()) {
				dist[v.first] = dist[u] + 1;
				bfs_mark[v.first] = u;
				q.push(v.first);
			}
		}
	}
}

void bfs_all() {
	for(int i = 0; i < (int) bfs_mark.size(); ++i) {
		if (bfs_mark[i] == -1) {
			bfs(i);
		}
	}
}

void test() {
	for(int i = 0; i < 4; ++i) {
		bfs_mark.push_back(-1);
	}
	for(int i = 0; i < 4; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	AdjList[0].push_back(make_pair(1, 0));
	AdjList[0].push_back(make_pair(3, 0));
	AdjList[3].push_back(make_pair(2, 0));
}


void print_rlt() {
	for(int i = 0; i < 4; ++i) {
		printf("%d -> %d with %d\n", bfs_mark[i], i, dist.find(i)->second );
	}
}

int main() {
	test();
	bfs(0);
	print_rlt();
	return 0;
}