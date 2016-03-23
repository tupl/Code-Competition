//@keyword: floyd_warshall
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#define SIZE 35
using namespace std;
typedef pair<int, int> ii;
typedef pair<string, string> ss;
typedef vector<ii> vii;
map<string, int> mp;
vector<string> rmp;
bool trans[SIZE][SIZE];
int V, E;
int curr;
void adde(string c) {
	mp[c] = curr;
	rmp.push_back(c);
	++curr;
}
bool hase(string c) { return mp.count(c); }
int gete(string c) { return mp[c]; }

void test() {
	ifstream fi; fi.open("test.txt");
	int counter = 1;
	while(!fi.eof())
	{
		int nE; fi >> nE;
		if (nE == 0) break;
		curr = 0;
		rmp.clear();
		memset(trans, false, sizeof(trans));
		vector<vector<string> > evts;
		evts.assign(nE, vector<string>());
		for(int i = 0; i < nE; ++i) {
			fi >> E;
			for(int j = 0; j < E; ++j) {
				string tmp; fi >> tmp;
				evts[i].push_back(tmp);
				if (!hase(tmp)) {
					adde(tmp);
				}
			}
		}
		V = curr;
		for(int i = 0; i < nE; ++i) {
			for(int j = 0; j < evts[i].size() - 1; ++j) {
				trans[gete(evts[i][j])][gete(evts[i][j + 1])] = true;
			}
		}
		fi >> nE;
		string tmp1, tmp2;
		for(int i = 0; i < nE; ++i) {
			fi >> tmp1 >> tmp2;
			trans[gete(tmp1)][gete(tmp2)] = true;
		}
		for(int k = 0; k < V; ++k) {
			for(int i = 0; i < V; ++i) {
				for(int j = 0; j < V; ++j) {
					trans[i][j] = trans[i][j] || (trans[i][k] && trans[k][j]);
				}
			}
		}

		vii rlt;
		for(int i = 0; i < V; ++i) {
			for(int j = i + 1; j < V; ++j) {
				if (!trans[i][j] && !trans[j][i]) {
					rlt.push_back(ii(i, j));
				}
			}
		}
		cout << "Case " << counter << ", "
			 << rlt.size() << " concurrent events:" << std::endl;
		for(int i = 0; i < (int) rlt.size() && i < 2; ++i) {
			ii u = rlt[i];
			cout << "(" << rmp[u.first] << "," << rmp[u.second] << ") ";
		}
		cout << std::endl;
		++counter;
	}
	fi.close();
}

int main() {
	test();
	return 0;
}

