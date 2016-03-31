//@keyword: graph_to_dag, dynamic_programming
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#define REP(i,j,k) for(int (i)=(j);(i)<(k);++(i))
#define MAX_FUEL 301
#define MAX_STOP 100
using namespace std;
const int INF = 100000000;
int memo[MAX_STOP][MAX_FUEL];
typedef vector<int> vi;
vi prices;
vi dists;
int max_dist;

void find_cost(){
	int last = dists.size() - 1;
	REP(i, 0, 201) {
		memo[0][i] = INF;
	}
	memo[0][100] = 0;
	for(int i = 1; i <= last; ++i) {
		for(int j = 0; j <= 200; ++j) {
			int ans = INF;
			for(int k = 0; k < i; ++k) {
				int d = j + dists[i] - dists[k];
				if (d <= 200) {
					ans = min(ans, memo[k][d]);
				}
			}
			if (j >= 1)
				ans = min(ans, memo[i][j - 1] + prices[i]);
			memo[i][j] = ans;
		}
	}
}

void test(){
	ifstream fi; fi.open("test.txt");
	// while(!fi.eof()){
		fi >> max_dist;
		int ns; fi >> ns;
		int dist, price;
		prices.push_back(0);
		dists.push_back(0);
		REP(i,0,ns){
			fi >> dist >> price;
			prices.push_back(price);
			dists.push_back(dist);
		}
		memset(memo, INF, sizeof(memo));
		find_cost();
		int minimum = INF;
		int last = dists.size() - 1; 
		for(int i = 100; i <= 200; ++i) {
			minimum = min(minimum, memo[last][i]);
		}
		cout << minimum << "\n";
	// }
	fi.close();
}

int main() {
	test();
	return 0;
}


