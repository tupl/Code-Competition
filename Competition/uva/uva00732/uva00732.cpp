#include <algorithm>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <stack>
#include <vector>
#include <iostream>

int r_i;
int r_o;
int total;
int len;
char step[100];
std::stack<char> st;
char s[100];
char t[100];
int curr_src;
int curr_trg;

void recur(int curr_step) {
	// found a solution
	if (curr_step >= total) {
		for(int i = 0; i < total; ++i) {
			std::cout << step[i] << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for(int i = 0; i < 2; ++i) {
			// choose i and it's available
			if (i == 0 && r_i > 0) {
				if (curr_src < len) {
					// saving
					int sr_i = r_i;
					int s_curr_src = curr_src;
					step[curr_step] = 'i';
					--r_i;
					std::stack<char> tmp_st(st);
					st.push(s[curr_src]);
					++curr_src;
					recur(curr_step + 1);
					st = tmp_st;
					curr_src = s_curr_src;
					r_i = sr_i;
				}
			}
			else if (i == 1 && r_o > 0) {
				// if stack is not empty and top is same as what we requires
				if (!st.empty() && st.top() == t[curr_trg]) {
					int sr_o = r_o;
					int s_curr_trg = curr_trg;
					step[curr_step] = 'o';
					--r_o;
					std::stack<char> tmp_st(st);
					st.pop();
					++curr_trg;
					recur(curr_step + 1);
					st = tmp_st;
					curr_trg = s_curr_trg;
					r_o = sr_o;
				}
			}
		}
	}
}

void start() {
	std::cout << "[" << std::endl;
	if (strlen(s) == strlen(t)) {
		len = strlen(s);
		total = 2 * len;
		r_i = len;
		r_o = len;
		curr_src = 0;
		curr_trg = 0;
		recur(0);
	}
	std::cout << "]" << std::endl;
}

int main(void) {
	strcpy(s,"madam");
	strcpy(t,"adamm");
	start();
	std::cout << std::endl;
	strcpy(s,"bahama");
	strcpy(t,"bahama");
	start();
	std::cout << std::endl;
	strcpy(s,"long");
	strcpy(t,"short");
	start();
	std::cout << std::endl;
	strcpy(s,"eric");
	strcpy(t,"rice");
	start();
	std::cout << std::endl;
	return 0;
}