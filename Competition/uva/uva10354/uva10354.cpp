#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <queue>
#define SIZE 100
#define INF 10000000
using namespace std;
int P, R, BH, OF, YH, M;
int Path[SIZE][SIZE];
int AdjMat[SIZE][SIZE];
int BossMat[SIZE][SIZE];

void reset() {
	for(int i = 0; i < P; ++i) {
		for(int j = 0; j < P; ++j) {
			AdjMat[i][j] = INF;
			BossMat[i][j] = INF;
			Path[i][j] = i;
		}
	}
}

void traverse_path(int i, int j) {
	if(i != j) {
		int a, b; a = i; b = Path[i][j];
		AdjMat[i][j] = AdjMat[j][i] = INF;
	}
}

void floyd_warshall(bool isBoss) {
	for(int k = 0; k < P; ++k) {
		for(int i = 0; i < P; ++i) {
			for(int j = 0; j < P; ++j) {
				if (isBoss) {
					BossMat[i][j] = min(BossMat[i][j], BossMat[i][k] + BossMat[k][j]);
					Path[i][j] = Path[k][j];
				} else {
					AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);
				}
			}
		}
	}
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> P >> R >> BH >> OF >> YH >> M;
		printf("%d %d %d %d %d %d\n", P, R, BH, OF, YH, M);
		--BH, --OF, --YH, --M;
		reset();
		for(int i = 0; i < R; ++i) {
			int a, b, w; fi >> a >> b >> w;
			--a, --b;
			AdjMat[a][b] = AdjMat[b][a] = w;
			BossMat[a][b] = BossMat[b][a] = w;
		}
		floyd_warshall(true);
		traverse_path(BH, OF);
		floyd_warshall(false);
		cout << AdjMat[YH][M] << "\n\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}