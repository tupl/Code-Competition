#include <algorithm>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <stack>
#include <vector>
#include <iostream>

int val(char t) {
	if (t == '+' || t == '-'){
		return 1;
	}
	if (t == '*' || t == '/') {
		return 2;
	}
	return 0;
}

int compare(char t, char s) {
	int val1 = val(t);
	int val2 = val(s);
	if (val1 < val2) return -1;
	if (val1 > val2) return 1;
	return 0;
}

void convert(char t[4000]) {
	int i = 0;
	std::stack<char> st;
	while(t[i] != '\0') {
		if (t[i] == '(') {
			st.push(t[i]);
		}
		else if (t[i] == ')')
		{
			while(!st.empty() && st.top() != '(') {
				std::cout << st.top();
				st.pop();
			}
			st.pop(); //Remove '('
		}
		else if (t[i] == '+' || t[i] == '-' || t[i] == '*' || t[i] == '/') {
			while (!st.empty() && compare(st.top(), t[i]) >= 0) {
				std::cout << st.top();
				st.pop();
			}
			st.push(t[i]);
		}
		else{
			std::cout << t[i];
		}
		++i;
	}
	while(!st.empty()) {
		std::cout << st.top();
		st.pop();
	}
	std::cout << std::endl;
}

int main(void) {
	char t[4000];
	strcpy(t, "(3+2)*5");
	convert(t);
	strcpy(t, "4+5*6");
	convert(t);
	strcpy(t, "1*((4+5-3)/6)");
	convert(t);
	return 0;
}