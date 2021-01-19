#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Film.h"
#include "Bilet.h"
#include "Client.h"
#include "Locuri.h"

using namespace std;
void gestionareMeniu();
void optiuneUnu();
void scriereFilm();
void citireFilme();
void cautareFilm();
void stergereFilm();

void optiuneDoi();
void scriereBilet();
void citireBilet();
void cautareBilet();
void stergereBilet();

void optiuneTrei();
void scriereClient();
void citireClient();
void cautareClient();
void stergereClient();

void optiunePatru();
void gestionareLocuri();


int counter;

int main() {
	
	gestionareMeniu();
	

}


void gestionareMeniu() {
	int optiuneMeniu;
	
	do
	{
			cout << "\n\t---------------MENIU PRINCIPAL---------------";
			cout << "\n\tAlegeti optiunea dorita: ";
			cout << "\n\t1 Gestionare filme";
			cout << "\n\t2 Gestionare clienti";
			cout << "\n\t3 Gestionare bilete";
			cout << "\n\t4 Gestionare locuri libere";
			cout << "\n\t5 Inchidere" << endl;
		cin >> optiuneMeniu;

		switch (optiuneMeniu) {
		case 1:
			optiuneUnu();
			break;
		case 2:
			optiuneDoi();
			break;
		case 3:
			optiuneTrei();
			break;
		case 4:
			optiunePatru();
			break;
		case 5:
			break;

		default:
			cout << "Ai ales optiunea gresita" << endl;
			break;
		}
	} while (optiuneMeniu != 4);
}

void optiuneUnu() {
	int optiune;
	cout << "----------------" << endl;
	cout << "1. Adauga un film nou" << endl;
	cout << "2. Listare filme existente" << endl;
	cout << "3. Listare detalii film" << endl;
	cout << "4. Sterge film" << endl;
	cout << "5. Inapoi la meniul principal" << endl;
	cin >> optiune;
	switch (optiune) {
	case 1:
		scriereFilm();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();

		break;
	case 2:
		citireFilme();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 3:
		cautareFilm();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 4:
		stergereFilm();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 5:
		gestionareMeniu();

	default:
		cout << "Optiunea aleasa nu exista";
		break;
	}
}
void scriereFilm() {


	ofstream f("film.bin", ios::binary);

	cout << "Cate filme doresti sa adaugi?" << endl;
	cin >> counter;
	for (int i = 0; i < counter; i++) {
		Film film;
		cin >> film;
		film.serializareFilm(f);

	}
	f.close();




}
void citireFilme() {

	ifstream f("film.bin", ios::in | ios::out);
	Film film;
	int oldID = 500;
	int newID;

	while (!f.eof()) {

		film.deserializareFilm(f);


		newID = film.returnUID();

		if (newID != oldID) {
			film.returnData();
			oldID = film.returnUID();
		}
	}
	f.close();
}
void cautareFilm() {

	int idCautat;
	long pozitie;
	char confirmare = 'f';
	Film film;
	cout << "ID-ul filmului dorit: " << endl;
	cin >> idCautat;
	ifstream f("film.bin", ios::in | ios::out);
	f.seekg(0);
	while (!f.eof()) {
		pozitie = f.tellg();

		film.deserializareFilm(f);
		if (film.returnUID() == idCautat) {
			cout << film;
			f.seekg(pozitie);
			confirmare = 't';
			break;
		}
	}
	if (confirmare == 'f') {
		cout << "Nu a fost gasit nici un film cu acest ID" << endl;
	}

}
void stergereFilm() {


	int cautareID = 0;
	int flag = 0;
	cout << "ID-ul filmului ce urmeaza a fi sters: ";
	cin >> cautareID;

	Film film;

	ifstream f("film.bin", ios::in);
	ofstream g("temp.bin", ios::out);
	f.seekg(0);

	while (!f.eof()) {
		film.deserializareFilm(f);
		flag = film.check(cautareID);
		if (flag == 0) {
			film.serializareFilm(g);
		}
		if (flag == 1) {
			flag = 0;
		}
	}
	f.close();
	g.close();
	remove("film.bin");
	rename("temp.bin", "film.bin");


}

void optiuneDoi() {
	int optiune;
	cout << "----------------" << endl;
	cout << "1. Client nou" << endl;
	cout << "2. Vizualizare clienti activi" << endl;
	cout << "3. Vizualizare detalii clienti" << endl;
	cout << "4. Stergere client" << endl;
	cout << "5. Inapoi la meniul principal" << endl;
	cin >> optiune;
	switch (optiune)
	{
	case 1:
		scriereClient();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 2:
		citireClient();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 3:
		cautareClient();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 4:
		stergereClient();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 5:
		gestionareMeniu();
		break;
	default:
		break;
	}
}
void scriereClient() {

	ofstream f("client.bin", ios::binary);
	cout << "Cati clienti doresti sa adaugi?" << endl;
	cin >> counter;
	for (int i = 0; i < counter; i++) {
		Client client;
		cin >> client;
		client.serializareClient(f);
	}
	

}
void citireClient() {
	ifstream f("client.bin", ios::in | ios::out);
	Client client;
	int oldID = 500;
	int newID;

	while (!f.eof()){
		client.deserializareClient(f);
		
		newID = client.returnUID();
		if (newID != oldID) {
			client.returnData();
			oldID = client.returnUID();
		}
	}
	f.close();
}
void cautareClient() {
	int idCautat;
	long pozitie;
	char confirmare = 'f';
	Client client;
	cout << "ID-ul clientului dorit: " << endl;
	cin >> idCautat;
	ifstream f("client.bin", ios::in | ios::out);
	f.seekg(0);
	while (!f.eof()) {
		pozitie = f.tellg();

		client.deserializareClient(f);
		if (client.returnUID() == idCautat) {
			cout << client;
			f.seekg(pozitie);
			confirmare = 't';
			break;
		}
		if (confirmare == 'f') {
			cout << "Nu a fost gasit nici un client dupa acest ID" << endl;
		}
	}
}
void stergereClient() {

	int cautareID = 0;
	int flag = 0;
	cout << "ID-ul clientului ce urmeaza a fi sters :";
	cin >> cautareID;

	Client client;
	
	ifstream f("client.bin", ios::in);
	ofstream g("temp.bin", ios::out);
	f.seekg(0);

	while (!f.eof()) {
		client.deserializareClient(f);
		flag = client.check(cautareID);
		if (flag == 0) {
			client.serializareClient(g);
		}
		if (flag == 1) {
			flag = 0;
		}
	}
	f.close();
	g.close();
	remove("client.bin");
	rename("temp.bin", "client.bin");
}


void optiuneTrei() {
	int optiune;
	cout << "----------------" << endl;
	cout << "1. Adauga un bilet nou" << endl;
	cout << "2. Vezi toate biletele existente" << endl;
	cout << "3. Detalii despre bilet" << endl;
	cout << "4. Sterge bilet existent" << endl;
	cout << "5. Inapoi la meniul principal" << endl;
	cin >> optiune;
	switch (optiune) {
	case 1:
		scriereBilet();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 2:
		citireBilet();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 3:
		cautareBilet();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 4:
		stergereBilet();
		cout << "Inapoi la meniul principal";
		gestionareMeniu();
		break;
	case 5:
		gestionareMeniu();
		break;
	}

}
void scriereBilet() {
	ofstream f("bilet.bin", ios::binary);

	cout << "Cate bilete doresti sa adaugi?" << endl;
	cin >> counter;
	for (int i = 0; i < counter; i++) {
		Bilet bilet;
		cin >> bilet;
		bilet.serializareBilet(f);

	}
	f.close();
}
void citireBilet() {
	ifstream f("bilet.bin", ios::in | ios::out);
	Bilet bilet;
	int oldID = 500;
	int newID;

	while (!f.eof()) {
		bilet.deserializareBilet(f);

		newID = bilet.returnUID();
		if (newID != oldID) {
			bilet.returnData();
			oldID = bilet.returnUID();
		}
	}
	f.close();
}
void cautareBilet() {
	int idCautat;
	long pozitie = 0;
	char confirmare = 'f';
	Bilet bilet;
	cout << "ID-ul biletului cautat: " << endl;
	cin >> idCautat;
	ifstream f("bilet.bin", ios::in | ios::out);
	f.seekg(0);
	while (!f.eof()) {
		bilet.deserializareBilet(f);
		if (bilet.returnUID() == idCautat) {
			cout << bilet;
			f.seekg(pozitie);
			confirmare = 't';
			break;
		}
		if (confirmare == 'f') {
			cout << "Nu a fost gasit nici un bilet cu acest ID";
		}
	}
}
void stergereBilet() {

	int cautareID = 0;
	int flag = 0;
	cout << "ID-ul biletului pe care doresti sa il stergi: ";
	cin >> cautareID;
	Bilet bilet;
	ifstream f("bilet.bin", ios::in);
	ofstream g("temp.bin", ios::out);
	f.seekg(0);

	while (!f.eof()) {
		bilet.deserializareBilet(f);
		flag = bilet.check(cautareID);
		if (flag == 0) {
			bilet.serializareBilet(g);
		}
		if (flag == 1) {
			flag = 0;
		}
	}
	f.close();
	g.close();
	remove("bilet.bin");
	rename("temp.bin", "bilet.bin");


}




void optiunePatru() {
	gestionareLocuri();
}
void gestionareLocuri() {
	int numarRanduri;
	int numarScaune;
	int scauneDisponibile;
	char** matriceScaune;
	char selectare[3];
	int rand;
	int scaun;
	char raspuns;

	cout << "Introduceti numarul de randuri: ";
	cin >> numarRanduri;
	cout << "Introduceti numarul de scaune/rand: ";
	cin >> numarScaune;
	scauneDisponibile = numarRanduri * numarScaune;

	Locuri loc(numarRanduri, numarScaune);

	matriceScaune = loc.creareLocuri(numarRanduri, numarScaune);

	loc.initializareScaune(matriceScaune, numarRanduri, numarScaune);

	loc.afisareScaune(matriceScaune, numarRanduri, numarScaune);

	do {

		do {

			cout << "Sunt: " << scauneDisponibile << " scaune disponibile" << endl;
			cout << "Introduceti scaunul dorit: " << endl;
			cin >> selectare;
			rand = selectare[0] - '1';
			if (selectare[1] >= '0' && selectare[1] <= '9') {
				rand += 1;
				rand *= 10;
				rand += (selectare[1] - '1');
				selectare[1] = selectare[2];
			}
			scaun = selectare[1] - 'A';
			if (rand < 0 || rand > numarRanduri - 1) {
				cout << "Selectarea randurilor se face de la 1 la " << numarRanduri << endl;
				cout << "Incercati sa selectati alt rand." << endl;
			}
			if (scaun < 0 || scaun > numarScaune - 1) {
				cout << "Selectarea scaunelor se face de la A la " << char('A' + (numarScaune - 1)) << endl;
				cout << "Alegeti un alt scaun" << endl;
			}
		}while (rand <0 || rand > numarRanduri - 1 || scaun < 0 || scaun > numarScaune - 1);

			if (rand >= 0) {
				if (matriceScaune[rand][scaun] == '-') {
					cout << "Locul selectat a fost deja ocupat.";
				}
				else {
					matriceScaune[rand][scaun] = '-';
					scauneDisponibile--;
				}
				if (scauneDisponibile == 0) {
					cout << "Nu mai sunt locuri disponibile" << endl;
				}
			}
			loc.afisareScaune(matriceScaune, numarRanduri, numarScaune);
			do {
				cout << endl << "Rezervati inca un scaun? (Y/N)" << endl;
				cin >> raspuns;
				raspuns = toupper(raspuns);
				if (raspuns != 'Y' && raspuns != 'N') {
					cout << "Raspunsul oferit este gresit" << endl;
					cout << "Alegeti 'Y' sau 'N' " << endl;
				}
			} while (raspuns != 'Y' && raspuns != 'N');
			if (raspuns == 'N') {
				rand = -1;
			}


	} while(scauneDisponibile > 0 && rand >= 0);





}



