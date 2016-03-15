// @keyword sssp, bellman, graph_modeling
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#define INF 10000000
#define MAX_CITY 100
#define MAX_QUERRY 111
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
int dist[MAX_CITY][MAX_QUERRY];
map<string, int> city;
int curCity;
int maxQuery;

void addCity(string c) { city[c] = curCity; ++curCity; }
int city2idx(string c) { return city[c]; }

void reset() {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j <= maxQuery + 1; ++j) {
			dist[i][j] = INF;
		}
	}
}

void bellman_fold() {
	reset(); dist[0][0] = 0;
	for(int i = 0; i < V -1; ++i) {
		for(int u = 0; u < V; ++u) {
			for(int l = 0; l <= maxQuery; ++l )
			// for each (u, l)
			// (u, l + 1) <- (v, l) + weight
			for(int j = 0; j < (int) AdjList[u].size(); ++j) {
				ii v_o = AdjList[u][j]; int v = v_o.first, wei = v_o.second;
				if (dist[v][l + 1] > dist[u][l] + wei) {
					dist[v][l + 1] = dist[u][l] + wei;
				}
			}
		}
	}
}

void test() {
	ifstream fi; fi.open("test1.txt");
	int nt; fi >> nt;
	for(int t = 0; t < nt; ++t) {
		cout << "Scenario #" << t + 1 << "\n";
		fi >> V;
		curCity = 0;
		for(int i = 0; i < V; ++i) {
			string tmp; fi >> tmp;
			addCity(tmp);
		}
		fi >> E;
		AdjList.assign(V, vii());
		for(int i = 0; i < E; ++i) {
			string from, to; int weg;
			fi >> from >> to >> weg;
			AdjList[city2idx(from)].push_back(ii(city2idx(to), weg));
		}
		int nq; fi >> nq;
		for(int i = 0; i < nq; ++i) {
			int myq; fi >> myq;
			maxQuery = myq;
			bellman_fold();
			int minimum = INF;
			for(int j = 0; j <= maxQuery + 1; ++j) {
				minimum = min(minimum, dist[V - 1][j]);
			}
			if (minimum == INF) {
				cout << "No satisfactory flights" << "\n";
			} else {
				cout << "Total cost of flight(s) is " << minimum << "\n";
			}
		}
		cout << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}
