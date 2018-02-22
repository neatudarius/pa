--------------------------
reguli generale de cs
C vs class vs struct la PA

--------------------------
#define oo  (1 << 30)
#define ooLL  (1 << 60)

#define INF    (1 << 30)
#define INF_LL (1LL << 60)

---------------------------------------
typedef pair<int, int> edge;

struct edge {
	int x, y;

	edge() {}
	edge(int x, int y) { this->x = x; this->y = y; }

	bool operator<(const edge &other) {
		if (x < other.x) return true;
		if (x > other.x) return false;

		if (y < other.y) return true;
		if (y > other.y) return false;

		return false;
	}

	bool operator==(const edge &other) {
		return x == other.x && y == other.y;
	}
} 

---------------------------------------
no pointers - see vector how to allocate array and matrix

use references when have functions
void f(vector<int> &v) {
	...
}
