//traverse through a list

//sort a list
std::vector<Data> lines;
bool cmp(Data first, Data second) {
	return first.key < second.key;
}
std::sort(lines.begin(), lines.end(), cmp);