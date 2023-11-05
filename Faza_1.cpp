#include <iostream>
using namespace std;

//Domeniu: MediCina (Moldovan Catrinel)

class Doctor {
public:
    string nume;
    char* specializare;
    const int anNastere;
    float salariu;
    static int salariuMinim;


    Doctor() : anNastere(1975) {         //constructor fara parametrii
        this->nume = "Constantinescu Florin";
        this->specializare = new char[strlen("Dermatologie" + 1)];
        strcpy_s(this->specializare, strlen("Dermatologie") + 1, "Dermatologie");
        this->salariu = 6500;
    }

    Doctor(string nume, const char* specializare, float salariu, const int an) : anNastere(an) {      //constructor cu toti parametrii
        this->nume = nume;
        this->specializare = new char[strlen(specializare + 1)];
        strcpy_s(this->specializare, strlen(specializare) + 1, specializare);
        this->salariu = salariu;
    }

    Doctor(string nume, const int an) : anNastere(an) {
        this->nume = nume; 
        this->specializare = new char[strlen("Alergologie" + 1)];
        strcpy_s(this->specializare, strlen("Alergologie") + 1, "Alergologie");
        this->salariu = 5000; 
    }


    void afisare() {
        cout << this->nume << " " << this->specializare << " " << this->anNastere << " " << this->salariu << " " << this->salariuMinim << endl;
    }


    ~Doctor() {
        if (this->specializare != NULL) {
            delete[]this->specializare;
            this->specializare = NULL; 
        }
    }

};
int Doctor::salariuMinim = 2080;


class Spital {
public: 
    string nume; 
    char* oras; 
    string domeniu; 
    const int anInfiintare;
    int nrAngajati;
    static int suprafataMinimaSalon;

    Spital() : anInfiintare(2001) {
        this->nume = "Sanador"; 
        this->oras = new char[strlen("Bucuresti" + 1)]; 
        strcpy_s(this->oras, strlen("Bucuresti") + 1, "Bucuresti"); 
        this->domeniu = "Privat"; 
        this->nrAngajati = 100;
    }

    Spital(string nume, const char* oras, string domeniu, const int an, int nr) : anInfiintare(an) {
        this->nume = nume; 
        this->oras = new char[strlen(oras + 1)]; 
        strcpy_s(this->oras, strlen(oras) + 1, oras); 
        this->domeniu = domeniu; 
        this->nrAngajati = nr; 
    }

    Spital(string nume, const int an, int nr) :anInfiintare(an) {
        this->nume = nume; 
        this->oras = new char[strlen("Targu Mures" + 1)]; 
        strcpy_s(this->oras, strlen("Targu Mures") + 1, "Targu Mures"); 
        this->domeniu = "Privat"; 
        this->nrAngajati = nr;
    }


    void afisare() {
        cout << this->nume << " " << this->oras << " " << this->domeniu << " " << this->anInfiintare << " " << this->nrAngajati<< " " << this->suprafataMinimaSalon << endl;
    }

    ~Spital() {
        if (this->oras != NULL) {
            delete[]this->oras;
            this->oras = NULL;
        }
    }

};
int Spital::suprafataMinimaSalon = 20;


class Medicament {
public: 
    string nume; 
    const string substantaActiva; 
    char* tip; 
    int gramaj;
    static int TVA;

    Medicament() : substantaActiva("Ibuprofen") {
        this->nume = "Nurofen"; 
        this->tip = new char[strlen("OTC" + 1)]; 
        strcpy_s(this->tip, strlen("OTC") + 1, "OTC"); 
        this->gramaj = 200;
    }

    Medicament(string nume, const string substanta, const char* tip, int gramaj) : substantaActiva(substanta) {
        this->nume = nume; 
        this->tip = new char[strlen(tip + 1)]; 
        strcpy_s(this->tip, strlen(tip) + 1, tip); 
        this->gramaj = gramaj;
    }

    Medicament(string nume, int gramaj) :substantaActiva("Paracetamol") {
        this->nume = nume; 
        this->tip = new char[strlen("OTC" + 1)]; 
        strcpy_s(this->tip, strlen("OTC") + 1, "OTC");
        this->gramaj = gramaj;
    }


    void afisare() {
        cout << this->nume << " " << this->substantaActiva << " " << this->tip << " " << this->gramaj << "mg " << this->TVA << "%" << endl;
    }

    ~Medicament() {
        if (this->tip != NULL) {
            delete[]this->tip;
            this->tip = NULL;
        }
    }

};
int Medicament::TVA = 9;



void main() {
    Doctor d1;
    d1.afisare();

    Doctor d2("Popescu Maria", "Urologie", 6000, 1963);
    d2.afisare();

    Doctor d3("Ion Dinu", 1970);
    d3.afisare();

    cout << endl; 

    Spital s1; 
    s1.afisare();

    Spital s2("Floreasca", "Bucuresti", "Public", 1949, 200);
    s2.afisare();

    Spital s3("MedLife", 2003, 60);
    s3.afisare();

    cout << endl;

    Medicament m1;
    m1.afisare();

    Medicament m2("Tramadol", "Clorhidrat de tramadol", "RX", 50);
    m2.afisare();

    Medicament m3("Theraflu", 650);
    m3.afisare();
}
