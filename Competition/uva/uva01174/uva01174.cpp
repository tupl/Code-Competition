#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <map>
using namespace std;
// edge - weight - two vertieces
typedef pair<int, int> ii;
typedef pair<int, ii> i_ii;
typedef vector<int> vi;
vector< pair<int, ii> > EdgeList, MstList;
int V, E;
vi pset; // parent of element
vi sset; // size of set
int numSet; //Number of set
int mst_cost;

void initSet(int N) {
	pset.assign(N, 0); numSet = N;
	sset.assign(N, 1);
	for(int i = 0; i < N; ++i) { pset[i] = i; }
}
int findSet(int i) {
	return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
}
int numDisjointSets() {
	return numSet;
}
bool isSameSet(int i, int j) {
	return findSet(i) == findSet(j);
}
int sizeOfSet(int i) {
	return sset[findSet(i)];
}
void unionSet(int i, int j) {
	if (findSet(i) != findSet(j)) {
		int orgi = findSet(i);
		int orgj = findSet(j);
		pset[orgi] = orgj;
		sset[orgj] += sset[orgi];
		-- numSet;
	}
}


void Krusal() {
	sort(EdgeList.begin(), EdgeList.end());
	mst_cost = 0;
	initSet(V);
	int counter = 0;
	MstList.clear();
	for(int i = 0; i < E; ++i) {
		i_ii front = EdgeList[i];
		if (!isSameSet(front.second.first, front.second.second)) {
			MstList.push_back(i_ii(front.first, ii(front.second.first, front.second.second)));
			mst_cost += front.first;
			unionSet(front.second.first, front.second.second);
			++ counter;
			if (counter == V - 1) {
				break;
			}
		}
	}
}

int curCity = 0;
map<string, int> si;
map<int, string> is;

int cityIndex(string tmp) {
	if(si.count(tmp)) {
		return si.find(tmp)->second;
	} else {
		si[tmp] = curCity;
		is[curCity] = tmp;
		++curCity;
		return curCity - 1;
	}
}

string indexCity(int u) {
	return is[u];
}

void test() {
	ifstream fi;
	fi.open("input.txt");
	fi >> V >> E;
	cout << V << " " << E << "\n";
	EdgeList.clear();
	for(int i = 0; i < E; ++i) {
		string sfrom, sto;
		int from, to, weight;
		fi >> sfrom >> sto >> weight;
		from = cityIndex(sfrom);
		to = cityIndex(sto);
		printf("%d %d %d\n", from, to, weight);
		EdgeList.push_back( pair<int, ii>( weight, ii(from, to) ) );
	}
	Krusal();
	cout << mst_cost << "\n";
	for(int i = 0; i < MstList.size(); ++i) {
		i_ii tmp = MstList[i];
		string from = indexCity(tmp.second.first);
		string to = indexCity(tmp.second.second);
		cout << from << " " << to << " with weight " << tmp.first << "\n";
	}
	fi.close();
}

int main() {
	test();
	return 0;
}