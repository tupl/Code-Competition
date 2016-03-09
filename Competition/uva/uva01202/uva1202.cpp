#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#define INF 1000000
#define MAX_GRID 201
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
int x_[] = {0,1,0,-1};
int y_[] = {1,0,-1,0};
struct Grid {
	int top, right, bot, left;
};
int f1, f2;

struct State
{
	int value;
	int x, y;
	State(int value_, int x_, int y_) {
		value = value_; x = x_; y = y_;
	}
};

struct StateComparator
{
    bool operator()(const State& a, const State& b) const {
        if (a.value < b.value) return true;
        if (a.x < b.x) return true;
        if (a.y < b.y) return true;
        return false;
    }
};

Grid grid[MAX_GRID][MAX_GRID];

void reset_grid() {
	for(int i = 0; i < MAX_GRID; ++i) {
		for(int j = 0; j < MAX_GRID; ++j) {
			grid[i][j].top = grid[i][j].right =
			grid[i][j].bot = grid[i][j].left = 0;
		}
	}
}

void set_door(int x, int y, int d) {
	if(d == 0) {
		grid[x][y].bot = 1;
		grid[x][y-1].top = 1;		
	} else if (d == 1) {
		grid[x][y].left = 1;
		grid[x-1][y].right = 1;		
	}
}

void set_wall(int x, int y, int d, int t) {
	if (d == 0) {
		for(int i = 0; i < t; ++i) {
			grid[x+i][y].bot = INF;
			grid[x+i][y-1].top = INF;
		}
	} else if (d == 1){
		for(int i = 0; i < t; ++i) {
			grid[x][y+i].left = INF;
			grid[x-1][y+i].right = INF;
		}
	}
}

bool valid(ii v) {
	if (v.first < 0 || v.first >= MAX_GRID ||
		v.second < 0 || v.second >= MAX_GRID) return false;
	return true;
}

ii state2ii(State s) {
	ii tmp; tmp.first = s.x; tmp.second = s.y;
	return tmp;
}

void printState(State v) {
	cout << v.value << "->(" << v.x << "," << v.y << ")\n";
}

bool isFinal(State s) {
	return s.x == f1 && s.y == f2;
}

int dijiska(ii s) {
	map<ii, int, greater<ii> > dist;
	dist[s] = 0;
	priority_queue<State, vector<State>, StateComparator> q;
	q.push(State(0, s.first, s.second));
	while(!q.empty()){
		State u = q.top(); q.pop();
		if (u.value > dist[state2ii(u)]) continue;
		if (isFinal(u)) {
			return dist[state2ii(u)];
		}
		for(int i = 0; i < 4; ++i) {
			int newx = u.x + x_[i];
			int newy = u.y + y_[i];
			ii v; v.first = newx; v.second = newy;
			if (valid(v)) {
				int value = 0;
				switch(i) {
					case 0: value = grid[newx][newy].bot; break;
					case 1: value = grid[newx][newy].left; break;
					case 2: value = grid[newx][newy].top; break;
					case 3: value = grid[newx][newy].right; break;
				}
				if (value != INF) {
					if (!dist.count(v) ||
						dist[state2ii(u)] + value < dist[v]) {
						dist[v] = dist[state2ii(u)] + value;
						State news(dist[v], newx, newy);
						q.push(news);
					}
				}
			}
		}
	}
	return -1;
}

void test() {
	ifstream fi; fi.open("test.txt");
	int M, N;
	while(!fi.eof()) {
		fi >> M >> N;
		if (M == -1 && N == -1) break;
		reset_grid();
		for(int i = 0; i < M; ++i) {
			int x, y, d, t;
			fi >> x >> y >> d>> t;
			set_wall(x, y, d, t);
		}
		for(int i = 0; i < N; ++i) {
			int x, y, d;
			fi >> x >> y >> d;
			set_door(x, y, d);
		}
		double f1d, f2d;
		fi >> f1d >> f2d;
		f1 = floor(f1d); f2 = floor(f2d);
		// print_grid(2);
		cout << dijiska(ii(0, 0)) << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}