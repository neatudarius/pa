#include <iostream>
#include <set>

using namespace std;

int conditie_complicata(int x) {
	return x == 40;  // :D
}

int main() {
	// declarare
	set< int > s;

	int n = 6;
	for (int i = 1; i <= n; ++i) {
		s.insert(10 * i);
	}
	// 10, 20, 30, 40, 50, 60


	// ...
	// sa zicem ca trebuie sa stergem numarul x in anumite conditii
	// care ne oblica sa traversam setul ca sa decidem dac stergem sau nu
	
	/*
		Iterators, pointers and references referring to elements removed
 	by the function are invalidated.
    	All other iterators, pointers and references keep their validity.
    */
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (conditie_complicata(*it)) {
			auto it_tmp = it;
			--it;

			s.erase(it_tmp);
		}
	}
	
	// a disparut 40
	for (auto &x : s) {
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}