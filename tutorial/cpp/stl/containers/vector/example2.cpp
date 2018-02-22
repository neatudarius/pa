#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));

	int n = 10;

	vector<int> v(n);

	for (int i = 1; i <= n; ++i) {
		v.push_back(i);
	}


	for (int i = 0; i < n; ++i) {
		cout << v[i] << " ";
	}
	cout << "\n";

	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << *it << " ";
		*it = 23423;
	}
	cout << "\n";

	for (int i = 0; i < n; ++i) {
		cout << v[i] << " ";
	}
	cout << "\n";



	return 0;
}