#include<iostream>
using namespace std;

char* AlocirajIKopiraj(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, tekst);
	return novi;
}

char* GetRandomString(int duzina) {                             //Vraca random string odredjene duzine kojeg sacinjavaju velika i mala slova
	int velicina = duzina + 1;
	char* randomString = new char[velicina];
	for (size_t i = 0; i < velicina; i++) {
		int random_ascii = rand() % 26 + 65;
		char slovo = (char)random_ascii;
		bool pretvoriUMalo = (bool)(rand() % 2);
		if (pretvoriUMalo)
			slovo = tolower(slovo);
		randomString[i] = slovo;
	}
	randomString[velicina - 1] = '\0';
	return randomString;
}
class Sjediste {
private:
	char* _sjedisteId;   // Koristiti GetRandomString funkciju prilikom inicijalizacije [neka je duzina stringa 10]
	char _red;          //A-Z
	int _kolona;       //1,2,3,..., 100
public:
	
	Sjediste() {
		_sjedisteId = GetRandomString(10);
		_red = ' ';
		_kolona = 0;
	}
	
	
	Sjediste(char red, int kolona) {
		_sjedisteId = GetRandomString(10);
		_red = red;
		_kolona = kolona;
	}
	
	char GetRed() const { return _red; }
	int GetKolona() const { return _kolona; }
	
	void SetRed(char red) {
		_red = red;
	}
	void SetKolona(int kolona) {
		_kolona = kolona;
	}

	                                                          //Ispis sjedista u formatu: "[A-13]"
	void Ispis() {
		cout << "[" << _red << "-" << _kolona << "]";
	}
	
	~Sjediste() {
		delete[] _sjedisteId;
		_sjedisteId = nullptr;
	}
};

class Dvorana
{
private:
	char* _naziv;
	int _brojRedova;            //max.26 [A-Z]
	int _brojKolona;
	Sjediste** _sjedista;     
public:
	
	Dvorana() {
		_naziv = nullptr;
		_brojRedova = 0;
		_brojKolona = 0;
		_sjedista = nullptr;
	}

	//Podesiti vrijednosti atributa objekata matrice na sljedeci nacin -->
	//Polje [0][0] => _red : A, _kolona : 1
	//Polje [0][1] => _red : A, _kolona : 2
	//Polje [0][2] => _red : A, _kolona : 3
	//...
	//Polje [1][0] => _red : B, _kolona : 1
	//itd.
	Dvorana(const char* naziv, int brojRedova, int brojKolona) {
		_naziv = AlocirajIKopiraj(naziv);
		_brojRedova = brojRedova;
		_brojKolona = brojKolona;
		_sjedista = new Sjediste * [_brojRedova];            //Alokacija niza pokazivaca
		for (size_t i = 0; i < _brojRedova; i++)
			_sjedista[i] = new Sjediste[_brojKolona];        //Alokacija niza objekata za i-ti pokazivac u nizu
		int asciiA = 65;
		                                                     //Podesavanje vrijednosti atributa objekata
		for (size_t i = 0; i < _brojRedova; i++) {
			for (size_t j = 0; j < _brojKolona; j++) {
				_sjedista[i][j].SetRed((char)(asciiA + i));
				_sjedista[i][j].SetKolona(j + 1);
			}
		}
	}


	void SetNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}
	const char* GetNaziv() const { return _naziv; }
	int GetBrojRedova() const { return _brojRedova; }
	int GetBrojKolona() const { return _brojKolona; }

	
	//Dealokacija alocirane matrice sjedista, te zatim uraditi ponovnu alokaciju na osnovu novih dimenzija
	void SetSjedista(int brojRedova, int brojKolona) {
		for (size_t i = 0; i < _brojRedova; i++) {
			delete[] _sjedista[i];                       //Dealociranje niza objekata tipa Sjediste
			_sjedista[i] = nullptr;
		}
		delete[] _sjedista;                             //Dealociranje niza pokazivaca
		_sjedista = nullptr;
		                                                //Podesavanje atributa na nove vrijednosti
		_brojRedova = brojRedova;
		_brojKolona = brojKolona;
		
		_sjedista = new Sjediste * [_brojRedova];         //Alokacija niza pokazivaca
		for (size_t i = 0; i < _brojRedova; i++)
			_sjedista[i] = new Sjediste[_brojKolona];     //Alokacija niza objekata 
		int asciiA = 65;
		for (size_t i = 0; i < _brojRedova; i++) {
			for (size_t j = 0; j < _brojKolona; j++) {
				_sjedista[i][j].SetRed((char)(asciiA + i));
				_sjedista[i][j].SetKolona(j + 1);
			}
		}
	}

	Sjediste* GetSjediste(char red, int kolona) {
		for (size_t i = 0; i < _brojRedova; i++)
			for (size_t j = 0; j < _brojKolona; j++)
				if (_sjedista[i][j].GetRed() == red && _sjedista[i][j].GetKolona() == kolona)
					return &_sjedista[i][j];
		return nullptr;
	}


	//Uraditi ispis na sljedeci nacin --->
	//Dvorana: Dvorana 7 Extreme
	//Redova: 11
	//Kolona: 20
	// -----------------------------
	// [A-1] [A-2] [A-3] .... [A-20]
	// [B-1] [B-2] [B-3] .... [B-20]
	// .
	// .
	// .
	// [K-1] [K-2] [K-3] .... [K-20]
	// -----------------------------
	void Ispis() {
		cout << "Dvorana: " << _naziv << endl;
		cout << "Redova: " << _brojRedova << endl;
		cout << "Kolona: " << _brojKolona << endl;
		for (size_t i = 0; i < _brojRedova; i++) {
			for (size_t j = 0; j < _brojKolona; j++)
			{
				_sjedista[i][j].Ispis();
				cout << " ";
			}
			cout << endl;
		}
	}

	
	~Dvorana() {
		delete[]_naziv;
		_naziv = nullptr;
		for (size_t i = 0; i < _brojRedova; i++) {
			delete[] _sjedista[i];            //Dealociranje niza objekata tipa Sjediste
			_sjedista[i] = nullptr;
		}
		delete[] _sjedista;                  //Dealociranje niza pokazivaca
		_sjedista = nullptr;
	}
};
void main() {
	cout << "Testiranje klase 'Sjediste'" << endl;
	Sjediste s1, s2('C', 4);
	Sjediste s3(s2.GetRed(), s2.GetKolona());
	s3.Ispis();
	cout << endl;
	s3.SetRed('M');
	s3.SetKolona(16);
	s3.Ispis();
	cout << endl;
	cout << "Done." << "\n\n";

	cout << "Testiranje klase 'Dvorana'" << endl;
	Dvorana extreme3("Dvorana Extreme 3", 7, 7);
	extreme3.Ispis();
	cout << endl;
	Dvorana realExtreme3(extreme3.GetNaziv(), extreme3.GetBrojRedova(), extreme3.GetBrojKolona());
	realExtreme3.SetNaziv("Dvorana Real Extreme 3");
	realExtreme3.SetSjedista(10, 10);
	realExtreme3.Ispis();
	cout << endl;
	Dvorana real3D;
	real3D.SetNaziv("Dvorana Real 3D");
	real3D.SetSjedista(15, 8);
	real3D.Ispis();
	cout << endl;

	Sjediste* pok = real3D.GetSjediste('B', 2);
	cout << "Trazimo sjediste B-2 U dvorani Real 3D." << endl;
	if (pok != nullptr) {
		pok->Ispis();
		cout << endl << "Nadjeno." << endl;
	}
	else {
		cout << "Nije nadjeno." << endl;
	}
	pok = real3D.GetSjediste('X', 3);
	cout << "Trazimo sjediste X-3 u dvorani Real 3D." << endl;
	if (pok != nullptr) {
		pok->Ispis();
		cout << endl << "Nadjeno." << endl;
	}
	else {
		cout << "Nije nadjeno." << "\n\n";
	}
	cout << "Dealokacija dvorana..." << endl;
}
