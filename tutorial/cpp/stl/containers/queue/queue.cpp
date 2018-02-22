#include <iostream>
#include <queue>

using namespace std;

int main() {
	// declarare
	queue<int> Q;

	// de obicei punem cateva elemente initial (minim unul)
	int n = 10;
	for (int i = 0; i < n; ++i) {
		Q.push(i);  // inserare - adaugare in varf
	}

	cout << "size: " << Q.size() << "\n";

	// in algoritmi vom folosi stiva asa
	while (!Q.empty()) {
		int x = Q.front();  // obtine elementul din varf
		Q.pop();          // sterge elementul din varf (stergerea poate sa fie in alt loc)

		// ...
		// logica specifica algoritmului respectiv
		// ex. afisare
		cout << x << "\n";		
	}

	return 0;
}