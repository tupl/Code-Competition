//@keyword: floyd_warshall, all_pair_shortest_path, diameter_of_graph
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#define SIZE 100
using namespace std;
const int INF = 10000;
map<string, int> mp;
int sepa[SIZE][SIZE];
int V, E;
int curr;

void floyd_warshall() {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				sepa[i][j] = min(sepa[i][j], sepa[i][k] + sepa[k][j]);
			}
		}
	}
}

void addn(string c) {
	std::transform(c.begin(), c.end(), c.begin(), ::tolower);
	if (!mp.count(c)) {
		mp[c] = curr++;
	}
}

int getn(string c) {
	std::transform(c.begin(), c.end(), c.begin(), ::tolower);
	return mp[c];
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> V >> E;
		if (V == 0 && E == 0) break;
		memset(sepa, INF, sizeof(sepa));
		for(int i = 0; i < E; ++i) {
			string tmp1, tmp2; fi >> tmp1 >> tmp2;
			addn(tmp1); addn(tmp2);
			int first = getn(tmp1), second = getn(tmp2);
			sepa[first][second] = sepa[second][first] = 1;
		}
		for(int i = 0; i < V; ++i) { sepa[i][i] = 0; }
		floyd_warshall();
		int diameter = 0;
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				diameter = max(diameter, sepa[i][j]);
			}
		}
		if (diameter >= INF) {
			cout << "DISCONNECTED\n";
		} else {
			cout << diameter << "\n";
		}
	}
	fi.close();
}

int main(int argc, char const *argv[])
{
	test();
	return 0;
}