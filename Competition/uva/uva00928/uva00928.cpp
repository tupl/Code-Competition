// Keyword: sssp, bfs, grid
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#define MAZE_SIZE 301
using namespace std;
char maze[MAZE_SIZE][MAZE_SIZE];
int path[MAZE_SIZE][MAZE_SIZE];
int row, column;
int to_x, to_y;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

bool valid(int x, int y) {
	if (x < 0 || x >= row) return false;
	if (y < 0 || y >= column) return false;
	return true;
}

bool sssp_bfs(ii s) {
	int x_[] = {0, 1, 0, -1};
	int y_[] = {1, 0, -1, 0};
	queue<ii> q; q.push(s);
	path[s.first][s.second] = 0;
	while(!q.empty()) {
		ii u = q.front(); q.pop();
		for(int i = 0; i < 4; ++i) {
			int next_x = u.first + x_[i];
			int next_y = u.second + y_[i];
			if (valid(next_x, next_y)) {
				if (maze[next_x][next_y] == '.') {
					maze[next_x][next_y] = '@';
					path[next_x][next_y] = path[u.first][u.second] + 1;
					q.push(ii(next_x, next_y));
				} else if (maze[next_x][next_y] == 'E') {
					path[next_x][next_y] = path[u.first][u.second] + 1;
					to_x = next_x; to_y = next_y;
					return true;				
				}
			}
		}
	}
	return false;

}

void test() {
	int testCase;
	ifstream fi; fi.open("test.txt"); fi >> testCase;
	for(int k = 0; k < testCase; ++k) {
		fi >> column >> row;
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
		bool rlt = sssp_bfs(ii(fr_x, fr_y));
		if (rlt) {
			cout << path[to_x][to_y] << "\n";
		} else {
			cout << "NO\n";
		}
	} 
}

int main() {
	test();
	return 0;
}