int set(int &b, int n) { return b |= 1 << n; }
int clear(int &b, int n) { return b &= ~(1 << n); }
bool test(int b, int n) { return (b & (1 << n)) != 0; }
int toggle(int &b, int n) { return b ^= (1 << n); }
bool first(int b) { return (b & (-b)) != 0; }
int all(int b, int n) { return b = (1 << n) - 1; }