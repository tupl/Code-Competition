#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define INF 100000
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
int V, E;
vi busy;
vector<vii> AdjList;
vi dist;

bool bellman() {
	dist[0] = 0;
	for(int i = 0; i < V - 1; ++i) {
		for(int u = 0; u < V; ++u) {
			for(int j = 0; j < (int) AdjList[u].size(); ++j) {
				ii v_o = AdjList[u][j];
				int v = v_o.first, w = v_o.second;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
				}
			}
		}
	}
	for(int u = 0; u < V; ++u) {
		for(int j = 0; j < (int) AdjList[u].size(); ++j) {
			ii v_o = AdjList[u][j];
			int v = v_o.first, w = v_o.second;
			if (dist[v] > dist[u] + w) {
				return false;
			}
		}
	}
	return true;
}

void test() {
	ifstream fi; fi.open("test1.txt");
	fi >> V;
	busy.assign(V, 0);
	for(int i = 0; i < V; ++i) {
		int tmp; fi >> tmp;
		busy[i] = tmp;
	}
	fi >> E;
	AdjList.assign(V, vii());
	for (int i = 0; i < E; ++i)
	{
		int from, to; fi >> from >> to;
		--from, --to;
		AdjList[from].push_back(ii(to, busy[to] - busy[from]));
	}
	dist.assign(V, INF);
	bool stt = bellman();
	int nq, q; fi >> nq;
	for(int i = 0; i < nq; ++i) {
		fi >> q; --q;
		if (stt) {
			if (dist[q] >= 3) {
				cout << dist[q] << "\n";
			} else {
				cout << "?\n";
			}
		} else {
			cout << "?\n";
		}
	}
	fi.close();
}

int main() {
	test();
	return 0;
}