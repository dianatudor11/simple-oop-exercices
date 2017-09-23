#include <iostream>
#include <fstream>	
#include <map>
using namespace std;

class BonDeMasa {
private:
	int id;
	float valoare_unitara;
public:
	char* emitent;

	BonDeMasa() {
		this->emitent = NULL;
		this->id = 0;
		this->valoare_unitara = 0;
	}
	BonDeMasa(int id, char* nume, float valoare) {
		this->id = id;
		this->emitent = new char[strlen(nume) + 1];
		strcpy(this->emitent, nume);
		this->valoare_unitara = valoare;
	}
	BonDeMasa(const BonDeMasa &b) {
		this->id = b.id;
		this->emitent = new char[strlen(b.emitent) + 1];
		strcpy(this->emitent, b.emitent);
		this->valoare_unitara = b.valoare_unitara;
	}
	~BonDeMasa() {
		if (this->emitent != NULL)
			delete[] this->emitent;
	}
	void operator = (const BonDeMasa &b) {
		if (this->emitent != NULL)
			delete[] this->emitent;
		this->id = b.id;
		this->emitent = new char[strlen(b.emitent) + 1];
		strcpy(this->emitent, b.emitent);
		this->valoare_unitara = b.valoare_unitara;
	}

	friend void operator >>(istream& in, BonDeMasa& b);

	void Afiseaza(ofstream& file) {
		if (this->emitent != NULL) {
			file << this->id << endl;
			file << this->emitent << endl;
			file << this->valoare_unitara << endl;
		}
		else
			file << "Bon necompletat" << endl;
	}

	friend ifstream& operator >> (ifstream& fin, BonDeMasa &b) {
		int id;
		char buffer[50];
		float valoare;
		fin >> id;
		fin >> buffer;
		fin >> valoare;
		b.id = id;
		if (b.emitent != NULL)
			delete[] b.emitent;
		b.emitent = new char[strlen(buffer) + 1];
		strcpy(b.emitent, buffer);
		b.valoare_unitara = valoare;
		return fin;
	}

	virtual void AfiseazaTip() {
		cout << "Bon de masa" << endl;
	}
};

void operator >>(istream& in, BonDeMasa& b) {
	int new_id;
	char new_nume[50];
	float new_numar;
	cout << "Introduceti id-ul:" << endl;
	in >> new_id;
	cout << "Introduceti numele emitentului:" << endl;
	in >> new_nume;
	cout << "Introduceti valoare bonului:";
	in >> new_numar;
	b.id = new_id;
	b.emitent = new char[strlen(new_nume) + 1];
	strcpy(b.emitent, new_nume);
	b.valoare_unitara = new_numar;
}

class Angajat {
	static int marca;
	int numar_de_bonuri;
public:
	char nume[50];
	BonDeMasa* bonuri;

	Angajat() {
		this->numar_de_bonuri = 0;
		strcpy(this->nume, "Anonim");
		this->bonuri = NULL;
		this->marca = marca++;
	}

	Angajat(char* nume, int numar) {
		strcpy(this->nume, nume);
		this->numar_de_bonuri = numar;
		this->bonuri = new BonDeMasa[numar];
		this->marca = marca++;
	}

	Angajat(const Angajat &a) {

		strcpy(this->nume, a.nume);
		this->numar_de_bonuri = a.numar_de_bonuri;
		this->bonuri = new BonDeMasa[a.numar_de_bonuri];

	}

	void operator = (const Angajat &a) {
		if (this->nume != NULL)
			delete this->nume;
		if (this->bonuri != NULL)
			delete[] this->bonuri;
		strcpy(this->nume, a.nume);
		this->numar_de_bonuri = a.numar_de_bonuri;
		this->bonuri = new BonDeMasa[a.numar_de_bonuri];
		for (int i = 0; i < this->numar_de_bonuri; i++)
			this->bonuri[i] = a.bonuri[i];

	}

	int GetMarca() {
		return this->marca;
	}

	friend ostream& operator<<(ostream& out, Angajat &a);

	Angajat& operator *=(BonDeMasa &b) {

		if (this->numar_de_bonuri == 0) {
			this->numar_de_bonuri++;
			this->bonuri = new BonDeMasa[this->numar_de_bonuri];
			this->bonuri[this->numar_de_bonuri - 1] = b;
		}
		else {
			this->bonuri[0] = b;
		}
		return *this;
	}

	char* operator !() {
		if (this->numar_de_bonuri == 0) {
			return "Acest angajat nu primeste bonuri";
		}
		else {
			return "Acest angajat primeste bonuri";
		}
	}

	bool operator <(Angajat &a) {
		if (this->GetMarca() < a.GetMarca())
			return true;
		else
			return false;
	}

	void Afiseaza() {
		ofstream file("text.txt");
		file << this->nume << endl;
		file << this->marca << endl;
		file << this->numar_de_bonuri << endl;
		for (int i = 0; i < this->numar_de_bonuri; i++)
			this->bonuri[i].Afiseaza(file);
	}
};
int Angajat::marca = 0;

ostream& operator<<(ostream& out, Angajat &a) {
	out << "Angajatul cu numele " << a.nume << " marca " << a.GetMarca() << " are " << a.numar_de_bonuri << " bonuri" << endl;
	return out;
}

class CardDeMasa : public BonDeMasa {
	int pin;
public:
	CardDeMasa() :BonDeMasa() {
		this->pin = 0;
	}

	CardDeMasa(int new_pin) {
		this->pin = new_pin;
	}

	CardDeMasa(int id, char* emitent, float valoarea, int new_pin) :BonDeMasa(id, emitent, valoarea) {
		this->pin = new_pin;
	}

	void operator = (const CardDeMasa &c) {
		this->pin = c.pin;
	}
	void AfiseazaTip() {
		cout << "Card de masa" << endl;
	}
};

void main() {
	BonDeMasa b1(1, "GustoPass", 9.35), b2, b3;
	Angajat a1("Ion Ionescu", 22), a2, a3;
	cout << a1;
	/*cin >> b2;*/
	a1 *= b1;

	cout << (!a1);
	if (a1 < a2)
		cout << "Angajatul " << a1 << "are marca mai mica decat" << a2;
	/*else
	cout << "Angajatul" << a2 << "are marca mai mica decat " << a1;*/
	a1.Afiseaza();

	ifstream date("date.txt");
	date >> b3;

	BonDeMasa *pb = new BonDeMasa();
	CardDeMasa *pc = new CardDeMasa();
	pb->AfiseazaTip();
	pc->AfiseazaTip();
	pb = pc;
	pb->AfiseazaTip();

	map<int, Angajat> angajati;
	angajati.insert(pair<int, Angajat>(a1.GetMarca(), a1));
	angajati.insert(pair<int, Angajat>(a2.GetMarca(), a2));
	map<int, Angajat>::iterator it;
	for (it = angajati.begin(); it != angajati.end(); it++) {
		if (it->first == 3)
			cout << "Angajat gasit";
	}
}