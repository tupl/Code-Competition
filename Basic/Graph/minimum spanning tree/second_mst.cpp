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
	int counter = 0;
	initSet(V);
	MstList.clear();
	for(int i = 0; i < E; ++i) {
		i_ii front = EdgeList[i];
		if (!isSameSet(front.second.first, front.second.second)) {
			MstList.push_back(i_ii(front.first, ii(front.second.first, front.second.second)));
			mst_cost += front.first;
			unionSet(front.second.first, front.second.second);
			++ counter;
			if (counter == V - 1) break;
		}
	}
}

void second_krusal() {
	// int from, to;
	int bestSecMst_cost = 100000;
	vector<i_ii> bestSecMstList;

	for(int j = 0; j < MstList.size(); ++j) {
		int mFrom, mTo;
		vector<i_ii> secMstList;
		mFrom = MstList[j].second.first;
		mTo = MstList[j].second.second;
		printf("Mark %d %d\n", mFrom, mTo);
		int secMst_cost = 0;
		int counter = 0;
		initSet(V);

		for(int i = 0; i < E; ++i) {
			i_ii front = EdgeList[i];
			int from = front.second.first;
			int to = front.second.second;
			if (!isSameSet(from, to) &&
				(from != mFrom || to != mTo)) {
				secMstList.push_back(i_ii(front.first, ii(from, to)));
				secMst_cost += front.first;
				unionSet(from, to);
				++ counter;
				if (counter == V - 1) break;
			}
		}

		if (counter == V - 1) {
			if (secMst_cost < bestSecMst_cost) {
				bestSecMst_cost = secMst_cost;
				bestSecMstList = secMstList;
			}
		}
	}

	cout << bestSecMst_cost << "\n";
	for(int i = 0; i < bestSecMstList.size(); ++i) {
		i_ii tmp = bestSecMstList[i];
		printf("%d %d with %d\n", tmp.second.first, tmp.second.second,
			tmp.first);
	}	
}

void test() {
	ifstream fi;
	fi.open("sec_krusal.txt");
	fi >> V >> E;
	cout << V << " " << E << "\n";
	EdgeList.clear();
	for(int i = 0; i < E; ++i) {
		int from, to, weight;
		fi >> from >> to >> weight;
		printf("%d %d %d\n", from, to, weight);
		EdgeList.push_back( pair<int, ii>( weight, ii(from, to) ) );
	}
	Krusal();
	cout << mst_cost << "\n";
	for(int i = 0; i < MstList.size(); ++i) {
		i_ii tmp = MstList[i];
		printf("%d %d with %d\n", tmp.second.first, tmp.second.second,
			tmp.first);
	}
	second_krusal();
	fi.close();
}

int main() {
	test();
	return 0;
}
