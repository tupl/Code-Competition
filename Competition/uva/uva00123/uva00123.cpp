#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <iterator>
#include <list>

struct Data{
	std::string line;
	std::string key;
};

std::string ignores[50];
std::vector<Data> lines;
int count;

std::string transform(std::string origin, std::function<int(int)> oper) {
	std::string s = origin;
	std::transform(s.begin(), s.end(), s.begin(), oper);
	return s;
}

std::string combine(std::vector<std::string> v, std::string del) {
	std::string s = "";
	for(std::vector<std::string>::iterator t = v.begin(); t != v.end(); ++t) {
		s += *t;
		if (std::next(t, 1) != v.end()) { s += del; }
	}
	return s;
}

std::vector<std::string> tokenize(std::string s, std::string delim) {
	int i = 0;	
	std::vector<std::string> v;
    int pos = s.find(delim);
    while (pos != std::string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);
      if (pos == std::string::npos)
         v.push_back(s.substr(i, s.length()));
    }
    return v;
}

void addIgnore(std::string word) {
	ignores[count] = transform(word, ::tolower);
	++count;
}

bool isIgnore(std::string word) {
	for(int i = 0; i < count; ++i) {
		if (ignores[i] == word) {
			return true;
		}
	}
	return false;
}

void process(std::string line) {
	std::vector<std::string> v = tokenize(line, " ");
	for(std::vector<std::string>::iterator iter = v.begin(); iter != v.end(); ++iter ) {
		std::string r = transform(*iter, ::tolower);
		if (!isIgnore(r)) {
			std::string s = "";
			for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
				if (iter != it) {
					s += transform(*it, ::tolower);
				} else {
					s += transform(*it, ::toupper);
				}
				if (std::next(it, 1) != v.end()) { s += " "; }
			}
			Data tmp;
			tmp.line = s;
			tmp.key = r;
			lines.push_back(tmp);
		}
	}
}

bool cmp(Data first, Data second) {
	return first.key < second.key;
}

int main() {
	/*
		is
		the
		of
		and
		as
		a
		but
	*/
	addIgnore("the"); addIgnore("of"); addIgnore("and"); addIgnore("as"); addIgnore("a");
	addIgnore("but"); addIgnore("is");
	/*
		The Ascent of Man
		The Old Man and The Sea
		A Portrait of The Artist As a Young Man
		A Man is a Man but Bubblesort IS A DOG
	*/
	process("Descent of Man");
	process("The Old Man and The Sea");
	process("A Portrait of The Artist As a Young Man");
	process("A Man is a Man but Bubblesort IS A DOG");
	std::sort(lines.begin(), lines.end(), cmp);
	for(std::vector<Data>::iterator it = lines.begin(); it != lines.end(); ++it) {
		std::cout << it->line << std::endl;
	}
	return 0;
}
