#include <iostream>
using namespace std;


class Locuri {
private:
	static int ID;
	string numeFilm;
	char** matriceScaune;
	int numarRanduri;
	int numarScaune;
	int rand;
	int scaun;
	const int uID;

public:

	Locuri();
	Locuri(int numarRanduri, int numarScaune);
	Locuri(string numeFilm, char** matriceScaune, int numarRanduri, int numarScaune, int rand, int scaun);
	~Locuri();

	
	char **creareLocuri(int numarRanduri, int scaune);
	void initializareScaune(char** matriceScaune, int numarRanduri, int scaune);
	void afisareScaune(char** matriceScaune, int numarRanduri, int seats);
	
};