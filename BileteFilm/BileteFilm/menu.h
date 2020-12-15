#include <iostream>
using namespace std;
int optiune;


int menu() {
	cout << "Salut" << endl;
	cout << "Acesta este un meniu" << endl;
	cout << "Apasa pe optiunea dorita" << endl;
	cout << "1. Adauga carte" << endl;
	cout << "2. Scoate carte" << endl;
	cin >> optiune;
	cout << "Ai ales optiunea " << optiune;
	return optiune;
}