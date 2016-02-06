#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <cmath>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
map<int, int> dist; 

bool bipartite_check(int s, int& total, int& zero) {
	queue<int> q;
	total = 0, zero = 1;
	q.push(s);
	dist[s] = 0;
	while(!q.empty()) {
		++total;
		int u = q.front(); q.pop();
		for(int i = 0; i < (int) AdjList[u].size(); ++i) {
			ii v = AdjList[u][i];
			if(!dist.count(v.first)) {
				dist[v.first] = 1 - dist[u];
				q.push(v.first);
				if (dist[v.first] == 0) {
					++zero;
				}
			} else if (dist[v.first] == dist[u]) {
				return false;
			}
		}
	}
	return true;
}

void full_check() {
	int sum = 0;
	for(int i = 0; i < V; ++i) {
		if (!dist.count(i)) {
			int total, zero;
			bool rlt = bipartite_check(i, total, zero);
			if (!rlt) {
				cout << "-1\n";
				return;
			} else {
				if (total == 1) {
					sum += 1;
				} else {
					sum += min(total-zero, zero);
				}
			}
		}
	}
	cout << sum << "\n";
}

void test() {
	ifstream fi;
	fi.open("place_guard.txt");
	int numtest;
	fi >> numtest;
	for(int idx = 0; idx < numtest; ++idx) {
		fi >> V >> E;
		dist.clear();
		AdjList.clear();
		for(int i = 0; i < V; ++i) { vii tmp; AdjList.push_back(tmp); }
		for(int k = 0; k < E; ++k) {
			int i, j;
			fi >> i >> j;
			AdjList[i].push_back(make_pair(j, 0));
			AdjList[j].push_back(make_pair(i, 0));		
		}
		full_check();
	}
	fi.close();
}

int main() {
	test();
	return 0;
}