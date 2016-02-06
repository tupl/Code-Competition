#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
#include <utility>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
vi in_count;
vi topo;
map<string, int> si;
map<int, string> is;

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
	ifstream file;
	file.open("test.txt");
	int numTest;
	file >> numTest;
	for(int op = 0; op < numTest; ++op) {
		AdjList.clear();
		is.clear(); si.clear();
		topo.clear(); in_count.clear();
		file >> V;
		for(int i = 0; i < V; ++i) { vii tmp; AdjList.push_back(tmp); }
		for(int i = 0; i < V; ++i) {
			string tmp;
			file >> tmp;
			pair<string, int> myPair;
			myPair.first = tmp;
			myPair.second = i;
			si.insert(myPair);
			pair<int, string> oPair;
			oPair.first = i;
			oPair.second = tmp;
			is.insert(oPair);
		}
		file >> E;
		for(int i = 0; i < E; ++i) {
			string from, to;
			file >> from >> to;
			int p = si.find(from)->second;
			int q = si.find(to)->second;
			AdjList[p].push_back(make_pair(q, 0));
		}
		for(int i = 0; i < V; ++i) {
			sort(AdjList[i].begin(), AdjList[i].end());
		}

		topoSort();
		for(int i = 0; i < (int)topo.size(); ++i) {
			cout << is.find(topo[i])->second << " ";
		}
		cout << "\n\n";
	}
	file.close();
}

int main() {
	test();
	return 0;
}