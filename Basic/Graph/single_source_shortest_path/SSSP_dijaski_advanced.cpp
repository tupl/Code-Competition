//@template advanced_sssp advanced_dijaski
struct Stt
{
	...
	Stt(...) {....}
};

struct SttComp
{
    bool operator()(const Stt& a, const Stt& b) const { ... }
};

struct ScStt
{
	int score; Stt state;
	ScStt(int _score, Stt _st) { score = _score; state = _st; }
};

struct ScSttComp
{
    bool operator()(const ScStt& a, const ScStt& b) const { ... }
};

bool is_final(Stt s) {...}
int sssp_dijiska(Stt s) {
	map<Stt, int, SttComp> dist; dist[s] = 0;
	priority_queue<ScStt, vector<ScStt>, ScSttComp> pq;
	pq.push(ScState(0, s));
	while(!pq.empty()){
		ScStt u = pq.top(); pq.pop();
		if (u.score > dist[u.state]) continue;
		if (is_final(u.state)) {
			.... return dist[u.state];
		}
		// for each neighbor Stt v
			// weight = u -> v
			int t_score = dist[u.state] + weight;
			if (!dist.count(v) || t_score < dist[v]) {
				dist[v] = t_score;
				pq.push(ScStt(t_score, v));
			}
	}
	return -1;
}