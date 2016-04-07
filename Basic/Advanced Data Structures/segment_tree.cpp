#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;

class SegmentTree {
private: vi st, A;
	int n;
	int left(int p) {return p << 1;}
	int right(int p) {return (p << 1) + 1;}
	void build(int p, int L, int R) {
		if (L == R) {
			st[p] = L;
		}
		else
		{
			build(left(p), L, (L + R)/2);
			build(right(p), (L + R)/2 +1, R);
			int pos1 = st[left(p)], pos2 = st[right(p)];
			st[p] = (A[pos1] < A[pos2])? pos1 : pos2;
		}
	}
	int rmq(int p, int L, int R, int i, int j) {
		if (j < L || R < i) return -1;
		if (i <= L && R <= j) return st[p];
		int p1 = rmq(left(p), L, (L + R)/2, i, j);
		int p2 = rmq(right(p), (L + R)/2 + 1, R, i, j);
		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
		return (A[p1] < A[p2])? p1 : p2;
	}
	int update(int p, int L, int R, int idx, int val) {
		int i = idx, j = idx;
		if (i > R || j < L) return st[p];
		if (L == i && R == j) {
			A[i] = val;
			return st[p] = L;
		}
		int pos1, pos2;
		pos1 = update(left(p), L, (L + R)/2, idx, val);
		pos2 = update(right(p), (L + R)/2 +1, R, idx, val);
		return st[p] = (A[pos1] < A[pos2])? pos1 : pos2;
	}
public:
	int update(int idx, int val) {
		return update(1, 0, n -1, idx, val);
	}
	SegmentTree(const vi&_A) {
		A = _A;
		n = (int) A.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);
	}
	int rmq(int i, int j) {
		return rmq(1, 0, n -1, i, j); 
	}
};

int main() {
  int arr[] = { 18, 17, 13, 19, 15, 11, 20 };         // the original array
  vi A(arr, arr + 7);                      // copy the contents to a vector
  SegmentTree st(A);
  printf("              idx    0, 1, 2, 3, 4,  5, 6\n");
  printf("              A is {18,17,13,19,15, 11,20}\n");
  printf("RMQ(1, 3) = %d\n", st.rmq(1, 3));             // answer = index 2
  printf("RMQ(4, 6) = %d\n", st.rmq(4, 6));             // answer = index 5
  printf("RMQ(3, 4) = %d\n", st.rmq(3, 4));             // answer = index 4
  printf("RMQ(0, 0) = %d\n", st.rmq(0, 0));             // answer = index 0
  printf("RMQ(0, 1) = %d\n", st.rmq(0, 1));             // answer = index 1
  printf("RMQ(0, 6) = %d\n", st.rmq(0, 6));             // answer = index 5
  printf("              idx    0, 1, 2, 3, 4,  5, 6\n");
  printf("Now, modify A into {18,17,13,19,15,100,20}\n");
  st.update(5, 100);                    // update A[5] from 11 to 100
  printf("These values do not change\n");
  printf("RMQ(1, 3) = %d\n", st.rmq(1, 3));                            // 2
  printf("RMQ(3, 4) = %d\n", st.rmq(3, 4));                            // 4
  printf("RMQ(0, 0) = %d\n", st.rmq(0, 0));                            // 0
  printf("RMQ(0, 1) = %d\n", st.rmq(0, 1));                            // 1
  printf("These values change\n");
  printf("RMQ(0, 6) = %d\n", st.rmq(0, 6));                         // 5->2
  printf("RMQ(4, 6) = %d\n", st.rmq(4, 6));                         // 5->4
  printf("RMQ(4, 5) = %d\n", st.rmq(4, 5));                         // 5->4

  return 0;
}