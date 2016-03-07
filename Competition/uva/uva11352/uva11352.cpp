//@keyword sssp_bfs, grid
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#define MAXMAZE 100
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
ii fr, to;
map<ii, int> dist;
char maze[MAXMAZE][MAXMAZE];
int row, column;
int x_[] = {0,1,1,1,0,-1,-1,-1};
int y_[] = {1,1,0,-1,-1,-1,0,1};
int hx_[] = {-1,1,2,2,1,-1,-2,-2};
int hy_[] = {2,2,1,-1,-2,-2,-1,1};

bool valid(ii tmp) {
	if (tmp.first < 0 || tmp.first >= row) return false;
	if (tmp.second < 0 || tmp.second >= column) return false;
	return true;
}

void horse_fill() {
	for(int i = 0; i < row; ++i) {
		for(int j = 0; j < column; ++j) {
			if (maze[i][j] == 'Z') {
				for(int k = 0; k < 8; ++k) {
					ii tmp(i + hx_[k], j + hy_[k]);
					if (valid(tmp) && maze[tmp.first][tmp.second] == '.') {
						maze[tmp.first][tmp.second] = '#';
					}
				}
			}
		}
	}
}

bool isFinal(ii tmp) {
	return maze[tmp.first][tmp.second] == 'B';
}

void printMap() {
	cout << "\n";
	for(int j = 0; j < column; ++j) {
		for(int i = 0; i < row; ++i) {
			cout << maze[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}

bool sssp_bfs(ii s) {
	dist.clear();
	queue<ii> q; q.push(s);
	dist[s] = 0;
	while(!q.empty()) {
		ii u = q.front(); q.pop();
		for(int i = 0; i < 8; ++i) {
			ii tmp(u.first + x_[i], u.second + y_[i]);
			if (valid(tmp)) {
				if(!dist.count(tmp) &&
					(maze[tmp.first][tmp.second] == '.' ||
					 maze[tmp.first][tmp.second] == 'B')) {
					dist[tmp] = dist[u] + 1;
					if (isFinal(tmp)) {
						to = tmp;
						return true;
					}
					q.push(tmp);
				}
			}
		}
	}
	return false;
}

void test() {
	int testCase = 0;
	ifstream fi; fi.open("test.txt"); fi >> testCase;
	for(int p = 0; p < testCase; ++p) {
		fi >> column >> row;
		char tmp;
		for(int j = 0; j < column; ++j) {
			for(int i = 0; i < row; ++i) {
				fi >> tmp;
				if (tmp == 'A') {
					fr.first = i; fr.second = j;
				}
				maze[i][j] = tmp;
			}
		}
		horse_fill();
		bool rlt = sssp_bfs(fr) ;
		if (rlt) {
			cout << "Minimal possible length of a trip is " << dist[to] << "\n";
		} else {
			cout << "King Peter, you can’t go now!\n";
		}
	} 
}

int main() {
	test();
	return 0;
}