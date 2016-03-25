//@keyword: all_pair_shortest_path, floyd_warshall
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#define REP(i, j, k) for(int (i)=(j); (i) < (k); ++(i))
#define pb push_back
#define ll long long int
#define FILL(obj, val) memset(obj, val, sizeof(obj))
#define SIZE 100
#define str string
using namespace std;
const int INF = 10000;
int mat[SIZE][SIZE];
int V;
ll geo[SIZE][SIZE];

void test() {
	FILL(mat, INF);
	FILL(geo, 0L);
	ifstream fi; fi.open("test.txt");
	fi >> V;
	REP(i, 0, V) { geo[i][i] = 1L << i; }
	str line; getline(fi , line);
	REP(i, 0, V) { mat[i][i] = 0; }
	REP(i, 0, V) {
		getline(fi , line);
		stringstream ss(line);
		int a;
		while(ss >> a) {
			geo[i][a-1] = geo[a-1][i] = geo[i][i] | geo[a-1][a-1];
			mat[i][a-1] = mat[a-1][i] = 1;
		}
	}
	REP(k,0,V) REP(i,0,V) REP(j,0,V) {
		int val =  mat[i][k] + mat[k][j];
		if (val < mat[i][j]) {
			mat[i][j] = val;
			geo[i][j] = geo[i][k] | geo[k][j];
		} else if (val == mat[i][j]) {
			geo[i][j] |= geo[i][k] | geo[k][j];
		}
	}
	ll full = 0L;
	REP(i,0,V) { full |= 1 << i; }
	int nt; fi >> nt; getline(fi, line);
	REP(i,0,nt){
		vector<int> arr;
		getline(fi , line);
		stringstream ss(line);
		int a;
		while(ss >> a) {
			arr.pb(a - 1);
		}
		ll start = 0L;
		REP(j,0,arr.size()) REP(k,j+1,arr.size()) {
			int x = arr[j], y = arr[k];
			start |= geo[x][y];
		}
		if (start == full) printf("YES\n");
		else printf("NO\n");
	}
	fi.close();
}

int main() {
	test();
	return 0;
}
