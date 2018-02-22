#include <iostream>
#include <set>

using namespace std;

int main() {
	// declarare
	set< pair<int, int> > s;

	s.insert({2, 3});
	s.insert({2, 3});
	s.insert({2, 4});
	s.insert({2, 4});
	s.insert({9, 3});
	s.insert({9, 3});
	s.insert({2, 5});

	// cel mai mic element
	auto it_min = s.begin();

	// (*it_min).first
	cout << it_min->first << " " << it_min->second << "\n";


	return 0;
}