#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>

bool check(char t[3001]) {
	std::stack<char> st;
	int i = 0;
	while(t[i] != '\0') {
		if (t[i] == '(' || t[i] == '[') {
			st.push(t[i]);
		} else if (t[i] == ')') {
			if (st.empty()) return false;
			if (st.top() == '(') {
				st.pop();
			} else {
				return false;
			}
		} else if (t[i] == ']') {
			if (st.empty()) return false;
			if (st.top() == '[') {
				st.pop();
			} else {
				return false;
			}
		}
		++i;
	}
	if (!st.empty()) return false;
	return true;
}

int main() {
	char t[129];
	strcpy(t, "([])");
	std::cout << ((check(t)) ? "YES" : "NO") << std::endl;
	char m[129];
	strcpy(m, "(([()])))");
	std::cout << ((check(m)) ? "YES" : "NO") << std::endl;
	char n[129];
	strcpy(n, "([()[]()])()");
	std::cout << ((check(n)) ? "YES" : "NO") << std::endl;
	return 0;
}