// @keyword sssp, dijiska
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define INF 1000000
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
vector<vii> AdjList;
int V, E;
int result;

struct State {
	ii state;
	int score;
	State(ii o_st, int o_s) { state = o_st; score = o_s; }
};

struct StateComp {
	bool operator()(const State& st1, const State& st2) {
		if (st1.score != st2.score) return st1.score < st2.score;
		if (st1.state.first != st2.state.first) return st1.state.first < st2.state.first;
		return st1.state.second < st2.state.second;
	}
};

bool isFinal(ii v) {
	// n - 1 and on cycle
	if (v.first == V - 1 && v.second == 1) {
		return true;
	}
	return false;
}

// 0 for no cycle
// 1 for cycle
int dijiska(int city) {
	int dist[501][2];
	result = INF;
	for(int i = 0; i < 500; ++i) { for(int j = 0; j < 2; ++j) { dist[i][j] = INF;}}
	priority_queue<State, vector<State>, StateComp> pq; pq.push(State(ii(city, 1), 0));
	dist[city][1] = 0;
	while(!pq.empty()) {
		State u = pq.top(); pq.pop();
		int u_city = u.state.first;
		int u_cycle = u.state.second;
		if (u.score > dist[u_city][u_cycle]) continue;
		if (isFinal(u.state)) {
			if (result > u.score) {
				result = u.score;
			}
		}
		for(int i = 0; i < (int) AdjList[u_city].size(); ++i) {
			ii v = AdjList[u_city][i];
			int v_city = v.first, v_weight = v.second;
			int val = dist[u_city][u_cycle] + v_weight;
			if (val < dist[v_city][0]) {
				dist[v_city][0] = val;
				pq.push(State(ii(v_city, 0), val));
			}
			if (u_cycle == 0) {
				// no cycle
				if (val < dist[v_city][1]) {
					dist[v_city][1] = val;
					pq.push(State(ii(v_city, 1), val));
				}
			}
		}
	}
	return -1;
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> V >> E;
		int x, y, w;
		AdjList.clear();
		AdjList.assign(V, vii());
		for(int i = 0; i < E; ++i) {
			fi >> x >> y >> w;
			AdjList[x].push_back(ii(y, w));
			AdjList[y].push_back(ii(x, w));
		}
		dijiska(0);
		cout << result << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}