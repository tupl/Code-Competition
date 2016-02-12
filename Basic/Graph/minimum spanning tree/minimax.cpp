#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <map>
using namespace std;
// edge - weight - two vertieces
typedef pair<int, int> ii;
typedef pair<int, ii> i_ii;
typedef vector<int> vi;
typedef vector<ii> vii;
vector< pair<int, ii> > EdgeList, MstList;
int V, E;
vi pset; // parent of element
vi sset; // size of set
int numSet; //Number of set
int mst_cost;

const int DFS_BLACK = 1;
const int DFS_WHITE = 0;
vector<vii> AdjList;
vi dfs_num; // mark the vertices
vi dfs_mark; // comes from what vertices

void initSet(int N) {
	pset.assign(N, 0); numSet = N;
	sset.assign(N, 1);
	for(int i = 0; i < N; ++i) { pset[i] = i; }
}
int findSet(int i) {
	return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
}
int numDisjointSets() {
	return numSet;
}
bool isSameSet(int i, int j) {
	return findSet(i) == findSet(j);
}
int sizeOfSet(int i) {
	return sset[findSet(i)];
}
void unionSet(int i, int j) {
	if (findSet(i) != findSet(j)) {
		int orgi = findSet(i);
		int orgj = findSet(j);
		pset[orgi] = orgj;
		sset[orgj] += sset[orgi];
		-- numSet;
	}
}


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

void Minimax(int origin, int dest) {
	sort(EdgeList.begin(), EdgeList.end());
	mst_cost = 0;
	initSet(V);
	int counter = 0;
	MstList.clear();
	for(int i = 0; i < E; ++i) {
		i_ii front = EdgeList[i];
		if (!isSameSet(front.second.first, front.second.second)) {
			MstList.push_back(i_ii(front.first, ii(front.second.first, front.second.second)));
			mst_cost += front.first;
			unionSet(front.second.first, front.second.second);
			++counter;
			if (counter == V - 1) break;
		}
	}
	for(int i = 0; i < V; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	for(int i = 0; i < MstList.size(); ++i) {
		int weight = MstList[i].first;
		int from = MstList[i].second.first;
		int to = MstList[i].second.second;
		AdjList[from].push_back(make_pair(to, weight));
		AdjList[to].push_back(make_pair(from, weight));
	}
	dfs_num.assign(V, DFS_WHITE);
	dfs_mark.assign(V, -1);

	dfs(origin);
	int _ = dest;
	int maximum = 0;
	while(true) {
		int next = dfs_mark[_];
		for(int i = 0; i <  AdjList[next].size(); ++i) {
			ii tmp = AdjList[next][i];
			int weight = tmp.second;
			if (tmp.first == _ && weight > maximum) {
				maximum = weight;
			}
		}
		_ = next;
		if (_ == origin) break;
	}
	cout << "Maximum = " << maximum << "\n";
}

void test() {
	ifstream fi;
	fi.open("krusal.txt");
	fi >> V >> E;
	cout << V << " " << E << "\n";
	EdgeList.clear();
	for(int i = 0; i < E; ++i) {
		int from, to, weight;
		fi >> from >> to >> weight;
		printf("%d %d %d\n", from, to, weight);
		EdgeList.push_back( pair<int, ii>( weight, ii(from, to) ) );
	}
	Minimax(0, 3);
	fi.close();
}

int main() {
	test();
	return 0;
}
