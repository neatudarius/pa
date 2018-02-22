#include <iostream>
#include <set>

using namespace std;

int main() {
	// declarare
	set< pair<int, int> > s;

	pair<int, int> p = {2, 3};
	pair<int, int> q = {2, 4};
	s.insert(p);
	s.insert(p);
	s.insert(q);
	s.insert(q);

	for (auto &p : s) {
		cout << p.first << " " << p.second << "\n";
	}
	// se afiseaza (2, 3), (2, 4) pt ca se compara cu < mai intai first, apoi second

	return 0;
}