#include <iostream>
#include <fstream>
#include <string>
#include "film.h"
#include "Bilet.h"

using namespace std;
int optiune;




int main()
{
	//cout << "~~~Gestionare bilete film~~~" << endl;
	//cout << "MENIU PRICIPAL" << endl;
	//cout << "Selecteaza optiunea dorita: " << endl;
	//cout << "1. Gestionare filme" << endl;
	//cout << "2. Cumparare bilet " << endl;
	//cout << "3. Situatie filme rulate" << endl;
	//cout << "4. Situatie locuri disponibile" << endl;
	//cout << "5. Returnare bilet emis" << endl;
	//cout << " " << endl;
	//cin >> optiune;



		int v[3] = { 1, 2, 3 };
		char sds[] = { 'A', 'B', 'C'};
		char sala[] = "A2";
		char numeCl[] = "Sergiu Malanciuc";
		char* a = nullptr;
		
		/*Bilet s1(1, "Hobbit", v, 3, sala, numeCl, 50);
		cout << s1;*/
		

		Film s2(1, "THD", sds, v, 3, "Horror", 50);
		cout << s2;
		

	




}


