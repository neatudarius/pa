#include <iostream>
#include <set>

using namespace std;

int main() {
	// declarare
	set< int > s;

	int n = 6;
	for (int i = 1; i <= n; ++i) {
		s.insert(10 * i);
	}

	auto it_low = s.lower_bound(22);
	auto it_upp = s.upper_bound(42);
	s.erase(it_low, it_upp);

	for (auto &x : s) {
		cout << x << "\n";
	}
	cout << "\n";

	return 0;
}