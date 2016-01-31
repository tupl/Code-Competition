#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <deque>

int maxk(int N, int K, int T[1000]) {
	int max = 0;
	for(int i = 0; i < K; ++i) {
		max += T[i];
	}
	int begin = 0, end = K - 1;
	int sum = max;
	while(end + 1 < N) {
		++ begin;
		++ end;
		sum = sum + T[end] - T[begin - 1];
		if (sum > max) max = sum;
	}
	return max;
}

int main(void) {
	int N = 6, K = 3;
	int T[1000] = {10, 50, 30, 20, 5, 1};
	std::cout << maxk(N, K, T) << std::endl;
	return 0;
}