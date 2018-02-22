#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
	// presupun ca am  stringul
    string line = "Gigel R 100 2.8";
    // cum extrag: Gigel ca si std::string
    //             R ca si char
    //             100 ca si int
    //             2.8 ca si double?
    string name;
    char move;
    int age;
    double grade;

    stringstream ss(line);
    ss >> name >> move >> age >> grade;

    cout << name << "#" << move << "#" <<age << "#" << grade << "\n";


    // de fapt pot folosi stringstream ca pe snprintf: concatenez chestii
    stringstream buffer;
    buffer << name << "#" << move << "#" <<age << "#" << grade << "\n";

    // buffer.str() contine tot textul concatenat care poate fi stocat unde imi trebuie
    cout << buffer.str(); // am stocat deja \n in buffer

	return 0;
}