#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int numRungs;
vector<int> rungs;

bool can(int k) {
	int prev = 0, next;
	for(int i = 0; i < rungs.size(); ++i) {
		next = rungs[i];
		if (next - prev > k) {
			return false;
		} else if (next - prev == k) {
			--k;
		}
		prev = next;
	}
	return true;
}

void bisection() {
	int lo = 0, hi = 1000000, mid, ans;
	while(hi > lo + 1) {
		mid = (hi + lo) / 2;
		// printf("%d %d -> %d\n", lo, hi, mid);
		if (can(mid)) {
			hi = mid;
			ans = mid;
		} else {
			lo = mid;
		}
	}
	printf("%d\n", ans);
}

void test() {
	ifstream fi; fi.open("test.txt");
	int nt, tc; fi >> nt;
	int val;
	for(int i = 0; i < nt; ++i) {
		fi >> numRungs;
		rungs.clear();
		for(int j = 0; j < numRungs; ++j) {
			fi >> val;
			rungs.push_back(val);
		}
		bisection();
	}
	fi.close();
}

int main() {
	test();
	return 0;
}