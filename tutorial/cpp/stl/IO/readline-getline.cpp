#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	freopen("readline.in",  "r", stdin);   // redirectez gigel.in la stdin

	string line;
	while (getline(cin, line)) {
		cout << "(" << line << ")" << "\n";
		// pot folosi sstream sa scot chestii din line
	}

	return 0;
}