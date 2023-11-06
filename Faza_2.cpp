#include <iostream>
using namespace std;

//Domeniu: MediCina (Moldovan Catrinel)

class Spital; //declar din nou clasa spital *inainte* de clasa doctor pt ca functia globala pe care o declar friend in clasa doctor sa poata recunoaste obiecte de tipul spital (eroarea: "syntax error : identifier 'Spital'")

class Doctor {
private:
    string nume;
    char* specializare;
    const int anNastere;
    float salariu;
    static int salariuMinim;


public:
    //constructori :
    Doctor() : anNastere(1975) {         //constructor fara parametrii
        this->nume = "Constantinescu Florin";
        this->specializare = new char[strlen("Dermatologie") + 1];
        strcpy_s(this->specializare, strlen("Dermatologie") + 1, "Dermatologie");
        this->salariu = 6500;
    }

    Doctor(string nume, const char* specializare, float salariu, const int an) : anNastere(an) {      //constructor cu toti parametrii
        this->nume = nume;
        this->specializare = new char[strlen(specializare) + 1];
        strcpy_s(this->specializare, strlen(specializare) + 1, specializare);
        this->salariu = salariu;
    }

    Doctor(string nume, const int an) : anNastere(an) {
        this->nume = nume;
        this->specializare = new char[strlen("Alergologie") + 1];
        strcpy_s(this->specializare, strlen("Alergologie") + 1, "Alergologie");
        this->salariu = 5000;
    }

    Doctor(const Doctor& d) : anNastere(d.anNastere) {     //constructor de copiere
        this->nume = d.nume; 
        this->specializare = new char[strlen(d.specializare) + 1]; 
        strcpy_s(this->specializare, strlen(d.specializare) + 1, d.specializare);
        this->salariu = d.salariu;
    }


    //getteri :
    string getNume() {
        return this->nume;
    }

    const int getAnNastere() {
        return this->anNastere;
    }

    float getSalariu() {
        return this->salariu;
    }

    static int getSalariuMinim() {
        return salariuMinim;
    }

    char* getSpecializare() {
        return this->specializare;
    }
    

    //setteri :
    void setNume(string numeNou) {
        if (numeNou.length() > 3) {
            this->nume = numeNou;
        }
    }

    void setSalariu(float salariuNou) {
        if (salariuNou != NULL && salariuNou>=salariuMinim) {
            this->salariu = salariuNou; 
        }
    }

    void setSpecializare(const char* specializareNoua) {
        if (this->specializare != NULL) {
            delete[]this->specializare;
        }
        this->specializare = new char[strlen(specializareNoua) + 1]; 
        strcpy_s(this->specializare, strlen(specializareNoua) + 1, specializareNoua);
    }

    static void setSalariuMinim(int salariuMinimNou) {
        salariuMinim = salariuMinimNou;
    }


    //metoda afisare : 
    void afisare() {
        cout << endl << "Nume: " << this->nume << endl;
        cout << "Anul nasterii: " << this->anNastere << endl;
        cout << "Specializare: " << this->specializare << endl;
        cout << "Salariu: " << this->salariu << endl;
        cout << "Salariu minim: " << this->salariuMinim << endl;
    }


    //destructor : 
    ~Doctor() {
        if (this->specializare != NULL) {
            delete[]this->specializare;
            this->specializare = NULL;
        }
    }

    //declar prietena functia globala
    friend void marireSalariuSiNrAngajati(Doctor& d, float a, Spital& s, int b);

};
int Doctor::salariuMinim = 2080;    //initializare atribut static


class Spital {
private:
    string nume;
    char* oras;
    string domeniu;
    const int anInfiintare;
    int nrAngajati;
    static int suprafataMinimaSalon;


public:
    //constructori : 
    Spital() : anInfiintare(2001) {      //constructor fara parametrii 
        this->nume = "Sanador";
        this->oras = new char[strlen("Bucuresti") + 1];
        strcpy_s(this->oras, strlen("Bucuresti") + 1, "Bucuresti");
        this->domeniu = "Privat";
        this->nrAngajati = 100;
    }

    Spital(string nume, const char* oras, string domeniu, const int an, int nr) : anInfiintare(an) {   //constructor cu toti parametrii 
        this->nume = nume;
        this->oras = new char[strlen(oras) + 1];
        strcpy_s(this->oras, strlen(oras) + 1, oras);
        this->domeniu = domeniu;
        this->nrAngajati = nr;
    }

    Spital(string nume, const int an, int nr) :anInfiintare(an) {   
        this->nume = nume;
        this->oras = new char[strlen("Targu Mures") + 1];
        strcpy_s(this->oras, strlen("Targu Mures") + 1, "Targu Mures");
        this->domeniu = "Privat";
        this->nrAngajati = nr;
    }

    Spital(const Spital& s) : anInfiintare(s.anInfiintare) {    //constructor de copiere
        this->nume = s.nume; 
        this->oras = new char[strlen(s.oras) + 1]; 
        strcpy_s(this->oras, strlen(s.oras) + 1, s.oras); 
        this->domeniu = s.domeniu; 
        this->nrAngajati = s.nrAngajati; 
    }


    //getteri : 
    string getNume() {
        return this->nume;
    }

    char* getOras() {
        return this->oras;
    }

    string getDomeniu() {
        return this->domeniu;
    }

    const int getAnInfiintare() {
        return this->anInfiintare;
    }

    int getNrAngajati() {
        return this->nrAngajati;
    }

    static int getSuprafataMinimaSalon() {
        return suprafataMinimaSalon;
    }


    //setteri : 
    void setNume(string numeNou) {
        if (numeNou.length() > 3) {
            this->nume = numeNou;
        }
    }

    void setOras(const char* oras) {
        if (this->oras != NULL) {
            delete[]this->oras;
        }
        this->oras = new char[strlen(oras) + 1];
        strcpy_s(this->oras, strlen(oras) + 1, oras);
    }

    void setDomeniu(string domeniu) {
        if (domeniu.length() > 3) {
            this->domeniu = domeniu;
        }
    }

    void setNrAngajati(int angajati) {
        if (angajati != NULL) {
            this->nrAngajati = angajati;
        }
    }

    static void setSuprafataMinimaSalon(int suprafata) {
        suprafataMinimaSalon = suprafata;
    }
    

    //metoda afisare : 
    void afisare() {
        cout << endl << "Nume: " << this->nume << endl;
        cout << "Oras: " << this->oras << endl;
        cout << "Domeniu: " << this->domeniu << endl;
        cout << "An infiintare: " << this->anInfiintare << endl;
        cout << "Nr angajati: " << this->nrAngajati << endl;
        cout << "Suprafata minima salon: " << this->suprafataMinimaSalon << endl;
    }


    //destructor : 
    ~Spital() {
        if (this->oras != NULL) {
            delete[]this->oras;
            this->oras = NULL;
        }
    }

    //declar prietena functia globala
    friend void marireSalariuSiNrAngajati(Doctor& d, float a, Spital& s, int b);

};
int Spital::suprafataMinimaSalon = 20;   //initializare atribut static


class Medicament {
private:
    string nume;
    const string substantaActiva;
    char* tip;
    int gramaj;
    static int TVA;


public:
    Medicament() : substantaActiva("Ibuprofen") {     //constructor fara parametrii 
        this->nume = "Nurofen";
        this->tip = new char[strlen("OTC") + 1];
        strcpy_s(this->tip, strlen("OTC") + 1, "OTC");
        this->gramaj = 200;
    }

    Medicament(string nume, const string substanta, const char* tip, int gramaj) : substantaActiva(substanta) {   //constructor cu toti parametrii 
        this->nume = nume;
        this->tip = new char[strlen(tip) + 1];
        strcpy_s(this->tip, strlen(tip) + 1, tip);
        this->gramaj = gramaj;
    }

    Medicament(string nume, int gramaj) :substantaActiva("Paracetamol") {
        this->nume = nume;
        this->tip = new char[strlen("OTC") + 1];
        strcpy_s(this->tip, strlen("OTC") + 1, "OTC");
        this->gramaj = gramaj;
    }

    Medicament(const Medicament& m) : substantaActiva(m.substantaActiva) {     //constructor de copiere
        this->nume = m.nume; 
        this->tip = new char[strlen(m.tip) + 1]; 
        strcpy_s(this->tip, strlen(m.tip) + 1, m.tip); 
        this->gramaj = m.gramaj; 
    }


    //getteri :
    string getNume() {
        return this->nume;
    }

    const string getSubstantaActiva() {
        return this->substantaActiva;
    }

    char* getTip() {
        return this->tip;
    }

    int getGramaj() {
        return this->gramaj;
    }

    static int getTVA() {
        return TVA;
    }


    //setteri : 
    void setNume(string nume) {
        if (nume.length() > 3) {
            this->nume = nume;
        }
    }

    void setTip(const char* tip) {
        if (this->tip != NULL) {
            delete[]this->tip;
        }
        this->tip = new char[strlen(tip) + 1];
        strcpy_s(this->tip, strlen(tip) + 1, tip);
    }

    void setGramaj(int gramaj) {
        if (gramaj != NULL) {
            this->gramaj = gramaj;
        }
    }

    static void setTVA(int TVAnou) {
        TVA = TVAnou;
    }


    //functie afisare : 
    void afisare() {
        cout << endl << "Nume: " << this->nume << endl;
        cout << "Substanta activa: " << this->substantaActiva << endl;
        cout << "Tip: " << this->tip << endl;
        cout << "Gramaj: " << this->gramaj << " mg" << endl;
        cout << "TVA: " << this->TVA << " %" << endl; 
    }


    //destructor : 
    ~Medicament() {
        if (this->tip != NULL) {
            delete[]this->tip;
            this->tip = NULL;
        }
    }

    //declar prietena functia globala
    friend void schimbareInMedicamentCuReteta(Medicament& m);

};
int Medicament::TVA = 9;   //initializare atribut static 


//functii globale 
void marireSalariuSiNrAngajati(Doctor& d, float a, Spital& s, int b) {
    d.salariu = d.salariu + a; 
    s.nrAngajati = s.nrAngajati + b; 
}

void schimbareInMedicamentCuReteta(Medicament& m) {
    if (m.tip != NULL) {
        delete[]m.tip;
    }
    m.tip = new char[strlen("RX") + 1]; 
    strcpy_s(m.tip, strlen("RX") + 1, "RX");
}



void main() {
    Doctor d1;
    cout << "Nume: " << d1.getNume() << endl;
    cout << "Anul nasterii: "<< d1.getAnNastere() << endl;
    cout << "Specializare: " << d1.getSpecializare() << endl;
    cout << "Salariu: " << d1.getSalariu() << endl;
    cout << "Salariu minim: " << d1.getSalariuMinim() << endl;

    d1.setNume("Micu Stefan"); 
    d1.setSalariu(3400);
    d1.setSalariuMinim(3000);
    d1.setSpecializare("Cardiologie");
    d1.afisare();

    Doctor d2("Popescu Maria", "Urologie", 6000, 1963);
    d2.afisare();

    Doctor d3("Ion Dinu", 1970);
    d3.afisare();

    Doctor d4(d3);
    d4.afisare();

    cout << endl;

    Spital s1;
    cout << "Nume: " << s1.getNume() << endl;
    cout << "Oras: " << s1.getOras() << endl;
    cout << "Domeniu: " << s1.getDomeniu() << endl;
    cout << "An infiintare: " << s1.getAnInfiintare() << endl;
    cout << "Nr angajati: " << s1.getNrAngajati() << endl;
    cout << "Suprafata minima salon: " << s1.getSuprafataMinimaSalon() << endl;

    s1.setNume("Regina Maria");
    s1.setOras("Bucuresti"); 
    s1.setDomeniu("Privat"); 
    s1.setNrAngajati(400);
    Spital::setSuprafataMinimaSalon(25);
    s1.afisare();

    Spital s2("Floreasca", "Bucuresti", "Public", 1949, 200);
    s2.afisare();

    Spital s3("MedLife", 2003, 60);
    s3.afisare();

    Spital s4(s3); 
    s4.afisare();

    cout << endl;

    Medicament m1;
    cout << "Nume: " << m1.getNume() << endl;
    cout << "Substanta activa: " << m1.getSubstantaActiva() << endl;
    cout << "Tip: " << m1.getTip() << endl;
    cout << "Gramaj: " << m1.getGramaj() << " mg" << endl;
    cout << "TVA: " << m1.getTVA() << " %" << endl;

    m1.setNume("Advil"); 
    m1.setTip("RX");
    m1.setGramaj(300);
    m1.setTVA(10);
    m1.afisare();

    Medicament m2("Tramadol", "Clorhidrat de tramadol", "RX", 50);
    m2.afisare();

    Medicament m3("Theraflu", 650);
    m3.afisare();

    Medicament m4(m3); 
    m4.afisare();

    cout << endl;

    marireSalariuSiNrAngajati(d1, 800, s2, 1);
    cout << d1.getSalariu() << endl;
    cout << s2.getNrAngajati() << endl; 

    cout << endl; 

    schimbareInMedicamentCuReteta(m3);
    cout << m3.getTip() << endl; 
}