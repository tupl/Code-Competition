struct Time {
	int h;
	int m;
	int s;
};

class CompareTime {
public:
	bool operator()(Time& t1, Time& t2) {
		return true;
	}
};

std::priority_queue<Time, vector<Time>, CompareTime> pq;

pq.push
pq.pop()
pq.empty()
