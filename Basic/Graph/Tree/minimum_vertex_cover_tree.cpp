#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#define MAX_V 1000
#define MAX_STATE 2
using namespace std;

int memo[MAX_V][MAX_STATE];
int V, E;
int MVC(int v, int flag) {
	int ans = 0;
	if (memo[v][flag] != -1) return memo[v][flag];
	else if (leaf[v]) {
		ans = flag;
	} else if (flag == 0) {
		ans = 0;
		for(int j = 0; j < (int)Children[v].size(); ++j) {
			ans += MVC(Children[v][j], 1);
		}
	} else if (flag == 1) {
		ans = 1;
		for(int j = 0; j < (int)Children[v].size(); ++j) {
			ans += min(MVC(Children[v][j], 1), MVC(Children[v][j], 0));
	}
	return memo[v][flag] = ans;
}

int main() {
	return 0;
}