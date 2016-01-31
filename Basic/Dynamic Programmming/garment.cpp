/*
	Solution of this UVA11450 problem with TOP-DOWN approach
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

int M, C;
int mMoney[201][20];
int p[20][20];
int K[20];
int negInfi = -1000000;

void init() {
	for( int i = 0; i <= M; ++i ) {
		for( int j = 0; j < C; ++j ) {
			mMoney[i][j] = negInfi;
		}
	}
}

int solve(int m, int c) {
	if (m < 0) return negInfi;
	if (c < 0) return 0;
	if (mMoney[m][c] >= 0) return mMoney[m][c];
	int ans = negInfi;
	for( int i = 0; i < K[c]; ++i ) {
		ans = max(ans, solve(m - p[c][i], c - 1) + p[c][i]);
	}
	return mMoney[m][c] = ans;
}

int main() {
	M = 100; C = 4;
	K[0] = 3; K[1] = 2; K[2] = 4; K[3] = 4;
	p[0][0] = 8; 	p[0][1] = 6; 	p[0][2] = 4;
	p[1][0] = 5; 	p[1][1] = 10;
	p[2][0] = 1;  	p[2][1] = 3; 	p[2][2] = 3; 	p[2][3] = 7;
	p[3][0] = 50; 	p[3][1] = 14; 	p[3][2] = 23; 	p[3][3] = 8;
	init();
	printf("Result = %d\n", solve(M, C - 1));

	M = 20; C = 3;
	K[0] = 3; K[1] = 2; K[2] = 4;
	p[0][0] = 4; 	p[0][1] = 6; 	p[0][2] = 8;
	p[1][0] = 5; 	p[1][1] = 10;
	p[2][0] = 1;  	p[2][1] = 3; 	p[2][2] = 5; 	p[2][3] = 5;
	init();
	printf("Result = %d\n", solve(M, C - 1));

	M = 5; C = 3;
	K[0] = 3; K[1] = 2; K[2] = 4;
	p[0][0] = 6; 	p[0][1] = 4; 	p[0][2] = 8;
	p[1][0] = 10; 	p[1][1] = 6;
	p[2][0] = 7;  	p[2][1] = 3; 	p[2][2] = 1; 	p[2][3] = 7;
	init();
	printf("Result = %d\n", solve(M, C - 1));
	return 0;
}