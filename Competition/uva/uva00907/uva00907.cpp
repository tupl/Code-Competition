//@keyword: uva_00907, graph_to_dag, add_property
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define REP(i,j,k) for(int (i)=(j);(i) < (k); ++(i))
#define MAX_CAMP 1000
#define MAX_NIGHT 1000
using namespace std;
const int INF = 100000;
typedef vector<int> vi;
vi travel;
int nCamp, nNight;
int cost[MAX_CAMP][MAX_NIGHT];

int solve(int posi, int n_left) {
	if (n_left == 0) {
		int total = 0;
		REP(i,posi,travel.size()) {
			total += travel[i];
		}
		return total;
	}
	if (cost[posi][n_left] != -1) return cost[posi][n_left];
	int ans = INF;
	int range = 0;
	REP(i,posi,nCamp) {
		range += travel[i];
		ans = min(ans, max(range, solve(i + 1, n_left - 1)));
	}
	return cost[posi][n_left] = ans;
}

void test() {
	ifstream fi; fi.open("test.txt");
	fi >> nCamp >> nNight;
	int val;
	REP(i,0,nCamp+1){
		fi >> val;
		travel.push_back(val);
	}
	memset(cost, -1, sizeof(cost));
	cout << solve(0, nNight) << ::endl;
	fi.close();
}

int main() {
	test();
	return 0;
}
