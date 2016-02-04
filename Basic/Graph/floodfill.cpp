#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

int dr[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dc[] = {0, 1, 1,  1, 0, -1, -1, -1};
int num_dire = 8;

// int dr[] = {1, 0, -1,  0};
// int dc[] = {0, 1,  0, -1};
// int num_dire = 4;

char grid[20][20];
int R, C;

int floodfill(int r, int c, char c1, char c2) {
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

int test() {
	R = C = 4;
	grid[0][0] = 'L'; grid[0][1] = 'L'; grid[0][2] = 'L'; grid[0][3] = 'L';
	grid[1][0] = 'L'; grid[1][1] = 'W'; grid[1][2] = 'W'; grid[1][3] = 'L';
	grid[2][0] = 'L'; grid[2][1] = 'W'; grid[2][2] = 'L'; grid[2][3] = 'W';
	grid[3][0] = 'L'; grid[3][1] = 'W'; grid[3][2] = 'W'; grid[3][3] = 'W';
	cout << floodfill(3, 3, 'W', '.') << '\n';
	for(int i = 0; i < R; ++i) {
		for(int j = 0; j < C; ++j) {
			cout << grid[i][j];
		}
		cout << "\n";
	}
}

int main() {
	test();
	return 0;
}