/*
	Moved to adjacency matrix to solve it
*/

#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <cmath>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
map<int, int> dist;
bool check;

void bipartite_check(int s, int& one, int&zero) {
	queue<int> q; q.push(s);
	one = 0;
	zero = 1;
	dist[s] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = 0; i < (int) AdjList[u].size(); ++i) {
			ii v = AdjList[u][i];
			if(!dist.count(v.first)) {
				dist[v.first] = 1 - dist[u];
				q.push(v.first);
				if (dist[v.first] == 0) {
					++zero;
				}
				else
				{
					++one;
				}
			} else if (dist[v.first] == dist[u]) {
				check = false;
				return;
			}
		}
	}
}

void read_input() {
	ifstream myfile;
	myfile.open("input.txt");
	int numtests;
	myfile >> numtests;
	cout << numtests << "\n";
	for(int i = 0; i < numtests; ++i) {
		AdjList.clear();
		myfile >> V;
		cout << V << "\n";
		for(int j = 0; j < V; ++j) {
			vii tmp;
			AdjList.push_back(tmp);
		}
		for(int j = 0; j < V; ++j) {
			int len;
			myfile >> len;
			cout << "Len == " << len << "\n";
			for(int k = 0; k < len; ++k) {
				int val;
				myfile >> val;
				cout << val - 1 << "\n";
				AdjList[j].push_back(make_pair(val - 1, 0));
				AdjList[val - 1].push_back(make_pair(j, 0));
			}
		}

		for(int i = 0; i < (int) AdjList.size(); ++i) {
			std::vector<ii>::iterator it;
			it = std::unique (AdjList[i].begin(), AdjList[i].end());
			AdjList[i].resize( std::distance(AdjList[i].begin(),it) );
		}

		for(int i = 0; i < (int) AdjList.size(); ++i) {
			cout << "Vertext " << i << " ";
			for(int j = 0; j < (int) AdjList[i].size(); ++j) {
				cout << AdjList[i][j].first << " ";
			}
			cout << "\n";
		}

		int total = 0;
		dist.clear();
		bool check = true;
		for(int j = 0; j < V; ++j) {
			if (!dist.count(j)) {
				int zero, one;
				bipartite_check(j, one, zero);
				if (!check) {
					cout << 0 << "\n"; 
					break;
				}
				total += max(zero, one);
			}
		}
		if (check) {
			cout << total << "\n";
		}
	}
}

int main() {
	read_input();
	return 0;
}