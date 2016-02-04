#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

int dr[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dc[] = {0, 1, 1,  1, 0, -1, -1, -1};
int num_dire = 8;

// int dr[] = {1, 0, -1,  0};
// int dc[] = {0, 1,  0, -1};
// int num_dire = 4;

int grid[20][20];
int R, C;

int floodfill(int r, int c, int c1, int c2) {
	if ( r < 0 || r >= R || c < 0 || c >= C)
		return 0;
	if ( grid[r][c] != c1 ) return 0;
	int ans = 1;
	grid[r][c] = c2;
	for(int d = 0; d < num_dire; ++d) {
		ans += floodfill(r + dr[d], c + dc[d], c1, c2);
	}
	return ans;
}

void countWarEages() {
	int eagles = 0;
	for(int i = 0; i < R; ++ i) {
		for(int j = 0; j < C; ++j) {
			if (grid[i][j] == 1) {
				floodfill(i, j, 1, 0);
				++eagles;
			}
		}
	}
	cout << "Contain " << eagles << " war eagles\n";
}

void read_input() {
	ifstream myfile;
	myfile.open("input.txt");
	while (!myfile.eof()) {
		myfile >> R;
		C = R;
		string tmp;
		for(int i = 0; i < R; ++i) {
			myfile >> tmp;
			for(int j = 0; j < C; ++j) {
				if (tmp[j] == '1') {
					grid[i][j] = 1;
				} else if (tmp[j] == '0') {
					grid[i][j] = 0;
				}
			}
		}
		countWarEages();
	}
	myfile.close();
}

int main() {
	read_input();
	return 0;
}