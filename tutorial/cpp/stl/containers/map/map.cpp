#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
	// count
	map<int, int> h;

	vector<int> v;
	v.push_back(2);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	// 2 3
	// 3 1


	for (int i = 0; i < v.size(); ++i) {
		h[ v[i] ]++;
	}

	for(auto &p : h) {
		cout << p.first << " " << p.second << "\n";
	}

	/*
	if (h[v[i]] == 0) {
	
	}

	auto it = h.find(v[i]);
	if (it != h.end()) {
		// DA
	} else {
		// NU
	}



	*/
	// correct find and usage

	// iterator

	
}