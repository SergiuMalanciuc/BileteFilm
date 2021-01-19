#include <iostream>
#include <string>
#include <fstream>
#include "Client.h"
using namespace std;

Client::Client() : uID(ID++)
{
	nume = "";
	numeFilmDorit = "";
	email = nullptr;
	locDorit = nullptr;
	nrLocuriDorite = 0;
}

Client::Client(string nume, string numeFilmDorit, const char* email, int* locDorit, int nrLocuriDorite) : uID(ID++)
{
	this->nume = nume;
	this->numeFilmDorit = numeFilmDorit;

	if (email != nullptr) {
		int length = strlen(email) + 1;
		this->email = new char[length];
		strcpy_s(this->email, length, email);
	}
	else {
		this->email = nullptr;
	}

	if (locDorit != nullptr && nrLocuriDorite > 0) {
		this->locDorit = new int[nrLocuriDorite];
		this->nrLocuriDorite = nrLocuriDorite;
		for (int i = 0; i < nrLocuriDorite; i++) {
			this->locDorit[i] = locDorit[i];
		}
	}
	else {
		this->locDorit = nullptr;
		this->nrLocuriDorite = 0;
	}
}

Client::Client(const Client& s) : uID(s.ID++)
{
	nume = s.nume;
	numeFilmDorit = s.numeFilmDorit;

	if (s.email != nullptr) {
		int length = strlen(s.email) + 1;
		email = new char[length];
		strcpy_s(email, length, s.email);
	}
	else {
		email = nullptr;
	}

	if (s.locDorit != nullptr && s.nrLocuriDorite > 0) {
		locDorit = new int[s.nrLocuriDorite];
		nrLocuriDorite = s.nrLocuriDorite;
		for (int i = 0; i < s.nrLocuriDorite; i++) {
			locDorit[i] = s.locDorit[i];
		}
	}
	else {
		locDorit = nullptr;
		nrLocuriDorite = 0;
	}

}

Client::~Client()
{
	if (email != nullptr) {
		delete[] email;
	}
	if (locDorit != nullptr) {
		delete[] locDorit;
	}
}

void Client::serializareClient(ofstream& f)
{
	f.write((char*)&uID, sizeof(uID));

	int lungimeNume = nume.length() + 1;
	f.write((char*)&lungimeNume, sizeof(lungimeNume));
	f.write(nume.c_str(), lungimeNume);

	int lungimeFilm = numeFilmDorit.length() + 1;
	f.write((char*)&lungimeFilm, sizeof(lungimeFilm));
	f.write(numeFilmDorit.c_str(), lungimeFilm);

	string mail(email);
	int lungimeEmail = mail.length() + 1;
	f.write((char*)&lungimeEmail, sizeof(lungimeEmail));
	f.write(mail.c_str(), lungimeEmail);

	f.write((char*)&nrLocuriDorite, sizeof(nrLocuriDorite));
	for (int i = 0; i < nrLocuriDorite; i++) {
		f.write((char*)&locDorit[i], sizeof(locDorit[i]));
	}
}

void Client::deserializareClient(ifstream& f)
{
	f.read((char*)&uID, sizeof(uID));

	int lungimeNume = 0;
	f.read((char*)&lungimeNume, sizeof(lungimeNume));
	char* auxNume = new char[lungimeNume];
	f.read(auxNume, lungimeNume);
	nume = auxNume;
	


	int lungimeFilm = 0;
	f.read((char*)&lungimeFilm, sizeof(lungimeFilm));
	char* auxFilm = new char[lungimeFilm];
	f.read(auxFilm, lungimeFilm);
	numeFilmDorit = auxFilm;


	int lungimeMail = 0;
	f.read((char*)&lungimeMail, sizeof(lungimeMail));
	char* auxMail = new char[lungimeMail];
	f.read(auxMail, lungimeMail);
	string mail;
	mail = auxMail;
	int n = mail.length() + 1;
	email = new char[n];
	strcpy_s(email, n, mail.c_str());
	

	f.read((char*)&nrLocuriDorite, sizeof(nrLocuriDorite));
	delete[] locDorit;
	locDorit = new int[nrLocuriDorite];
	for (int i = 0; i < nrLocuriDorite; i++) {
		f.read((char*)&locDorit[i], sizeof(locDorit[i]));
	}



}

ostream& operator<<(ostream& iesire, Client s) {

	
	iesire << "Numele clientului este: " << s.nume << endl;

	iesire << "Numele filmului dorit: " << s.numeFilmDorit << endl;

	if (s.email != nullptr) {
		iesire << "Email" << s.email << endl;
	}

	iesire << "Numarul de locuri dorite: " << s.nrLocuriDorite << endl;
	if (s.locDorit != nullptr && s.nrLocuriDorite > 0) {
		for (int i = 0; i < s.nrLocuriDorite; i++) {
			iesire << "Locul " << i + 1 << ": " << s.locDorit[i] << endl;
		}
	}

	return iesire;
}

istream& operator>>(istream& intrare, Client& s) {



	cout << "Nume client: ";
	intrare >> ws;
	getline(intrare, s.nume);

	cout << "Numele filmului dorit: ";
	intrare >> ws;
	getline(intrare, s.numeFilmDorit);

	cout << "Email-ul: ";
	intrare >> ws;
	char buffer[100];
	intrare.getline(buffer, 99);
	s.email = new char[strlen(buffer) + 1];
	strcpy_s(s.email, strlen(buffer) + 1, buffer);

	cout << "Numarul de locuri dorite: ";
	if (s.locDorit != nullptr) {
		delete[] s.locDorit;
	}
	intrare >> s.nrLocuriDorite;
	if (s.nrLocuriDorite > 0) {
		s.locDorit = new int[s.nrLocuriDorite];
		for (int i = 0; i < s.nrLocuriDorite; i++) {
			cout << "Locul " << i + 1 << " este " << endl;
			intrare >> s.locDorit[i];
		}
	}
	else {
		s.nrLocuriDorite = 0;
		s.locDorit = nullptr;
	}
	return intrare;
}






string Client::setNume(string nume)
{
	this->nume = nume;
	return this->nume;
}

string Client::getNume()
{
	return this->nume;
}

string Client::setNumeFilm(string nume)
{
	this->numeFilmDorit = nume;
	return this->numeFilmDorit;
}

string Client::getNumeFilm()
{
	return this->numeFilmDorit;
}

char* Client::setEmail(const char* mail)
{
	int len = strlen(mail) + 1;
	this->email = new char[len];
	strcpy_s(this->email, len, mail);

	return this->email;
}

char* Client::getEmail()
{
	return this->email;
}

int* Client::setLocDorit(int* locDorit, int nrLocuri)
{
	if (locDorit != nullptr && nrLocuri > 0) {
		this->nrLocuriDorite = nrLocuri;
		this->locDorit = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++) {
			this->locDorit[i] = locDorit[i];
		}
		return this->locDorit;
	}
	else {
		this->locDorit = nullptr;
		this->nrLocuriDorite = 0;
	}
}

int* Client::getLocDorit()
{
	return this->locDorit;
}

int Client::getNrLocuri()
{
	return this->nrLocuriDorite;
}

int Client::returnUID()
{
	return uID;
}

void Client::returnData()
{
	cout << "ID: " << uID << endl;
	cout << "Numele clientului este: " << nume << endl;
}

int Client::check(int s)
{
	if (s == uID) {
		return 1;
	}
	else {
		return 0;
	}
}


int Client::ID = 0;