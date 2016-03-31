//@keyword: dag,
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> box;
const int Unvisited = 0;
const int Visited = 1;
vector<box> boxes;
int nBox, nDim;
vector<int> mark;
vector<int> topo;

vector<int> maxseq;
vector<int> pr;

bool isInside(box l, box r) {
	for(int i = 0; i < nDim; ++i) {
		if (l[i] > r[i]) return false;
	}
	return true;
}

void dfs(int u) {
	mark[u] = Visited;
	for(int i = 0; i < nBox; ++i) {
		if (mark[i] == Unvisited && isInside(boxes[u], boxes[i])) {
			dfs(i);
		}
	}
	topo.push_back(u);
}

void topological() {
	for(int i = 0; i < nBox; ++i) {
		if (mark[i] == Unvisited) {
			dfs(i);
		}
	}
}

void printPath(int i) {
	if (pr[i] != -1) {
		printPath(pr[i]);
	}
	cout << topo[i] + 1 << " ";
}

void solve() {
	maxseq.assign(nBox, 0);
	pr.assign(nBox, -1);
	int maxval = 0, maxidx = -1;
	for(int i = 0; i < nBox; ++i) {
		box cur = boxes[topo[i]];
		int maximum = 0;
		for(int j = 0; j < i; ++j) {
			box pre = boxes[topo[j]];
			if (isInside(pre, cur)) {
				if( maxseq[j] > maximum) {
					maximum = maxseq[j];
					pr[i] = j;
				}
			}
		}
		maxseq[i] = maximum + 1;
		if (maxseq[i] > maxval) {
			maxval = maxseq[i];
			maxidx = i;
		}
	}
	cout << maxval << ::endl;
	printPath(maxidx);
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> nBox >> nDim;
		int val;
		boxes.assign(nBox, box());
		mark.assign(nBox, Unvisited);
		topo.clear();
		for(int i = 0; i < nBox; ++i) {
			for(int j = 0; j < nDim; ++j) {
				fi >> val;
				boxes[i].push_back(val);
			}
		}
		for(int i = 0; i < nBox; ++i) {
			sort(boxes[i].begin(), boxes[i].end());
		}
		topological();
		reverse(topo.begin(), topo.end());
		solve();
		cout << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}
