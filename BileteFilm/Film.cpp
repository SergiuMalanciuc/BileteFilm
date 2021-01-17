#include <iostream>
#include <string>
#include <fstream>
#include "Film.h"
using namespace std;

Film::Film() : id(1) {
	nume = " ";
	sala = nullptr;
	ora = nullptr;
	nrDerulari = 0;
	gen = " ";
	pret = 0;
}

Film::Film(int id, string nume, const char* sala, int* ora, int nrDerulari, string gen, int pret) : id(id) {
	
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

}

Film::Film(const Film& s) : id(s.id) { 

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

}

Film::~Film() {
	if (ora != nullptr) {
		delete[] ora;
	}
	if (sala != nullptr) {
		delete[] sala;
	}
}

void Film::serializareFilm(ofstream &f)
{
	int lungimeNume = nume.length() + 1;
	f.write((char*)&lungimeNume, sizeof(lungimeNume));
	f.write(nume.c_str(), lungimeNume);
	//nume -> string

	string salaStoc(sala);
	int lungimeSala = salaStoc.length() + 1;
	f.write((char*)&lungimeSala, sizeof(lungimeSala));
	f.write(salaStoc.c_str(), lungimeSala);
	//sala -> char -> string

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
}

void Film::deserializareFilm(ifstream &f)
{
	int lengthNume = 0;
	f.read((char*)&lengthNume, sizeof(lengthNume));
	char* aux = new char[lengthNume];
	f.read(aux, lengthNume);
	nume = aux;
	cout << "Nume film: " << nume << endl;

	int lungimeSala = 0;
	f.read((char*)&lungimeSala, sizeof(lungimeSala));
	char* auxSala = new char[lungimeSala];
	f.read(auxSala, lungimeSala);
	string sSala;
	sSala = auxSala;
	int n = sSala.length() + 1;
	sala = new char[n];
	strcpy_s(sala, n, sSala.c_str());
	cout << "Sala: " << sala << endl;

	int lengthGen = 0;
	f.read((char*)&lengthGen, sizeof(lengthGen));
	char* aux2 = new char[lengthGen];
	f.read(aux2, lengthGen);
	gen = aux2;
	cout << "Genul: " << gen << endl;

	f.read((char*)&nrDerulari, sizeof(nrDerulari));
	delete[] ora;
	ora = new int[nrDerulari];
	for (int i = 0; i < nrDerulari; i++) {
		f.read((char*)&ora[i], sizeof(ora[i]));
	}
	cout << "Numarul de redari zilnice: " << nrDerulari << endl;
	for (int i = 0; i < nrDerulari; i++) {
		cout << i+1 << ". " << ora[i] << endl;
	}



}

string Film::setNume(string Nume)
{
	this->nume = Nume;
	return this->nume;
}

string Film::getNume()
{
	return this->nume;
}

char* Film::setSala(const char* Sala)
{
	int len = strlen(Sala) + 1;
	this->sala = new char[len];
	strcpy_s(this->sala, len, Sala);

	return this->sala;
}

char* Film::getSala()
{
	return this->sala;
}

int* Film::setOra(int* ore, int nrDerulari)
{
	if (ore != nullptr && nrDerulari > 0) {
		this->nrDerulari = nrDerulari;
		this->ora = new int[nrDerulari];
		for (int i = 0; i < nrDerulari; i++) {
			this->ora[i] = ore[i];
		}
		return this->ora;
	}
	else {
		this->ora = nullptr;
		this->nrDerulari = 0;
		return this->ora;
	}
}

int* Film::getOra()
{
	return this->ora;
}

int Film::getNrDerulari()
{
	return this->nrDerulari;
}

string Film::setGen(string Gen)
{
	this->gen = Gen;
	return this->gen;
}

string Film::getGen()
{
	return this->gen;
}

int Film::setPret(int Pret)
{
	this->pret = Pret;
	return this->pret;
}

int Film::getPret()
{
	return this->pret;
}


ostream& operator<<(ostream& iesire, Film s) {
	iesire << "Numele filmului este " << s.nume << endl;


	if (s.sala != nullptr) {
		iesire << "Sala: " << s.sala << endl;
	}


	cout << "Numarul de redari zilnice: " << s.nrDerulari << endl;
	cout << "Orele de difuzare: " << endl;
	for (int i = 0; i < s.nrDerulari; i++) {
		cout << i+1 << ". " << s.ora[i] << endl;
	}

	iesire << "Genul filmului este: " << s.gen << endl;
	iesire << "Pretul filmului este: " << s.pret << endl;

	return iesire;
}

istream& operator>>(istream& intrare, Film s)
{
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

	return intrare;
}

