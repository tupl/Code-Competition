//@keyword: floyd_warshall, all_pair_shortest_path
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#define REP(i,j,k) for(int (i)=(j); (i) < (k); ++(i))
#define SIZE 100
#define FILL(o,i) memset(o,i,sizeof(o));
#define str string
#define pb push_back
using namespace std;
const int INF = 10000;
int mat[SIZE][SIZE];
int path[SIZE][SIZE];
int V;
map<str, int> mp;
vector<str> rmp;

void printPath(int i, int j) {
	if (i != j) {
		printPath(i, path[i][j]);
		cout << rmp[j] << " ";
	} else {
		cout << rmp[i] << " ";
	}
}

void test() {
	ifstream fi; fi.open("test.txt");
	int nt; fi >> nt;
	REP(tc,0,nt) {
		mp.clear(); rmp.clear();
		fi >> V; str tmp;
		REP(i,0,V) {
			fi >> tmp;
			mp[tmp] = i;
			rmp.pb(tmp);
		}
		FILL(mat, INF);
		int num;
		REP(i,0,V) REP(j,0,V) {
			fi >> num; mat[i][j] = (num == -1)? INF: num;
		}
		REP(i,0,V) REP(j,0,V) {
			path[i][j] = i;
		}
		str name, ori, dest;
		REP(k,0,V) REP(i,0,V) REP(j,0,V) {
			if (mat[i][j] > mat[i][k] + mat[k][j]) {
				mat[i][j] = mat[i][k] + mat[k][j];
				path[i][j] = k;
			}
		}
		int nq; fi >> nq;
		REP(i,0,V) {
			REP(j,0,V) {
				cout << path[i][j] << " ";
			}
			cout << ::endl;
		}
		REP(i,0,nq) {
			fi >> name >> ori >> dest;
			int x = mp[ori], y = mp[dest];
			cout << name << " " << mat[x][y] << ::endl;
			if (x != y) {
				printPath(x, y);
			} else {
				printPath(x, path[x][y]);
				cout << rmp[y];
			}
			cout << ::endl;
		}
	}
	fi.close();
}

int main() {
	test();
	return 0;
}