//@keyword: dag, dynamic_programming, scheduling
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#define REP(i,j,k) for(int (i)=(j); (i) < (k); ++(i))
using namespace std;
typedef vector<int> vi;
vector<vi> AdjList;
const int unvisited = 0;
const int visited = 1;
vi cost;
vi topo;
vi total;
vi mark;
int nTask;

void dfs(int i) {
	mark[i] = visited;
	REP(j,0,AdjList[i].size()) {
		int v = AdjList[i][j];
		if (mark[v] == unvisited) {
			dfs(v);
		}
	}
	topo.push_back(i);
}

void topological() {
	REP(i,0,27) {
		if (mark[i] == unvisited) {
			dfs(i);
		}
	}
}

int solve() {
	total.assign(nTask, 0);
	REP(i,0,nTask) {
		int maxval = 0;
		REP(j,0,i) {
			maxval = max(maxval, total[i])
		}
	}
}