#include <iostream>
#include <set>

using namespace std;

int main() {
	// declarare
	set<int> s;

	// inserare
	int x = 10;
	s.insert(x);
	s.insert(x);
	s.insert(x + 1);
	s.insert(x + 1);
	s.insert(x + 1);
	s.insert(x + 115);

	// size
	cout << "size: " << s.size() << "\n";
	
	// afisez cu for each loop
	// set tine elemente unice
	// set tine elementele ordonate conform operatorului <
	for (auto &x : s) {
		cout << x << " ";
	}
	cout << "\n";

	// cautare
	auto it = s.find(x);
	if (it != s.end()) {
		cout << x << " este in set\n";
	} else {
		cout << x << " NU este in set\n";
	}


	// stergere din set
	s.erase(x);
	cout << "size: " << s.size() << "\n";

	// afisez cu iterator
	// set tine elemente unice
	// set tine elementele ordonate conform operatorului <
	for (auto it = s.begin(); it != s.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";

	// cautare
	it = s.find(x);
	if (it != s.end()) {
		cout << x << " este in set\n";
	} else {
		cout << x << " NU este in set\n";
	}

	return 0;
}