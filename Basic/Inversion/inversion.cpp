//@keyword: inversion_number, merge_sort_variation
#include <iostream>
#include <fstream>
#include <cmath>
#define SIZE 200
using namespace std;
int origin[SIZE];
int extra[SIZE];
int inver;
void merge_sort(int i, int j){
	if (i == j) return;
	int middle = (i + j)/ 2;
	merge_sort(i, middle);
	merge_sort(middle + 1, j);
	int l = i, r = middle + 1, k = 0;
	while(l <= middle && r <= j){
		if (origin[l] <= origin[r]){
			extra[i + k] = origin[l++];
		} else {
			inver += (middle - l + 1);
			extra[i + k] = origin[r++];
		}
		++k;
	}
	while(l <= middle){ extra[i + k] = origin[l++];}
	while(r <= j){ extra[i + k] = origin[r++];}
}

int main() {
  // origin = {1, 20, 6, 4, 5};
	origin[0] = 2; origin[1] = 3; origin[2] = 1;
	// origin[0] = 1; origin[1] = 20; origin[2] = 6; origin[3] = 4; origin[4] = 5;
	merge_sort(0, 2);
	printf(" Number of inversions are %d \n", inver);
	return 0;
}