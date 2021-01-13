#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Bilet {
private:
	const int ID;
	string numeFilm;
	int* locuri;
	int nrLocuri;
	char* sala;
	char* numeClient;
	int pret;
	static string welcome;


public:

	Bilet() : ID(1){
		numeFilm = " ";
		locuri = nullptr;
		nrLocuri = 0;
		sala = nullptr;
	}

	Bilet(int ID, string numeFilm, int* locuri, int nrLocuri, const char* sala, const char* numeClient, int pret) : ID(ID) {
		this->numeFilm = numeFilm;

		if (locuri != nullptr && nrLocuri != 0) {
			this->locuri = new int[nrLocuri];
			this->nrLocuri = nrLocuri;
			for (int i = 0; i < nrLocuri; i++) {
				this->locuri[i] = locuri[i];
			}
			
		}
		else {
			this->locuri = nullptr;
			this->nrLocuri = 0;
		}

		if (sala != nullptr) {
			int length = strlen(sala) + 1;
			this->sala = new char[length];
			strcpy_s(this->sala, length, sala);
		}
		else {
			this->sala = nullptr;
		}

		if (numeClient != nullptr) {
			int length = strlen(numeClient) + 1;
			this->numeClient = new char[length];
			strcpy_s(this->numeClient, length, numeClient);
		}
		else {
			this->numeClient = nullptr;
		}
		this->pret = pret;
	}

	Bilet(const Bilet& s) : ID(s.ID) {
		numeFilm = s.numeFilm;

		if (s.locuri != nullptr && s.nrLocuri != 0) {
			nrLocuri = s.nrLocuri;
			locuri = new int[s.nrLocuri];
			for (int i = 0; i < nrLocuri; i++) {
				locuri[i] = s.locuri[i];
			}
		}
		else {
			locuri = nullptr;
			nrLocuri = 0;
		}

		if (s.sala != nullptr) {
			int length = strlen(s.sala) + 1;
			sala = new char[length];
			strcpy_s(sala, length, s.sala);
		}
		else {
			sala = nullptr;
		}

		if (s.numeClient != nullptr) {
			int length = strlen(s.numeClient) + 1;
			numeClient = new char[length];
			strcpy_s(numeClient, length, s.numeClient);
		}
		else {
			numeClient = nullptr;
		}

		pret = s.pret;
	}

	~Bilet() {
		if (locuri != nullptr) {
			delete[] locuri;
		}
		
		if (sala != nullptr) {
			delete[] sala;
		}

		if (numeClient != nullptr) {
			delete[] numeClient;
		}
	}


	Bilet operator= (const Bilet& s) {
		numeFilm = s.numeFilm;

		if (s.locuri != nullptr && s.nrLocuri != 0) {
			nrLocuri = s.nrLocuri;
			locuri = new int[s.nrLocuri];
			for (int i = 0; i < nrLocuri; i++) {
				locuri[i] = s.locuri[i];
			}
		}
		else {
			locuri = nullptr;
			nrLocuri = 0;
		}

		if (s.sala != nullptr) {
			int length = strlen(s.sala) + 1;
			sala = new char[length];
			strcpy_s(sala, length, s.sala);
		}
		else {
			sala = nullptr;
		}

		if (s.numeClient != nullptr) {
			int length = strlen(s.numeClient) + 1;
			numeClient = new char[length];
			strcpy_s(numeClient, length, s.numeClient);
		}
		else {
			numeClient = nullptr;
		}

		pret = s.pret;
	}

	Bilet operator++ () {
		this->pret++;
	}

	bool operator! () {
		return nrLocuri > 0;
	}

	int& operator[](int index) throw (exception)
		{
			if (index >= 0 && index < nrLocuri && locuri != nullptr)
			{
				return locuri[index];
			}
			else
			{
				throw exception("Index invalid!");

			}
		}

	void scriereBilet() {
		ofstream f("bilete.bin", ios::binary);


		int lungimeNume = numeFilm.length() + 1;
		f.write((char*)&lungimeNume, sizeof(lungimeNume));
		f.write(numeFilm.c_str(), lungimeNume);



		f.write((char*)&nrLocuri, sizeof(nrLocuri));
		for (int i = 0; i < nrLocuri; i++) {
			f.write((char*)&locuri[i], sizeof(locuri[i]));
		}



		int lungimeSala = strlen(sala);
		f.write((char*)&lungimeSala, sizeof(lungimeSala));
		f.write((char*)&sala, lungimeSala);
		

		int lungimeNumeClient = strlen(numeClient);
		f.write((char*)&lungimeNumeClient, sizeof(lungimeNumeClient));
		f.write((char*)&numeClient, lungimeNumeClient);


		f.write((char*)&pret, sizeof(pret));



		f.close();
	}

	void citireBilet() {
		ifstream f("bilete.bin", ios::binary);

		int lungimeNume = 0;
		f.read((char*)&lungimeNume, sizeof(lungimeNume));
		char* aux = new char[lungimeNume];
		f.read(aux, lungimeNume);
		numeFilm = aux;
		cout << "Numele filmului de pe bilet este: " << numeFilm << endl;

		f.read((char*)&nrLocuri, sizeof(nrLocuri));
		delete[] locuri;
		locuri = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++) {
			f.read((char*)&locuri[i], sizeof(locuri[i]));
		}
		cout << "Numarul de locuri rezervate pe acest bilet: " << nrLocuri << endl;
		cout << "Numarul locurilor rezervate: " << endl;
		for (int i = 0; i < nrLocuri; i++) {
			cout << "Locul: " << locuri[i] << endl;
		}





		cout << " " << endl;
		f.close();



	}




	friend istream& operator>>(istream&, Bilet);

};

string Bilet::welcome = "Vizionare placuta";

istream& operator>>(istream& intrare, Bilet s) {
	
	cout << "Numele filmului: " << endl;
	intrare >> ws;
	getline(intrare, s.numeFilm);


	cout << "Numarul de locuri dorite" << endl;
	if (s.locuri != nullptr) {
		delete[] s.locuri;
	}
	intrare >> s.nrLocuri;
	if (s.nrLocuri > 0) {
		s.locuri = new int[s.nrLocuri];
		for (int i = 0; i < s.nrLocuri; i++) {
			cout << "Locul: [" << i << "] =";
			intrare >> s.locuri[i];
		}
	}
	else {
		s.nrLocuri = 0;
		s.locuri = nullptr;
	}

	cout << "Sala: " << endl;
	intrare >> ws;
	char buffer[100];
	intrare.getline(buffer, 99);
	s.sala = new char[strlen(buffer) + 1];
	strcpy_s(s.sala, strlen(buffer) + 1, buffer);

	cout << "Numele Clientului: " << endl;
	intrare >> ws;
	char buffer0[100];
	intrare.getline(buffer0, 99);
	s.numeClient = new char[strlen(buffer0) + 1];
	strcpy_s(s.numeClient, strlen(buffer0) + 1, buffer0);

	cout << "Pret: " << endl;
	intrare >> s.pret;

	return intrare;


}