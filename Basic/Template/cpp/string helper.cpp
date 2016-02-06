// convert string into lower, upper
std::string transform(std::string origin, std::function<int(int)> oper) {
	std::string s = origin;
	std::transform(s.begin(), s.end(), s.begin(), oper);
	return s;
}

// combine separate word into a string with delimilator
std::string combine(std::vector<std::string> v, std::string del) {
	std::string s = "";
	for(std::vector<std::string>::iterator t = v.begin(); t != v.end(); ++t) {
		s += *t;
		if (std::next(t, 1) != v.end()) { s += del; }
	}
	return s;
}

// tokennize a string into token with given delimilator
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

//Captitalize the first character
std::string t = "sdfsdfsdfdfsdfsdfdfdfd";
t[0] = toupper(t[0]);
std::cout << t;

//Get permutation
char tmp[50] = "abaacb";
std::next_permutation(tmp, tmp + 6);
// std::prev_permutation(tmp, tmp + 6);
for(int i = 0; tmp[i] != '\0'; ++i) {
	std::cout << tmp[i];
}
std::cout << std::endl;