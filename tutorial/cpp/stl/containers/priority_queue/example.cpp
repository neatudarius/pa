#include <iostream>
#include <queue> // priority_queue

using namespace std;

int main() {
	// declarare
	// less<int>()
	// greater<int>()
	            // tip, structura de stocare, comparator
	priority_queue< int, vector<int>, greater<int> > pq;

	for (int i = 0; i < 10; ++i) {
		pq.push(i);
	}

	cout << "size: " << pq.size() << "\n";

	// se foloseste ca o coada
	while (!pq.empty()) {
		auto p = pq.top();
		pq.pop();

		cout << p << "\n";
	}

	return 0;
}