#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <math>
#include <map>
#define INF 1000000
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int res[MAX_V][MAX_V], mf, f, s, t;
vi p;

// O(VE^2)
void augment(int v, int minEdge) {
	if (v == s) { f = minEdge; return; }
	else if (p[v] != -1) {
		
	}
}

// O(V^2E) Dinic's algorithm