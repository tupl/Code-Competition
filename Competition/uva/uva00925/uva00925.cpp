//@keyword: floyd_warshall, transitive_closure
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#define SIZE 150
using namespace std;
map<string, int> mp;
vector<string> rmp;
bool mat[SIZE][SIZE];
int V, E;

int getc(string c) {
	return mp[c];
}

void printmat() {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			cout << mat[i][j] << " ";
		}
		cout << std::endl;
	}
	cout << std::endl;
}

void test() {
	int nt; ifstream fi; fi.open("test.txt");
	fi >> nt;
	for(int tc = 0; tc < nt; ++tc) {
		fi >> V; rmp.clear(); mp.clear();
		memset(mat, false, sizeof(mat));
		for(int i = 0; i < V; ++i) {
			string tmp; fi >> tmp;
			rmp.push_back(tmp);
			mp[tmp] = i;
		}
		fi >> E;
		for(int i = 0; i < E; ++i) {
			string dest, src; int nrq;
			fi >> dest >> nrq;
			for(int j = 0; j < nrq; ++j) {
				fi >> src;
				mat[getc(src)][getc(dest)] = true;
			}
		}

		for(int k = 0; k < V; ++k) {
			for(int i = 0; i < V; ++i) {
				for(int j = 0; j < V; ++j) {
					mat[i][j] = mat[i][j] || (mat[i][k] && mat[k][j]);
				}
			}
		}

		for(int i = 0; i < V; ++i) {
			// j -> i
			vector<string> rlt;
			for(int j = 0; j < V; ++j) {
				if (mat[j][i]) {
					bool added = true;
					// j -> k -> i
					for(int k = 0; k < V; ++k) {
						if (mat[j][k] && mat[k][i]) {
							added = false; break;
						}
					}
					if (added) {
						rlt.push_back(rmp[j]);
					}
				}
			}
			if (rlt.size() > 0) {
				cout << rmp[i] << " " << rlt.size() << " ";
				for(int j = 0; j < rlt.size(); ++j) {
					cout << rlt[j] << " ";
				}
				cout << std::endl;
			}
		}
		cout << std::endl;
	}
	fi.close();
}

int main() {
	test();
	return 0;
}