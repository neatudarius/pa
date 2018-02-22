#include <iostream>
#include <vector>

using namespace std;

int main() {
	// usage: constructors, resize, clear, empty, size, []
	//       array, matrix
	vector<int> v;
	// 1) on demand
	v.push_back(2);
	v.pop_back(2);

	// alocare dinamica
	v.resize(n);
	//v[0], .. , v[n-1]

	v.size();     // cate am alocat/cerut eu
	v.capacity(); // cate are el alocate de fapt in spate
					// size <= capacity

	vector<int> v;
	vector<int> v;


	// push_back, pop_back, front/back, erase

	// vector<bool>

	return 0;
}