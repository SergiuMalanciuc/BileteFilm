#include "Locuri.h"



Locuri::Locuri() : uID(ID++)
{
	numeFilm = "";
	matriceScaune = nullptr;
	numarRanduri = 0;
	numarScaune = 0;
	rand = 0;
	scaun = 0;
}

Locuri::Locuri(int numarRanduri, int numarScaune) : uID(ID++) {
	this->numarRanduri = numarRanduri; 
	this->numarScaune = numarScaune;
}

Locuri::Locuri(string numeFilm, char** matriceScaune, int numarRanduri, int numarScaune, int rand, int scaun) : uID(ID++)
{
	this->numeFilm = numeFilm;
	this->numarRanduri = numarRanduri;
	this->numarScaune = numarScaune;
	this->rand = rand;
	this->scaun = scaun;
	this->matriceScaune = new char* [numarRanduri];
	for (int i = 0; i < numarRanduri; i++) {
		for (int j = 0; j < numarScaune; j++) {
			this->matriceScaune[i][j] = matriceScaune[i][j];
		}
	}
}

Locuri::~Locuri()
{
	{
		if (matriceScaune != nullptr) {
			delete[] matriceScaune;
		}
	}
}



char** Locuri::creareLocuri(int numarRanduri, int scaune)
{
	matriceScaune = new char* [numarRanduri];
	for (int i = 0; i < numarRanduri; i++) {
		matriceScaune[i] = new char[scaune];
	}
	return matriceScaune;
}

void Locuri::initializareScaune(char** matriceScaune, int numarRanduri, int scaune)
{
	for (int i = 0; i < numarRanduri; i++) {
		for (int j = 0; j < numarScaune; j++) {
			matriceScaune[i][j] = 'A' + j;
		}
	}
}

void Locuri::afisareScaune(char** matriceScaune, int numarRanduri, int seats)
{
	for (int i = 0; i < numarRanduri; i++) {
		cout.width(2);
		cout << i + 1 << ' ';
		for (int j = 0; j < numarScaune; j++) {
			cout << matriceScaune[i][j] << ' ';
		}
		cout << endl;
	}
}

int Locuri::ID = 0;