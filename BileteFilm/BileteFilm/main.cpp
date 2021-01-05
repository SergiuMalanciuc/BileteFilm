#include <iostream>
#include <fstream>
#include <string>
#include "film.h"

using namespace std;
int optiune;




int main()
{
	cout << "~~~Gestionare bilete film~~~" << endl;
	cout << "MENIU PRICIPAL" << endl;
	cout << "Selecteaza optiunea dorita: " << endl;
	cout << "1. Gestionare filme" << endl;
	cout << "2. Cumparare bilet " << endl;
	cout << "3. Situatie filme rulate" << endl;
	cout << "4. Situatie locuri disponibile" << endl;
	cout << "5. Returnare bilet emis" << endl;
	cout << " " << endl;
	cin >> optiune;



	switch (optiune) {
	case 1:
		int v[3] = { 9, 18, 21 };
		char sds[] = { 'A', 'B', 'C' };
		char dsds[] = "hello";
		char* a = nullptr;
		//Film s1(50, "SDS", "Test", v, 3, "Horror", 50);
		
		Film s2(1, "The Hobbit", "2", v, 3, "Horror", 50);
		
		s2.scrieretext();
		
		



			

			
			


	}
	




}


