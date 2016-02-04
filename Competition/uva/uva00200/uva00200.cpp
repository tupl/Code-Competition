<<<<<<< HEAD
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
const int DFS_WHITE = 0;
const int DFS_BLACK = 1;
vector<vii> AdjList;
vi topoSort;
vi dfs_num;
int V, E;

void dfs2(int u) {
	dfs_num[u] = DFS_BLACK;
	for(int i = 0; i < (int)AdjList[u].size(); ++i) {
		ii v = AdjList[u][i];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs2(v.first);
		}
	}
	topoSort.push_back(u);
}

void topologicalSort() {
	topoSort.clear();
	// dfs_num.assign(V, DFS_WHITE);
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			dfs2(i);
		}
	}
	reverse(topoSort.begin(), topoSort.end());
}

void compare(string m, string n) {
	int len = min(m.length(), n.length());
	for(int i = 0; i < len; ++i) {
		if (m[i] != n[i]) {
			int indx1 = ((int) m[i]) - 65;
			int indx2 = ((int) n[i]) - 65;
			AdjList[indx1].push_back(make_pair(indx2, 0));
			return;
		}
	}
}

void read_input() {
	V = 26;
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	dfs_num.assign(V, -1);
	for(int i = 0; i < alphabet.length(); ++i) {
		vii _;
		AdjList.push_back(_);
	}
	ifstream myfile;
	myfile.open("input.txt");
	string tmp;
	vector<string> vs;
	while(!myfile.eof()) {
		myfile >> tmp;
		if (tmp != "#") {
			vs.push_back(tmp);
			for(int i = 0; i < tmp.length(); ++i) {
				int indx = ((int) tmp[i]) - 65;
				dfs_num[indx] = DFS_WHITE;
			}
		}
	}

	for(int i = 0; i < (int) vs.size() - 1; ++i) {
		compare(vs[i], vs[i+1]);
	}

	myfile.close();
	topologicalSort();
	for(int i = 0; i < (int) topoSort.size(); ++i) {
		cout << alphabet[topoSort[i]];
	}
}

int main() {
	read_input();
	return 0;
=======
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
const int DFS_WHITE = 0;
const int DFS_BLACK = 1;
vector<vii> AdjList;
vi topoSort;
vi dfs_num;
int V, E;

void dfs2(int u) {
	dfs_num[u] = DFS_BLACK;
	for(int i = 0; i < (int)AdjList[u].size(); ++i) {
		ii v = AdjList[u][i];
		if (dfs_num[v.first] == DFS_WHITE) {
			dfs2(v.first);
		}
	}
	topoSort.push_back(u);
}

void topologicalSort() {
	topoSort.clear();
	// dfs_num.assign(V, DFS_WHITE);
	for(int i = 0; i < V; ++i) {
		if (dfs_num[i] == DFS_WHITE) {
			dfs2(i);
		}
	}
	reverse(topoSort.begin(), topoSort.end());
}

void compare(string m, string n) {
	int len = min(m.length(), n.length());
	for(int i = 0; i < len; ++i) {
		if (m[i] != n[i]) {
			int indx1 = ((int) m[i]) - 65;
			int indx2 = ((int) n[i]) - 65;
			AdjList[indx1].push_back(make_pair(indx2, 0));
			return;
		}
	}
}

void read_input() {
	V = 26;
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	dfs_num.assign(V, -1);
	for(int i = 0; i < alphabet.length(); ++i) {
		vii _;
		AdjList.push_back(_);
	}
	ifstream myfile;
	myfile.open("input.txt");
	string tmp;
	vector<string> vs;
	while(!myfile.eof()) {
		myfile >> tmp;
		if (tmp != "#") {
			vs.push_back(tmp);
			for(int i = 0; i < tmp.length(); ++i) {
				int indx = ((int) tmp[i]) - 65;
				dfs_num[indx] = DFS_WHITE;
			}
		}
	}

	for(int i = 0; i < (int) vs.size() - 1; ++i) {
		compare(vs[i], vs[i+1]);
	}

	myfile.close();
	topologicalSort();
	for(int i = 0; i < (int) topoSort.size(); ++i) {
		cout << alphabet[topoSort[i]];
	}
}

int main() {
	read_input();
	return 0;
>>>>>>> f0c25fcdc79de5684a878bb936788db73b6f8cba
}