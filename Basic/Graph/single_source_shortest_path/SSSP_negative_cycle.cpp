#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <math>
#define INF 1000000
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
int V, E;
vector<vii> AdjList;

bool BellmanFord(int s) {
	vi dist(V, INF);
	dist[s] = 0;
	for(int i = 0; i < V - 1; ++i) {
		for(int u = 0; u < V; ++u) {
			for(int j = 0; j < (int) AdjList[u].size(); ++j) {
				ii v = AdjList[u][j];
				dist[v.first] = min(dist[v.first], dist[u] + v.second);
			}
		}
	}

	for(int u = 0; u < V; ++u) {
		for(int j = 0; j < (int) AdjList[u].size(); ++j) {
			ii v = AdjList[u][j];
			if (dist[v.first] > dist[u] + v.second) {
				return false;
			}
		}
	}
	return true;
}

