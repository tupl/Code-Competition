#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
vector<vii> AdjList;
int V, E;
map<string, int> c2idx;
int counter = 0;
map<ii, vii> AdjList;

void add_city(string city) {
	c2idx[city] = counter;
	++counter;
}

int city_to_index(string city) {
	return c2idx[city];
}

int string_to_time(string sv) {
	return atoi(sv.c_str());
}

void test() {
	ifstream fi; fi.open("test.txt");
	while(!fi.eof()) {
		fi >> V; if (V == 0) return;
		string tmp, tmp1, tmp2;
		for(int i = 0; i < V; ++i) {
			fi >> tmp;
			add_city(tmp);
		}
		int ntrain;
		for(int i = 0; i < ntrain; ++i) {
			int limit; fi >> limit;
			for(int j = 0; j < limit; ++j) {
				fi >> tmp1 >> tmp2;
				int mytime = string_to_time(tmp1);
				int mycity = city_to_index(tmp2);
				
			}
		}
	}
	fi.close();
}

int main()
{
	cout << string_to_time("0900") << "\n";
	return 0;
}


