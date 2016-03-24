//@keyword: floyd_warshall, transitive_closure
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#define SIZE 100
using namespace std;
typedef pair<int, int> ii;
map<string, int> mp;
bool air1[SIZE][SIZE];
bool air2[SIZE][SIZE];
int V, E;
int curr;

bool hasc(string c) {
	return mp.count(c);
}
void addc(string c) {
	if (!hasc(c)) {
		mp[c] = curr++;
	}
}
int getc(string c) {
	return mp[c];
}

void closure(bool my[SIZE][SIZE]) {
	for(int k = 0; k < V; ++k) {
		for(int i = 0; i < V; ++i) {
			for(int j = 0; j < V; ++j) {
				my[i][j] = my[i][j] || (my[i][k] && my[k][j]);
			}
		}
	}
}

void printc(bool my[SIZE][SIZE]) {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			cout << my[i][j] << " ";
		}
		cout << "\n";
	}
}

bool compare() {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			if (air1[i][j] != air2[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void test() {
	ifstream fi; fi.open("test.txt");
	int nt; fi >> nt;
	for(int tc = 0; tc < nt; ++tc) {
		vector<ii> edge1, edge2;
		curr = 0, V = 0;
		fi >> E;
		for(int i = 0; i < E; ++i) {
			string tmp1, tmp2; fi >> tmp1 >> tmp2;
			addc(tmp1), addc(tmp2);
			edge1.push_back(ii(getc(tmp1), getc(tmp2)));
		}
		fi >> E;
		for(int i = 0; i < E; ++i) {
			string tmp1, tmp2; fi >> tmp1 >> tmp2;
			addc(tmp1), addc(tmp2);
			edge2.push_back(ii(getc(tmp1), getc(tmp2)));
		}
		V = curr;
		memset(air1, false, sizeof(air1));
		memset(air2, false, sizeof(air2));
		for(int i = 0; i < V; ++i) {
			air1[i][i] = air2[i][i] = true;
		}
		for(int i = 0; i < edge1.size(); ++i) {
			ii u = edge1[i];
			air1[u.first][u.second] = true;
		}
		for(int i = 0; i < edge2.size(); ++i) {
			ii u = edge2[i];
			air2[u.first][u.second] = true;
		}
		printc(air1); cout << "\n";
		printc(air2); cout << "\n";
		closure(air1), closure(air2);
		printc(air1); cout << "\n";
		printc(air2); cout << "\n";
		cout << (compare()? "YES" : "NO") << std::endl;
	}
	fi.close();
}

int main() {
	test();
	return 0;
}