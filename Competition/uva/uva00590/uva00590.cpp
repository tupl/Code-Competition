//@keyword: dag, convert_to_dag
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define REP(i,j,k) for(int (i)=(j);(i) < (k); ++(i))
#define MAX_CITY 15
#define DAY 1000
using namespace std;
const int INF = 100000;
typedef vector<int> vi;
vi cost[MAX_CITY][MAX_CITY];
int nCity, nDay;
int memo[MAX_CITY][DAY];

int getCost(int i, int j, int day) {
	if (cost[i][j].size() == 0) return INF;
	int k = day % (int) cost[i][j].size();
	return cost[i][j][k];
}

int solve(int city, int day) {
	if (day == nDay) {
		if (city == nCity - 1) { // last city
			return 0;
		} else {
			return INF;
		}
	}
	if (memo[city][day] != -1) return memo[city][day];
	int ans = INF;
	REP(i,0,nCity) {
		ans = min(ans, solve(i, day+1) + getCost(city,i,day));
	}
	return memo[city][day] = ans;
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()){
		fi >> nCity >> nDay;
		if (nCity == 0 && nDay == 0) break;
		REP(i,0,nCity) REP(j,0,nCity) {
			cost[i][j].clear();
		}
		REP(i,0,nCity) REP(j,0,nCity) {
			if (j != i) {
				int n, val; fi >> n;
				REP(k,0,n) {
					fi >> val;
					cost[i][j].push_back((val == 0)? INF: val);
				}
			}
		}
		memset(memo, -1, sizeof(memo));
		int val;
		if ((val = solve(0,0)) == INF) {
			printf("No possible flights\n");
		} else {
			printf("%d\n", val);
		}
	}
	fi.close();
}

int main() {
	test();
	return 0;
}