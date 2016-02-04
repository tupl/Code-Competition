#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;

bool bipartite_check(int s) {
	queue<int> q; q.push(s);
	map<int, int> dist; dist[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < (int) AdjList[u].size(); ++i) {
			ii v = AdjList[u][i];
			if(!dist.count(v.first)) {
				dist[v.first] = 1 - dist[u];
				q.push(v.first);
			} else if (dist[v.first] == dist[u]) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	return 0;
}