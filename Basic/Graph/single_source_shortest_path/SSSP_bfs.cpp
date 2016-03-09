#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <math>
#include <map>
#define INF 1000000
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
int V, E;
vector<vii> AdjList;

void sssp_bfs(int s) {
	map<int, int> dist;
	dist[s] = 0;
	queue<int> q; q.push(s);
	vi p;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < (int) AdjList[u].size(); ++i) {
			ii v = AdjList[u][i];
			if (!dist.count(v.first])) {
				dist[v.first] = dist[u] + 1;
				p[v.first] = u;
				q.push(v.first);
			}
		}
	}
}