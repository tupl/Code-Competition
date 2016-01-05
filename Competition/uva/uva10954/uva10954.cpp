#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <functional>

class CompareInt {
public:
	bool operator()(int& t1, int& t2) {
		return t1 > t2;
	}
};

int solve(int n, int T[10000]) {
	std::priority_queue<int, std::vector<int>, CompareInt> pq;
	for(int i = 0; i < n; ++i) {
		pq.push(T[i]);
	}
	int first = pq.top();
	pq.pop();
	int second = pq.top();
	pq.pop();
	int sum = first + second;
	int total = sum;
	for(int i = 2; i < n; ++i) {
		sum += pq.top();
		total += sum;
		pq.pop();
	}
	return total;
}

int main(void) {
	int T[10000] = {1, 2, 3};
	std::cout << solve(3, T) << std::endl;
	return 0;
}