//@keyword: dag, graph_to_dag, dynamic_programming
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#define NSTATE 1000
#define NLEFT 1000
#define REP(i,j,k) for(int (i)=(j);(i)<(k);++(i))
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
vector<vi> sta;
vb special;
int n_state, n_move;
int memo[NSTATE][NLEFT];

int count(int c, int left) {
	if (left < 0) return 0;
	if (memo[c][left] != -1) return memo[c][left];
	int ans = 0;
	if (special[c] && left == 0) ++ans;
	REP(i,0,sta[c].size()) {
		int next = sta[c][i];
		ans += count(next, left - 1);
	}
	return memo[c][left] = ans;
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> n_state; char c, f, t, s;
		special.assign(n_state, false);
		sta.assign(n_state, vi());
		REP(i,0,n_state) {
			fi >> c >> f >> t >> s;
			sta[c-65].push_back(f-65);
			sta[c-65].push_back(t-65);
			if (s=='x') special[c-65] = true;
		}
		fi >> n_move;
		memset(memo, -1, sizeof(memo));
		cout << count(0, n_move) << ::endl;
	}
	fi.close();
}

int main() {
	test();
	return 0;
}