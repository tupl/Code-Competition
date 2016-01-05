#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <functional>
#include <algorithm>
#include <list>

struct Gr {
	int id;
	int t;
	int interval;
};

class CompareGr {
public:
	bool operator()(Gr& t1, Gr& t2) {
		if (t1.t < t2.t) return false;
		if (t1.t == t2.t && t1.id < t2.id) return false;
		return true;
	}
};

std::vector<int> argus(int N, int id[100000], int t[100000], int K) {
	std::vector<int> v;
	std::priority_queue<Gr, std::vector<Gr>, CompareGr> pq;
	for(int i = 0; i < N; ++i) {
		Gr tmp;
		tmp.id = id[i];
		tmp.t = t[i];
		tmp.interval = t[i];
		pq.push(tmp);
	}
	for(int i = 0; i < K; ++i) {
		Gr tmp = pq.top();
		pq.pop();
		v.push_back(tmp.id);
		tmp.t += tmp.interval;
		pq.push(tmp);
	}
	return v;
}

int main(void) {
	int id[100000] = {2004, 2005};
	int t[10000] = {200, 300};
	int N = 2, K = 5;
	std::vector<int> v = argus(N, id, t, K);
	for(std::vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter) {
		std::cout << *iter << std::endl;
	}
	return 0;
}