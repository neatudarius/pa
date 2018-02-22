#include <iostream>
#include <stack>

using namespace std;

int main() {
	// declarare
	stack<int> st;

	// de obicei punem cateva elemente initial (minim unul)
	int n = 10;
	for (int i = 0; i < n; ++i) {
		st.push(i);  // inserare - adaugare in varf
	}

	cout << "size: " << st.size() << "\n";

	// in algoritmi vom folosi stiva asa
	while (!st.empty()) {
		int x = st.top();  // obtine elementul din varf
		st.pop();          // sterge elementul din varf (stergerea poate sa fie in alt loc)

		// ...
		// logica specifica algoritmului respectiv
		// ex. afisare
		cout << x << "\n";		
	}
	
	return 0;
}