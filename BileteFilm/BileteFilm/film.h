#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Film {
private:
	string nume;
	char* sala;
	int* ora;
	int nrDerulari;
	string gen;
	static string cinematograf;
	const int id;
	int pret;

public:

	Film() : id(1) {
		nume = " ";
		sala = nullptr;
		ora = nullptr;
		nrDerulari = 0;
		gen = " ";
		pret = 0;
		cout << "S-a apelat constructorul fara parametrii" << endl;
	}

	Film(int id, string nume, const char* sala, int* ora, int nrDerulari, string gen, int pret) : id(id) {
		this->nume = nume;

		if (sala != nullptr) {
			int len = strlen(sala) + 1;
			this->sala = new char[len];
			strcpy_s(this->sala, len, sala);
		}
		else {
			sala = nullptr;
		}

		if (ora != nullptr && nrDerulari > 0) {
			this->nrDerulari = nrDerulari;
			this->ora = new int[nrDerulari];
			for (int i = 0; i < nrDerulari; i++) {
				this->ora[i] = ora[i];
			}
		}
		else {
			this->ora = nullptr;
			this->nrDerulari = 0;
		}
		this->gen = gen;
		this->pret = pret;

		cout << "S-a apelat constructorul cu parametrii" << endl;


	}

	Film(const Film& s) : id(s.id) { //constructor de copiere
		
		nume = s.nume;

		if (s.sala != nullptr) {
			int len = strlen(s.sala) + 1;
			sala = new char[len];
			strcpy_s(sala, len, s.sala);
		}
		else {
			sala = nullptr;
		}

		if (s.ora != nullptr && s.nrDerulari > 0) {
			nrDerulari = s.nrDerulari;
			ora = new int[s.nrDerulari];
			for (int i = 0; i < s.nrDerulari; i++) {
				ora[i] = s.ora[i];
			}
		}
		else {
			ora = nullptr;
			nrDerulari = 0;
		}

		gen = s.gen;
		pret = s.pret;

		cout << "S-a apelat constructorul de copiere" << endl;

	} 
	
	~Film() {
		if (ora != nullptr) {
			delete[] ora;
		}
		if (sala != nullptr) {
			delete[] sala;
		}
		cout << "S-a apelat destructorul" << endl;
	}

	Film& operator= (const Film& s) {
		if (ora != nullptr) {
			delete[] ora;
		}
		nume = s.nume;
		delete[] sala;
		if (s.sala != nullptr) {
			int lungime = strlen(s.sala) + 1;
			sala = new char[lungime];
			strcpy_s(sala, lungime, s.sala);
		}
		else {
			sala = nullptr;
		}
		if (s.ora != nullptr && s.nrDerulari > 0) {
			nrDerulari = s.nrDerulari;
			ora = new int[s.nrDerulari];
			for (int i = 0; i < s.nrDerulari; i++) {
				ora[i] = s.ora[i];
			}
		}
		else {
			ora = nullptr;
			nrDerulari = 0;
		}
		return *this;
	}
	
	Film operator++ () {
		this->pret++;
	}

	Film operator+ () {
		Film copy = *this;
		copy.pret += pret;
		return copy;
	}
	
	bool operator!()
	{
		return nrDerulari > 0;
	}

	int& operator[](int index) throw (exception) 
	{
		if (index >= 0 && index < nrDerulari && ora != nullptr)
		{
			return ora[index];
		}
		else
		{
			throw exception("Index invalid!");
		}
	}

	


	string setNume(string nume) {
		this->nume = nume;
		return this->nume;
	}

	string getNume() {

		cout << "Numele filmului este " << nume << endl;
		return this->nume;
	}

	string setGen(string gen) {
		this->gen = gen; 
		return this->gen;
	}

	string getGen() {
		cout << "Genul filmului este " << gen << endl;
		return this->gen;
	}




	void scriereFilm() {
		ofstream f("filme.bin", ios::binary);

		int lungimeNume = nume.length() + 1;
		f.write((char*)&lungimeNume, sizeof(lungimeNume));
		f.write(nume.c_str(), lungimeNume);
		//nume -> string

		int lungimeGen = gen.length() + 1;
		f.write((char*)&lungimeGen, sizeof(lungimeGen));
		f.write(gen.c_str(), lungimeGen);
		//gen -> string

		f.write((char*)&nrDerulari, sizeof(nrDerulari));
		//nrDerulari -> int

		for (int i = 0; i < nrDerulari; i++) {
			f.write((char*)&ora[i], sizeof(ora[i]));
		}
		//ora -> int*

		f.close();
		
	}

	void citireFilm() {
		ifstream f("filme.bin", ios::binary);
		
		int lengthNume = 0;
		f.read((char*)&lengthNume, sizeof(lengthNume));
		char* aux = new char[lengthNume];
		f.read(aux, lengthNume);
		nume = aux;

		cout << "Numele filmului stocat in fisier este: " << nume << endl;
		//OK

		int lengthGen = 0;
		f.read((char*)&lengthGen, sizeof(lengthGen));
		char* aux2 = new char[lengthGen];
		f.read(aux2, lengthGen);
		gen = aux2;

		cout << "Genul filmului stocat in fisier este " << gen << endl;

		/*string buffer = "";
		char c = 0;
		while ((c = f.get()) != 0) {
			buffer += c;
		}
		delete[] sala;
		sala = new char[buffer.length() + 1];
		strcpy_s(sala, buffer.length() + 1, buffer.c_str());

		cout << "Sala filmului stocata in fisier este " << sala << endl;*/




		f.read((char*)&nrDerulari, sizeof(nrDerulari));
		delete[] ora;
		ora = new int[nrDerulari];
		for (int i = 0; i < nrDerulari; i++) {
			f.read((char*)&ora[i], sizeof(ora[i]));
		}

		cout << "Numarul de redari zilnice: " << nrDerulari << endl;
		cout << "Orele de difuzare: " << endl;
		for (int i = 0; i < nrDerulari; i++) {
			cout<< "Orele disponibile sunt: " << ora[i] << endl;
		}

		f.close();
	}
	

	


	friend Film operator+(int, Film);
	friend ostream& operator<<(ostream&, Film);
	friend istream& operator>>(istream&, Film);
	

	};


	ostream& operator<<(ostream& iesire, Film s) {
		iesire << "Numele filmului este " << s.nume << endl;
		//iesire << "Sala este" << s.sala << endl;
		if (s.ora != nullptr && s.nrDerulari != 0) {
			for (int i = 0; i < s.nrDerulari; i++) {
				iesire << "Ora " << i+1 << "este " << s.ora[i] << endl;
			}
		}
		//iesire << "Ora este" << s.ora << endl;
		iesire << "Numarul de derulari: " << s.nrDerulari << endl;
		iesire << "Genul filmului este: " << s.gen << endl;
		iesire << "Pretul filmului este: " << s.pret << endl;

		return iesire;
	}

	istream& operator>>(istream& intrare, Film s) {
		
		cout << "Nume";
		intrare >> ws;
		getline(intrare, s.nume);

		cout << "Sala: ";
		intrare >> ws;
		char buffer[100];
		intrare.getline(buffer, 99);
		s.sala = new char[strlen(buffer) + 1];
		strcpy_s(s.sala, strlen(buffer) + 1, buffer);

		cout << "Numar rulari zilnice: ";
		if (s.ora != nullptr) {
			delete[] s.ora;
		}
		intrare >> s.nrDerulari;
		if (s.nrDerulari > 0) {
			s.ora = new int[s.nrDerulari];
			for (int i = 0; i < s.nrDerulari; i++) {
				cout << "Ora[" << i << "] =";
				intrare >> s.ora[i];
			}

		}
		else {
			s.nrDerulari = 0;
			s.ora = nullptr;
		}

		cout << "Genul: ";
		intrare >> ws;
		getline(intrare, s.gen);

		cout << "Pret: ";
		intrare >> s.pret;;




		/*string gen;
		cout << "Genul filmului " << endl;
		intrare >> gen;
		s.setGen(gen);
		

		int pret;
		cout << "Pretul unui bilet:  " << endl;*/
		
		



		cout << "Numele filmului este " << s.nume << endl;
		cout << "Genul filmului este " << s.gen << endl;
		cout << "Pretul unui bilet este: " << s.pret << endl;


		return intrare;
	}
	

	
	string Film::cinematograf = "AFI";

