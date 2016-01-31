#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>

typedef std::vector<int> vi;
vi pset; // parent of element
vi sset; // size of set
int numSet; //Number of set
void initSet(int N) {
	pset.assign(N, 0); numSet = N; sset.assign(N, 1);
	for(int i = 0; i < N; ++i) { pset[i] = i; }
}
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
int numDisjointSets() { return numSet; }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
int sizeOfSet(int i) { return sset[findSet(i)]; }
void unionSet(int i, int j) {
	if (findSet(i) != findSet(j)) {
		int orgi = findSet(i), orgj = findSet(j);
		pset[orgi] = orgj; sset[orgj] += sset[orgi];
		-- numSet;
	}
}

int main(void) {
	return 0;
}