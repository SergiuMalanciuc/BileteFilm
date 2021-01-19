using namespace std;


class Bilet {

private:

	static int ID;
	string numeFilm;
	int* locuri;
	int nrLocuri;
	char* sala;
	string numeClient;
	int pret;
	const int uID;

public:

	Bilet();
	Bilet(string numeFilm, int* locuri, int nrLocuri, const char* sala, string numeClient, int pret);
	Bilet(const Bilet& s);
	~Bilet();

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
	
	void serializareBilet(ofstream& f);
	void deserializareBilet(ifstream& f);

	string setNumeFilm(string nume);
	string getNumeFilm();
	string setNumeClient(string numeClient);
	string getNumeClient();
	int* setLocuri(int* locuri, int nrLocuri);
	int* getLocuri();
	int getNrLocuri();
	char* setSala(const char* sala);
	char* getSala();
	int setPret(int pret);
	int getPret();
	int returnUID();
	void returnData();
	int check(int s);

	friend ostream& operator<<(ostream&, Bilet);
	friend istream& operator>>(istream&, Bilet&);

};









