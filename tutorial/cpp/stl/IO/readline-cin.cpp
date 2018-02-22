#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	freopen("readline.in",  "r", stdin);   // redirectez gigel.in la stdin

	string name;
	int age, grade;

	while (cin >> name >> age >> grade) {
		cout << name << "#" << age << "#" << grade << "\n";
	}

	return 0;
}