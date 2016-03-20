//@keyword all_pair_shortest_path, floyd_warshall
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
#include <cstring>
#include <string>
#define SIZE 100
using namespace std;
map<string, int> currency;
int V, cIdx, E;
double rate[SIZE][SIZE];

void addCur(string cur) {
	currency[cur] = cIdx; ++cIdx;
}

int str2idx(string cur) {
	return currency[cur];
}

void floyd_warshall() {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				rate[i][j] = max(rate[i][j], rate[i][k] * rate[k][j]);
			}
		}
	}
}

void test() {
	ifstream fi; fi.open("test1.txt");
	int ntc = 0;
	while(!fi.eof()) {
		++ntc;
		fi >> V;
		if (V == 0) break;
		cIdx = 0; currency.clear();
		for(int i = 0; i < V; ++i) {
			string tmp; fi >> tmp; addCur(tmp);
		}
		memset(rate, 0.0, sizeof(rate));
		fi >> E;
		for(int i = 0; i < E; ++i) {
			string from, to; double r;
			fi >> from >> r >> to;
			rate[str2idx(from)][str2idx(to)] = r;
		}
		for(int i = 0; i < V; ++i) { rate[i][i] = 1.0; }
		floyd_warshall();
		bool found = false;
		for(int i = 0; i < V; ++i) {
			if (rate[i][i] > 1.0) {
				found = true; break;
			}
		}
		cout << "Case " << ntc << ": ";
		cout << ((found)? "Yes" : "No") << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}
