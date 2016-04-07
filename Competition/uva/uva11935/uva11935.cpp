#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const double EPS = 1e-10;
typedef pair<int, int> ii;
vector<pair<double, ii> > events;

// 0 fuel_consumption
// 1 leak
// 2 gas station
// 3 mechanic
// 4 goal

bool can(double gas) {
	double curGas = gas;
	double consump = 0.0;
	double prev = 0.0;
	double isLeak = 0.0;
	for(int i = 0; i < (int) events.size(); ++i) {
		pair<double, ii> ev = events[i];
		double dist = ev.first;
		int type = ev.second.first;
		int extra = ev.second.second;
		if (i > 0) {
			double r = dist - prev;
			curGas -= (consump * r / 100.0);
			curGas -= r * isLeak;
			prev = dist;
		}
		if (curGas < 0.0) {
			return false;
		}
		switch(type) {
			case 0: consump = extra; break;
			case 1: isLeak += 1.0; break;
			case 2: curGas = gas; break;
			case 3: isLeak = 0.0; break;
		}
	}
	return true;
}

void bisection() {
	double lo = 0.0, hi = 100000.0, mid, ans = 0.0;
	while((hi - lo) > EPS) {
		mid = (lo + hi) / 2;
		if (can(mid)) {
			hi = mid; ans = mid;
		} else {
			lo = mid;
		}
	}
	printf("%f\n", ans);
}

void test() {
	ifstream fi; fi.open("test.txt");
	int nt; fi >> nt;
	string cmd;
	double dist, extra;
	for(int tc = 0; tc < nt; ++tc) {
		events.clear();
		int n_e; fi >> n_e;
		for(int j = 0; j < n_e; ++j) {
			fi >> dist >> cmd; extra = 0.0;
			if (cmd == "fuel_consumption") {
				fi >> extra;
				events.push_back(pair<double, ii>(dist, ii(0, extra)));
			} else if (cmd == "leak") {
				events.push_back(pair<double, ii>(dist, ii(1, 0.0)));
			} else if (cmd == "gas_station") {
				events.push_back(pair<double, ii>(dist, ii(2, 0.0)));
			} else if (cmd == "mechanic") {
				events.push_back(pair<double, ii>(dist, ii(3, 0.0)));
			} else if (cmd == "goal") {
				events.push_back(pair<double, ii>(dist, ii(4, 0.0)));
			}
		}
		// cout << can(36.0) << ::endl;
		bisection();
	}
	fi.close();
}

int main() {
	test();
	return 0;
}