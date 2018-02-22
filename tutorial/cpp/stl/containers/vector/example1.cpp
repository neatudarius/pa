#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));

	int n = 10;

	vector<int> v(n + 1);

	for (int i = 1; i <= n; ++i) {
		v[i] = rand() % 10;
	}


	for (int i = 1; i <= n; ++i) {
		cout << v[i] << " ";
	}
	cout << "\n";


	return 0;
}