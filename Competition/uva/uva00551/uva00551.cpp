#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>

bool open(char sy) { return sy == '(' || sy == '[' || sy == '{' || sy == '<'; }
bool close(char sy) { return sy == ')' || sy == ']' || sy == '}' || sy == '>'; }

void check(char t[3001]) {
	std::stack<char> s;
	int i = 0;
	int len = strlen(t);
	int count = 0;
	while(t[i] != '\0') {
		++count;
		if (open(t[i])) {
			if (t[i] == '(' && t[i+1] == '*') {
				s.push('*');
				i++;
			}
			else {
				s.push(t[i]);
			}
		} else if (close(t[i]) || (t[i] == '*' && t[i+1] == ')')) {
			if (s.empty()) break;
			if (t[i] == '*') {
				if (s.top() != '*') break;
				s.pop();
				++i;
			} else if (t[i] == ')') {
				if (s.top() != '(') {
					break;
				}
				s.pop();
			} else if (t[i] == ']') {
				if (s.top() != '[') {
					break;
				}
				s.pop();				
			} else if (t[i] == '}') {
				if (s.top() != '{') {
					break;
				}
				s.pop();
			} else if (t[i] == '>') {
				if (s.top() != '<') {
					break;
				}
				s.pop();
			}
		}
		++i;
	}
	if (i < len || !s.empty()) {
		if (i >= len && !s.empty()) count++;
		std::cout << "NO " << count << std::endl;
	} else {
		std::cout << "YES" << std::endl;
	}
}

int main() {
	char t[3001];
	strcpy(t, "(*a++(*)");
	check(t);
	char m[3001];
	strcpy(m, "(*a{+}*)");
	check(m);
	return 0;
}