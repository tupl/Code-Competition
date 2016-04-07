#include <iostream>


int LSOne(int i) { return i & (-i); }
class FenwickTree {
private: vi ft;
public:
	int rsq(int k) {
		int total = 0;
		for(; k; k -= LSOne(k)) total += ft[k];
		return total; 
	}
	int rsq(int i, int j) {
		return rsq(j) - (i == 1 ? 0: rsq(i - 1));
	}
	FenwickTree(int n) {
		ft.assign(n + 1, 0);
	}
	int adjust(int k, int val) {
		for(; k < (int)ft.size(); k += LSOne(k)) { ft[k] += val; }
	}
};