// https://www.quora.com/Can-topological-sorting-be-done-using-BFS
// this algorithm also find the least/best lexicographical topological ordering
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
vi in_count;
vi topo;

class mycomparison
{
public:
  bool operator() (const int& lhs, const int&rhs) const
  {
    return (lhs>rhs);
  }
};

void topoSort() {
	in_count.assign(V, 0);
	for(int i = 0; i < (int) AdjList.size(); ++i) {
		for(int j = 0; j < (int) AdjList[i].size(); ++j) {
			ii v = AdjList[i][j];
			++ in_count[v.first];
		}
	}
	priority_queue<int, vector<int>, mycomparison> q;
	for(int i = 0; i < (int) in_count.size(); ++i) {
		if (in_count[i] == 0) {
			q.push(i);
		}
	}

	while(!q.empty()) {
		int v = q.top(); q.pop();
		topo.push_back(v);
		for(int i = 0; i < (int) AdjList[v].size(); ++i) {
			ii ll = AdjList[v][i];
			int newv = ll.first;
			-- in_count[newv];
			if (in_count[newv] == 0) {
				q.push(newv);
			}
		}	
	}
}

void test() {
	V = 6;
	for(int i = 0; i < V; ++i) {
		vii tmp;
		AdjList.push_back(tmp);
	}
	ifstream file;
	file.open("typo.txt");
	file >> V >> E;
	for(int i = 0; i < E; ++i) {
		int from, to;
		file >> from >> to;
		AdjList[from].push_back(make_pair(to, 0));
	}
	file.close();
	topoSort();
	for(int i = 0 ; i < (int)topo.size(); ++i) {
		cout << topo[i] << " ";
	}
	cout << "\n";
}

int main() {
	test();
	return 0;
}