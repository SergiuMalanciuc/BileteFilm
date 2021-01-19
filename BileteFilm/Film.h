using namespace std;


class Film {
private:
	static int ID;
	string nume;
	char* sala;
	int* ora;
	int nrDerulari;
	string gen;
	const int uID;
	int pret;
public:

	Film();
	Film(string nume, const char* sala, int* ora, int nrDerulari, string gen, int pret);
	Film(const Film& s);
	~Film();
	
	Film& operator=(const Film& s) {
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
		this->pret++; }
	Film operator+ () {
		Film copy = *this;
		copy.pret += pret;
		return copy;
	}
	bool operator!() {
		return nrDerulari > 0;
	}
	int& operator[](int index) throw (exception) {
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
	}
	void serializareFilm(ofstream &f);
	void deserializareFilm(ifstream& f);




	string setNume(string Nume);
	string getNume();
	char* setSala(const char* Sala);
	char* getSala();
	int* setOra(int* ore, int nrDerulari);
	int* getOra();
	int getNrDerulari();
	string setGen(string Gen);
	string getGen();
	int setPret(int Pret);
	int getPret();
	void returnData();
	int returnUID();
	int check(int s);
	int returnNrNum();
	void getDataforBilet();

	friend ostream& operator<<(ostream&, Film);
	friend istream& operator>>(istream&, Film&);
	friend ifstream& operator>>(ifstream&, Film&); //citire din fisier
	friend ofstream& operator<<(ofstream&, Film&); //scriere in fisier

};




