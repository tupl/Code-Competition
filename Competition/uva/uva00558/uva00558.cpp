#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#define INF 100000
#define SIZE 500
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
vector<vii> AdjList;
int V, E;


bool bellman(int c) {
	vi dist(V, INF); dist[c] = 0;
	for(int i = 0; i < V - 1; ++i) {
		for(int u = 0; u < V; ++u) {
			for(int j = 0; j < (int)AdjList[u].size(); ++j) {
				ii v_o = AdjList[u][j];
				int v = v_o.first, u_v = v_o.second;
				if (dist[u] + u_v < dist[v]) {
					dist[v] = dist[u] + u_v;
				}
			}
		}
	}
	for(int u = 0; u < V; ++u) {
		for(int j = 0; j < (int)AdjList[u].size(); ++j) {
			ii v_o = AdjList[u][j];
			int v = v_o.first, u_v = v_o.second;
			if (dist[u] + u_v < dist[v]) {
				return true;
			}
		}
	}
	return false;
}

void test() {
	ifstream fi; fi.open("test.txt");
	int tc = 0; fi >> tc;
	for(int i = 0; i < tc; ++i) {
		fi >> V >> E;
		AdjList.assign(V, vii());
		for(int j = 0; j < E; ++j) {
			int x, y, w;
			fi >> x >> y >> w;
			AdjList[x].push_back(ii(y, w));
			// AdjList[y].push_back(ii(x, w));
		}
		cout << bellman(0) << "\n";
	}
	fi.close();
}

int main() { test(); return 0; }