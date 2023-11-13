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
        if (salariuNou != NULL && salariuNou >= salariuMinim) {
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


    //operatori :
    // = 
    Doctor& operator=(const Doctor& d) {
        if (this != &d) {
            this->nume = d.nume;
            if (this->specializare != NULL) {
                delete[]this->specializare;
            }
            this->specializare = new char[strlen(d.specializare) + 1];
            strcpy_s(this->specializare, strlen(d.specializare) + 1, d.specializare);
            this->salariu = d.salariu;
        }
        return *this;
    }

    //operator afisare
    friend ostream& operator<<(ostream& consola, Doctor& d) {     //nu e metoda !! (chiar daca am facut implementarea 'inline' in interiorul clasei); e functie prietena, deci nu o pot apela in main prin obiect (din cauza asta nu vedea operatorul) 
        consola << endl << "Nume: " << d.nume << endl;
        consola << "Anul nasterii: " << d.anNastere << endl;
        consola << "Specializare: " << d.specializare << endl;
        consola << "Salariu: " << d.salariu << endl;
        consola << "Salariu minim: " << d.salariuMinim << endl;

        return consola;
    }

    //operator citire
    friend istream& operator>>(istream& input, Doctor& d) {
        cout << endl << "Nume: ";
        input >> d.nume;
        cout << "Specializare: ";
        if (d.specializare != NULL) {
            delete[]d.specializare;
        }
        char temp[100];
        //char* temp = new char[51];
        input >> temp;
        d.specializare = new char[strlen(temp) + 1];
        strcpy_s(d.specializare, strlen(temp) + 1, temp);
        //delete[]temp;
        cout << "Salariu: ";
        input >> d.salariu;

        return input;
    }

    //post ++ 
    Doctor operator++(int) {
        Doctor temp = *this;
        this->salariu += 1000;

        return *this;
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


    //operatori : 
    // = 
    Spital& operator=(const Spital& s) {
        if (this != &s) {       //verific daca obiectele sunt diferite (comparand adresele)
            this->nume = s.nume;
            if (this->oras != NULL) {
                delete[]this->oras;
            }
            this->oras = new char[strlen(s.oras) + 1];
            strcpy_s(this->oras, strlen(s.oras) + 1, s.oras);
            this->domeniu = s.domeniu;
            this->nrAngajati = s.nrAngajati;
        }
        return *this;
    }

    // <
    bool operator<(Spital& s) {
        return this->nrAngajati < s.nrAngajati;
    }

    // pre --
    Spital operator--() {     //pre decrementare 
        this->nrAngajati = this->nrAngajati - 10;
        return *this;
    }

    //post --
    Spital operator--(int) {  //post decrementare 
        Spital temp = *this;
        this->nrAngajati = this->nrAngajati - 10;
        return temp;
    }

    //operator citire >>
    friend istream& operator>>(istream& input, Spital& s) {
        cout << endl << "Nume: ";
        input >> s.nume;
        cout << "Oras: ";
        if (s.oras != NULL) {
            delete[]s.oras;
        }
        char temp[50];
        input >> temp;
        s.oras = new char[strlen(temp) + 1];
        strcpy_s(s.oras, strlen(temp) + 1, temp);
        cout << "Domeniu: ";
        input >> s.domeniu;
        cout << "Numar angajati: ";
        input >> s.nrAngajati;

        return input;
    }

    //operator afisare <<
    friend ostream& operator<<(ostream& consola, const Spital& s) {
        consola << endl << "Nume: " << s.nume << endl;
        consola << "Oras: " << s.oras << endl;
        consola << "Domeniu: " << s.domeniu << endl;
        consola << "An infiintare: " << s.anInfiintare << endl;
        consola << "Nr angajati: " << s.nrAngajati << endl;
        consola << "Suprafata minima salon: " << s.suprafataMinimaSalon << endl;

        return consola;
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


    //operatori : 
    // = 
    Medicament& operator=(const Medicament& m) {
        if (this != &m) {
            this->nume = m.nume;
            if (this->tip != NULL) {
                delete[]this->tip;
            }
            this->tip = new char[strlen(m.tip) + 1];
            strcpy_s(this->tip, strlen(m.tip) + 1, m.tip);
            this->gramaj = m.gramaj;
        }
        return *this;
    }

    // !=
    bool operator!=(const Medicament& m) {
        return this->substantaActiva != m.substantaActiva;
    }

    // +=
    Medicament& operator+=(int a) {
        this->gramaj += a;
        return *this;
    }

    // ()
    double operator()(int nrPastilePachet) {
        double gramajValoareReala = this->gramaj;         //float e mai micut decat int si e posibil sa se piarda informatii la conversia din int in float => folosesc atunci double
        double gramajPastila = gramajValoareReala / nrPastilePachet;
        return gramajPastila;
    }

    //operator citire >>
    friend istream& operator>>(istream& input, Medicament& m) {
        cout << endl << "Nume: ";
        input >> m.nume;
        cout << "Tip: ";
        if (m.tip != NULL) {
            delete[]m.tip;
        }
        char temp[50];
        input >> temp;
        m.tip = new char[strlen(temp) + 1];
        strcpy_s(m.tip, strlen(temp) + 1, temp);
        cout << "Gramaj: ";
        input >> m.gramaj;

        return input;
    }

    //operator afisare <<
    friend ostream& operator<<(ostream& consola, const Medicament& m) {
        consola << endl << "Nume: " << m.nume << endl;
        consola << "Substanta activa: " << m.substantaActiva << endl;
        consola << "Tip: " << m.tip << endl;
        consola << "Gramaj: " << m.gramaj << endl;
        consola << "TVA: " << m.TVA << endl;

        return consola;
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
    Doctor *vd;      //vector alocat dinamic
    int n;
    Spital s[3];     //vector alocat static
    Medicament m[3];

    //Citire + Afisare Vector Doctori
    cout << "Introduceti numar doctori: " << endl << "n = ";
    cin >> n; 
    vd = new Doctor[n];  //alocare memorie vector

    cout << "Citire Vector Doctori :" << endl;
    for (int i = 0; i < n; i++) {
        cin >> vd[i];
    }

    cout << endl << "-------------------------" << endl; 

    cout << endl << "Afisare Vector Doctori :" << endl;
    for (int i = 0; i < n; i++) {
        cout << vd[i];
    }

    if (vd != NULL) {     //dezalocare memorie vector
        delete[]vd;
    }

    cout << endl << "-------------------------" << endl;


    //Citire + Afisare Vector Spitale
    cout << endl << "Citire Vector Spitale :" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> s[i];
    }

    cout << endl << "-------------------------" << endl;

    cout << endl << "Afisare Vector Spitale :" << endl;
    for (int i = 0; i < 3; i++) {
        cout << s[i];
    }

    cout << endl << "----------------------------" << endl;

    //Citire + Afisare Vector Medicamente
    cout << endl << "Citire Vector Medicamente :" << endl;
    for (int i = 0; i < 3;i++) {
        cin >> m[i];
    }

    cout << endl << "----------------------------" << endl;

    cout << endl << "Afisare Vector Medicamente :" << endl;
    for (int i = 0; i < 3;i++) {
        cout << m[i];
    }

    cout << endl << "-------------------------" << endl;

    //Matrice Doctori
    Doctor matDoctori[2][3];   //matrice alocata static
    cout << endl << "Citire Matrice Doctori :" << endl;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            cin >> matDoctori[i][j];
        }

    cout << endl << "-------------------------" << endl;

    cout << endl << "Afisare Matrice Doctori :" << endl;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            cout << matDoctori[i][j];
        }


    Doctor** md;      //matrice alocata dinamic
    int a, b; 
    cout << "Numar linii a = "; 
    cin >> a; 
    cout << "Numar coloane b = "; 
    cin >> b; 

    md = new Doctor * [a]; 
    for (int i = 0; i < a; i++) {
        md[i] = new Doctor[b];
    }

    cout << endl << "Citire Matrice Doctori :" << endl;
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++) {
            cin >> md[i][j];
        }

    cout << endl << "-------------------------" << endl;

    cout << endl << "Afisare Matrice Doctori :" << endl;
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++) {
            cout << md[i][j];
        }
}
