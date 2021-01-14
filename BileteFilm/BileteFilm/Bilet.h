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
	string numeClient;
	int pret;
	static string welcome;


public:

	Bilet() : ID(1){
		numeFilm = " ";
		locuri = nullptr;
		nrLocuri = 0;
		sala = nullptr;
		numeClient = " ";
		pret = 0;
	}

	Bilet(int ID, string numeFilm, int* locuri, int nrLocuri, const char* sala, string numeClient, int pret) : ID(ID) {
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

		this->numeClient = numeClient;
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

		numeClient = s.numeClient;

		pret = s.pret;
	}

	~Bilet() {
		if (locuri != nullptr) {
			delete[] locuri;
		}
		
		if (sala != nullptr) {
			delete[] sala;
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

		numeClient = s.numeClient;

		pret = s.pret;
	}

	Bilet operator++ () {
		this->pret++;
	}

	Bilet operator+ () {
		Bilet copy = *this;
		copy.pret += pret;
		return copy;
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

		int lungimeNumeClient = numeClient.length() + 1;
		f.write((char*)&lungimeNumeClient, sizeof(lungimeNumeClient));
		f.write(numeClient.c_str(), lungimeNumeClient);


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

		size_t lungimeNumeClient = 0;
		f.read((char*)&lungimeNumeClient, sizeof(lungimeNumeClient));
		char* auxNume = new char[lungimeNumeClient];
		f.read(auxNume, lungimeNumeClient);
		numeClient = auxNume;
		cout << "Numele clientului de pe bilet este: " << numeClient << endl;



		f.close();


	}


	friend Bilet operator+(int, Bilet);
	friend ostream& operator<<(ostream&, Bilet);
	friend istream& operator>>(istream&, Bilet);

};

string Bilet::welcome = "Vizionare placuta";


ostream& operator<<(ostream& iesire, Bilet s) {

	iesire << "Numele filmului de pe bilet: " << s.numeFilm << endl;


	if (s.locuri != nullptr && s.nrLocuri > 0) {
		iesire << "Numarul de locuri rezervate pe acest bilet: " << s.nrLocuri << endl;
		iesire << "Numarul locurilor rezervate: " << endl;
		for (int i = 0; i < s.nrLocuri; i++) {
			cout << "Locul: " << s.locuri[i] << endl;
		}
	}



	return iesire;
}
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
	getline(intrare, s.numeClient);

	cout << "Pret: " << endl;
	intrare >> s.pret;

	return intrare;


}