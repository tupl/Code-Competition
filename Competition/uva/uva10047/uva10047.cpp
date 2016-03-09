//@Keyword: sssp, bfs, grid, grid-additional-state
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#define MAZE_SIZE 301
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
struct State
{
	ii posi;
	int dire;
	int color;
	State(ii o_posi, int o_dire, int o_color) {
		posi = o_posi;
		dire = o_dire;
		color = o_color;
	}

    bool operator<(const State& rhs) const {
	    if (posi != rhs.posi) return posi < rhs.posi;
	    if (dire != rhs.dire) return dire < rhs.dire;
	    return color < rhs.color;
    }
};
char maze[MAZE_SIZE][MAZE_SIZE];
int row, column;
int to_x, to_y, to_dire;
int x_[] = {0, 1, 0, -1};
int y_[] = {1, 0, -1, 0};
map<State, int> dist;

bool valid(int x, int y) {
	if (x < 0 || x >= row) return false;
	if (y < 0 || y >= column) return false;
	return true;
}

int next_direction(int dire, int turn) {
	dire += ((turn == 0)? 1: -1);
	if (dire < 0) return 3;
	return dire % 4;
}

int next_color(int i) {
	return (i + 1) % 5;
}

bool isFinal(State s) {
	return maze[s.posi.first][s.posi.second] == 'T' && s.color == 0;
}

vector<State> next_states(State s) {
	vector<State> children;
	int next_x, next_y;
	next_x = s.posi.first + x_[s.dire];
	next_y = s.posi.second + y_[s.dire];
	if (valid(next_x, next_y) && (maze[next_x][next_y] == '.' || maze[next_x][next_y] == 'T')) {
		children.push_back(State(ii(next_x, next_y), s.dire, next_color(s.color)));
	}
	children.push_back(State(s.posi, next_direction(s.dire, 0), s.color));
	children.push_back(State(s.posi, next_direction(s.dire, 1), s.color));
	return children;
}

bool sssp_bfs(State s) {
	dist.clear();
	queue<State> q; q.push(s);
	dist[s] = 0;
	while(!q.empty()) {
		State u = q.front(); q.pop();
		vector<State> new_states = next_states(u);
		for(int i = 0; i < (int) new_states.size(); ++i) {
			State tmp = new_states[i];
			if(!dist.count(tmp)) {
				dist[tmp] = dist[u] + 1;
				if (isFinal(tmp)) {
					to_x = tmp.posi.first;
					to_y = tmp.posi.second;
					to_dire = tmp.dire;
					return true;
				}
				q.push(tmp);
			}
		}
	}
	return false;
}

void test() {
	int testCase = 0;
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> column >> row;
		if (column == 0 || row == 0) return;
		++ testCase;
		cout << "Case #" << testCase << "\n";
		int fr_x, fr_y;
		char tmp;
		for(int j = 0; j < column; ++j) {
			for(int i = 0; i < row; ++i) {
				fi >> tmp;
				if (tmp == 'S') {
					fr_x = i; fr_y = j;
				}
				maze[i][j] = tmp;
			}
		}
		bool rlt = sssp_bfs(State(ii(fr_x, fr_y), 0, 0)) ;
		if (rlt) {
			cout << "minimum time = " << 
				dist[State(ii(to_x, to_y), to_dire, 0)] << " sec\n";
		} else {
			cout << "destination not reachable\n";
		}
		cout << "\n";
	} 
}

int main() {
	test();
	return 0;
}
