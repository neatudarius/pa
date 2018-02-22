#include <iostream>
#include <set>

using namespace std;

int main() {
	// declarare
	set< pair<int, int> > s;

	pair<int, int> p = {2, 3};
	pair<int, int> q = {2, 3};
	s.insert(p);
	s.insert(p);
	s.insert(q);
	s.insert(q);
	// size == 1 pt ca p == q este true (se compara first si second)
	
	for (auto &p : s) {
		cout << p.first << " " << p.second << "\n";
	}

	return 0;
}