#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <cmath>

long long T[100000];
long long R, L, B;
long long S[10001];

void cal_sum(void) {
	long long sum = 0;
	S[0 ] = 0;
	for(int i = 0; i < R; ++i) {
		sum += T[i];
		S[i + 1] = sum; 
	}
}

long long cost(long s, long t) {
	long p = (long) floor((s + t) / 2);
	return (p - s) * T[p] - (S[p] - S[s]) + (S[t + 1] - S[p + 1]) - (t - p) * T[p]; 
}

long long solve() {
	cal_sum();
	long begin = 0, end = 0;
	long max = 0;
	while (end < R) {
		while(cost(begin, end) > B) {
			++begin;
		}
		if (end - begin + 1 > max) {
			max = end - begin + 1;
		}
		++end;
	}
	return max;
}

int main(void) {
	T[0] = 1; T[1] = 2; T[2] = 10; T[3] = 12; T[4] = 14;
	R = 5; L = 20; B = 6;
	std::cout << solve() << std::endl;
	return 0;
}