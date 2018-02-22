#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));

	int n = 10;

	vector<int> v;

	for (int i = 1; i <= n; ++i) {
		v.push_back(i);
	}

	// int &x = v[i];
	for (auto &x : v) {
		cout << x << " ";
	}
	cout << "\n";

	// x = v[i]
	for (auto x : v) {
		cout << x << " ";
	}
	cout << "\n";

	return 0;
}