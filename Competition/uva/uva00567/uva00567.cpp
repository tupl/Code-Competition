// SSSP - BFS
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#define GWHITE 0
#define GBLACK 1
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
int V, E;
vector<vii> AdjList;

int sssp_bfs(int fr, int to) {
	queue<int> q; q.push(fr);
	map<int, int> dist;
	dist[fr] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < (int) AdjList[u].size(); ++i) {
			ii t = AdjList[u][i];
			if (!dist.count(t.first)) {
				dist[t.first] = dist[u] + 1;
				if (t.first == to) {
					return dist[t.first];
				}
				q.push(t.first);
			}
		}
	}
	return 0;
}

void test() {
	ifstream fi; fi.open("test.txt");
	int testSet = 0;
	while(!fi.eof()) {
		++ testSet;
		cout << "Test Set #" << testSet << "\n";
		V = 20;
		AdjList.assign(20, vii());
		for(int i = 0; i < 19; ++i) {
			int count; fi >> count;
			cout << count << "\n";
			for(int k = 0; k < count; ++k) {
				int dest; fi >> dest; --dest;
				AdjList[i].push_back(ii(dest, 1));
				AdjList[dest].push_back(ii(i, 1));
			}
		}
		int test; fi >> test;
		for(int i = 0; i < test; ++i) {
			int x, y; fi >> x >> y; 
			cout << x << " to " << y << ": ";
			--x; --y;
			cout << sssp_bfs(x, y) << "\n";
		}
		cout << "\n";
	}
}

int main() {
	test();
	return 0;
}
