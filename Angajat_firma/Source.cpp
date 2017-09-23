#include<iostream>
#include<fstream>
using namespace std;

ifstream fisIn("date.in");
ofstream fisOut("date.out"); //globale

class Angajat {
private:
	const int marca;
	char* nume;
	char functie[20];
	double salariu;
public:
	Angajat():marca(0) {
		this->nume = NULL;
		strcpy(this->functie, "somer");
		this->salariu = 0;
	}
	Angajat(int marca, char* n, char* f, double s) :marca(marca) {
		this->nume = new char[strlen(n) + 1];
		strcpy(nume, n);
		strcpy(functie, f);
		this->salariu = s;
	}

	Angajat(const Angajat &a):marca(a.marca) {
		if (a.nume != NULL) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(nume, a.nume);
		}
		else this->nume = NULL;
		strcpy(functie, a.functie);
		this->salariu = a.salariu;
	}

	Angajat operator=(Angajat &a) {
		if (a.nume != NULL) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(nume, a.nume);
		}
		else this->nume = NULL;
		strcpy(functie, a.functie);
		this->salariu = a.salariu;

		return *this;
	}
	friend istream &operator >> (istream &in, Angajat &a);
	friend ostream &operator << (ostream &out, Angajat &a) {
		if (a.nume == NULL) out << "nu avem nume";
		else {
			out << a.nume;
		}
		out << a.salariu;
		out << a.functie;
		out << a.marca;

		return out;
	}

	void setFunctia(char f[20]) {
		strcpy(functie, f);
	}

	char* getFunctie() {
		return functie;
	}

	double getSalariu() {
		return salariu;
	}

	char* getNume() {
		return nume;
	}

	bool operator!=(Angajat &a) {
		if (this->nume == NULL || a.nume == NULL)return true;
		if (strcmp(this->getNume(), a.getNume()) != 0)return true;
		return false;
	}
};

class Firma{
private:
	Angajat ** angajati;
	int nrAngajati;
	char* denumire;
	double cifraAfaceri;
public:
	Firma() {
		this->angajati = NULL;
		this->nrAngajati = 0;
		this->denumire = NULL;
		this->cifraAfaceri = 0.0;
	}

	Firma(Angajat **an, int nr, char *d, double cplm) {
		angajati = new Angajat*[nr];
		for (int i = 0;i < nr;i++) {
			angajati[i] = an[i];
		}
		denumire = new char[strlen(d)];
		strcpy(denumire, d);
		cifraAfaceri = cplm;
		nrAngajati = nr;
	}

	Firma(const Firma &f) {
		this->angajati = new Angajat*[f.nrAngajati];
		for (int i = 0;i < f.nrAngajati;i++) {
			this->angajati[i] = new Angajat(*(f.angajati[i]));
		}
		this->cifraAfaceri = f.cifraAfaceri;
		this->denumire = new char[strlen(f.denumire)];
		strcpy(this->denumire, f.denumire);
		this->nrAngajati = f.nrAngajati;
	}

	Firma operator=(Firma &f) {
		this->angajati = new Angajat*[f.nrAngajati];
		for (int i = 0;i < f.nrAngajati;i++) {
			this->angajati[i] = new Angajat(*f.angajati[i]);
		}
		this->cifraAfaceri = f.cifraAfaceri;
		this->denumire = new char[strlen(f.denumire)];
		strcpy(this->denumire, f.denumire);
		this->nrAngajati = f.nrAngajati;
		return *this;
	}

	friend ostream &operator<<(ostream &out, const Firma &f) {
		out << "Angajati:" << endl;
		for (int i = 0;i < f.nrAngajati;i++) {
			out << *f.angajati[i];
		}
		out << endl;
		out << f.nrAngajati << " " << f.denumire << " " << f.cifraAfaceri;
		return out;
	}

	Firma operator +=(Angajat &a) {
		Angajat **aux;
		aux = new Angajat *[this->nrAngajati];
		for (int i = 0; i < nrAngajati;i++) {
			aux[i] = new Angajat(*this->angajati[i]);
		}
		this->angajati = new Angajat*[this->nrAngajati + 1];
		for (int i = 0;i < nrAngajati;i++) {
			this->angajati[i] = new Angajat(*aux[i]);
		}
		this->angajati[nrAngajati] = new Angajat(a);
		this->nrAngajati++;
		return (*this);
	}

	int numarProgramatori() {
		int contor = 0;
		for (int i = 0; i < nrAngajati;i++) {
			
			if (strcmp("programator", angajati[i]->getFunctie()) == 0)contor++;
		}
		return contor;
	}

	bool operator>(Firma &f) {
		if (this->numarProgramatori() > f.numarProgramatori())return true;
		return false;
	}

	bool operator<(Firma &f) {
		if (this->numarProgramatori() < f.numarProgramatori())return true;
		return false;
	}

	bool operator==(Firma &f) {
		if (this->numarProgramatori() == f.numarProgramatori())return true;
		return false;
	}

	 operator float() {
		 double sum = 0.0;
		 for (int i = 0;i < nrAngajati;i++) {
			 sum += angajati[i]->getSalariu();
		 }
		 return (float)(sum / nrAngajati);
	}

	 Firma operator-=(Angajat &a) {
		 Angajat **aux = new Angajat*[nrAngajati];
		 for (int i = 0;i < nrAngajati;i++) {
			 aux[i] = new Angajat(*this->angajati[i]);
		 }
		 this->angajati = new Angajat*[nrAngajati - 1];
		 int j = 0;
		 for (int i = 0;i < nrAngajati;i++) {
			 if (*aux[i]!=a) {
				 this->angajati[j] = new Angajat(*aux[i]);
				 j++;
			 }
		 }
		 nrAngajati--;
		 return(*this);
	 }

	 friend istream &operator>>(istream &in, Firma &f) {
		 in >> f.nrAngajati;
		 f.angajati = new Angajat*[f.nrAngajati];
		 for (int i = 0;i < f.nrAngajati;i++) {
			 Angajat abc;
			 in >> abc;
			 f.angajati[i] = new Angajat(abc);
		 }
		 char aux[50];
		 in >> aux;
		 f.denumire = new char[strlen(aux)];
		 strcpy(f.denumire, aux);
		 in >> f.cifraAfaceri;
		 return in;
	 }
};

istream &operator >> (istream &in, Angajat &a) {
	char aux[50];
	in.getline(aux, 50);
	a.nume = new char[strlen(aux)];
	strcpy(a.nume, aux);
	in.getline(a.functie, 20);
	in >> a.salariu;

	return in;

}



void main() {
	Angajat a1;
	Angajat a2(1234, "Gigel", "programator", 1500);
	Angajat a3 = a1; 
	Angajat a4;
//	cin >> a4;
	a4.setFunctia("consultant");
	a1 = a4;
	cout << a1 << a2 << a3 << a4;

	Angajat *vect[4] = { new Angajat(a1), new Angajat(a2),  new Angajat(a3), new Angajat(a4) };
	Firma f1;
	Firma f2(vect, 4, "sc firma mea", 1200);
	Firma f3 = f2;
	f1 = f3;
	cout << f1 << f2 << f3;

	Angajat a5(4567, "Marin Georgescu", "contabil", 800);
	f1 += a5;
	cout << "nr programatori in firma f1:" << f1.numarProgramatori();

	if (f1 > f3)cout << "firma f1 are mai multi programatori ca f3" << endl;
	else if (f1 < f3)cout << "firma f1 are mai putini programaori" << endl;
	else if (f1 == f3) cout << "acelasi nr de programatori" << endl;

	cout <<"salariul mediu"<< (float)f2;

	f3 -= a2;
	cout << f3;

	fisOut << f2;
	fisIn >> f3;
	cout << f3;
}


