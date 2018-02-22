#include <iostream>
#include <set>

using namespace std;

struct cmp {
  // operatorul (functia) intoarce true daca A are prioritate mai mare decat B
  // ceea ce inseamna ca daca ar fi un heap, A este spre radacina, iar B spre frunze
  bool operator() (const pair<int, int>& A, const pair<int, int>& B) const {
  	if (A.first > B.first)   return true; 
  	if (A.first < B.first)   return false;
  	if (A.second > B.second) return true;
  	if (A.second < B.second) return false;
  	return false;
  }
};

int main() {
	// declarare
	set< pair<int, int>, cmp > s;

	pair<int, int> p = {2, 3};
	pair<int, int> q = {2, 4};
	s.insert(p);
	s.insert(p);
	s.insert(q);
	s.insert(q);

	for (auto &p : s) {
		cout << p.first << " " << p.second << "\n";
	}
	// se afiseaza (2, 4), (2, 3) pt ca se compara cu
	// cmp: descrescator dupa first, descrescator dupa y

	return 0;
}