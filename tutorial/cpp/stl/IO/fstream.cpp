#include <iostream>
#include <fstream>

using namespace std;

int main() {
	// deschide fisier in modul read
	ifstream in("gigel.in", ios::in);

	// citire
	int x, y;
	in >> x >> y;

	// afisez la stdout
	std::cout << x << " " <<  y << "\n";

	// inchidere
	in.close();

	// redeschidere
	in.open("gigel.in", ios::in);
	in >> x >> y;
	in.close();


	// scriere in alt fisier
	ofstream out("gigel.out", ios::out);
	out << x << " " << y << "\n";
	out.close();	

	return 0;
}