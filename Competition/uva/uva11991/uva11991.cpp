#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
typedef std::vector<int> vi;
typedef std::map<int, vi> Occur;

Occur occ;

int query(int K, int val) {
	std::map<int, vi>::iterator it = occ.find(val);
	if (it == occ.end()) {
		return 0;
	}
	vi vec = it->second;
	if (vec.size() < K) return 0;
	return vec[K - 1];
}

void solve(int N, int k, int T[10000],
		   int K[10000], int V[10000]) {
	for(int i = 0; i < N; ++i) {
		std::map<int, vi>::iterator it;
		it = occ.find(T[i]);
		if (it == occ.end()) {
			vi tmp;
			occ[T[i]] = tmp;
			it = occ.find(T[i]);
		}
		it->second.push_back(i + 1);
	}

	for(int i = 0; i < k; ++i) {
		std::cout << query(K[i], V[i]) << std::endl;
	}
}

int main() {
	int T[10000] = {1, 3, 2, 2, 4, 3, 2, 1};
	int N = 8, k = 4;
	int K[10000] = {1, 2, 3, 4};
	int V[10000] = {3, 4, 2, 2};
	solve(N, k, T, K, V);
	return 0;
}