#ifndef CLIENT_H
#define CLIENT_H
using namespace std;

class Client {
private:
	static int ID;
	string nume;
	string numeFilmDorit;
	char* email;
	int* locDorit;
	int nrLocuriDorite;
	const int uID;

public:
	Client();
	Client( string nume, string numeFilmDorit, const char* email, int* locDorit, int nrLocuriDorite);
	Client(const Client& s);
	~Client();
	Client operator= (const Client& s) {
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
	Client operator++() {
		this->nrLocuriDorite++;
	}
	Client operator+() {
		Client copy = *this;
		copy.nrLocuriDorite += nrLocuriDorite;
		return copy;
	}
	bool operator!() {
		return nrLocuriDorite > 0;
	}
	int& operator[](int index) throw(exception) {
		if (index >= 0 && index < nrLocuriDorite && locDorit != nullptr) {
			return locDorit[index];
		}
		else {
			throw exception("Index invalid!");
		}
	}
	
	string setNume(string nume);
	string getNume();
	string setNumeFilm(string nume);
	string getNumeFilm();
	char* setEmail(const char* mail);
	char* getEmail();
	int* setLocDorit(int* locDorit, int nrLocuri);
	int* getLocDorit();
	int getNrLocuri();
	int returnUID();
	void returnData();
	int check(int s);
	
	void serializareClient(ofstream& f);
	void deserializareClient(ifstream& f);


	friend ostream& operator<<(ostream&, Client);
	friend istream& operator>>(istream&, Client&);
};





#endif
















