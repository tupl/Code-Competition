//@keyword advanced_sssp advanced_dijaski state_space
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
#define INF 100000
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
vector<vii> AdjList;
vi price;
int V, E;
int capacity;
int from, to;
bool found;
int minimum;

struct Stt {
	ii state;
	int weight;
	Stt(ii _stt, int _w) {state = _stt; weight = _w;}
};

struct ScStt
{
	int score; ii state;
	ScStt(int _score, ii _st) { score = _score; state = _st; }
};

struct ScSttComp
{
    bool operator()(const ScStt& a, const ScStt& b) const {
    	if (a.score != b.score) return a.score < b.score;
    	return a.state < b.state;
    }
};

bool is_final(ii s) {
	return s.first == to;
}

vector<Stt> get_states(ii v) {
	vector<Stt> newstt;
	int city = v.first;
	int fuel = v.second;
	for(int i = fuel+1; i <=capacity; ++i) {
		newstt.push_back(
			Stt(ii(city, i), (i - fuel) * price[city] ));
	}
	for(int i = 0; i < (int) AdjList[city].size() ; ++i) {
		ii dest = AdjList[city][i];
		if (fuel - dest.second >= 0) {
			newstt.push_back(Stt(ii(dest.first, fuel - dest.second), 0));
		}
	}
	return newstt;
}

void printScStt(ScStt u) {
	cout << "(" << u.state.first
		 << ", " << u.state.second
		 << ") -> " << u.score << "\n";
}

int sssp_dijiska(ii s) {
	map<ii, int, greater<ii> > dist; dist[s] = 0;
	priority_queue<ScStt, vector<ScStt>, ScSttComp> pq;
	pq.push(ScStt(0, s));
	while(!pq.empty()){
		ScStt u = pq.top(); pq.pop();
		// printScStt(u);
		if (u.score > dist[u.state]) continue;
		if (is_final(u.state)) {
			found = true;
			if (u.score < minimum) {
				minimum = u.score;
			}
		}
		vector<Stt> newstates = get_states(u.state);
		for(int i = 0; i < (int) newstates.size(); ++i) {
			ii v = newstates[i].state;
			int weight = newstates[i].weight;
			int t_score = dist[u.state] + weight;
			if (!dist.count(v) || t_score < dist[v]) {
				dist[v] = t_score;
				pq.push(ScStt(t_score, v));
			}
		}
	}
	return -1;
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		int x, y, w;
		fi >> V >> E;
		price.assign(V, 0);
		for(int i = 0; i < V; ++i) {
			fi >> price[i];
		}
		AdjList.assign(V, vii());
		for(int i = 0; i < E; ++i) {
			fi >> x >> y >> w;
			AdjList[x].push_back(ii(y, w));
			AdjList[y].push_back(ii(x, w));
		}
		int query; fi >> query;
		for(int i = 0; i < query; ++i) {
			fi >> capacity >> from >> to;
			found = false; minimum = INF;
			sssp_dijiska(ii(from, 0));
			if (found) {
				cout << minimum << "\n";
			} else {
				cout << "impossible\n";
			}
		}
	}
	fi.close();
}

int main() {
	test();
	return 0;
}