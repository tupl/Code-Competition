/*
	This template is used for union_find problems
		that help us union two sets.
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>

typedef std::vector<int> vi;
vi pset; // parent of element
vi sset; // size of set
int numSet; //Number of set
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

int main() {
	int N = 5;
	initSet(N);
	unionSet(1, 2);
	std::cout << findSet(1) << std::endl;
	std::cout << findSet(2) << std::endl;
	std::cout << numDisjointSets() << std::endl;
	std::cout << isSameSet(1, 2) << std::endl;
	std::cout << sizeOfSet(1) << std::endl;
	std::cout << sizeOfSet(2) << std::endl << std::endl;
	unionSet(0, 4);
	std::cout << findSet(0) << std::endl;
	std::cout << findSet(4) << std::endl;
	std::cout << numDisjointSets() << std::endl;
	std::cout << isSameSet(0, 1) << std::endl;
	std::cout << sizeOfSet(0) << std::endl;
	std::cout << sizeOfSet(4) << std::endl << std::endl;
	unionSet(0, 1);
	std::cout << findSet(0) << std::endl;
	std::cout << findSet(1) << std::endl;
	std::cout << findSet(2) << std::endl;
	std::cout << findSet(4) << std::endl;
	std::cout << numDisjointSets() << std::endl;
	std::cout << isSameSet(0, 4) << std::endl;
	std::cout << sizeOfSet(0) << std::endl;
	std::cout << sizeOfSet(4) << std::endl;
	return 0;
}
