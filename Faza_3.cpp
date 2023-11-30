#include <iostream>
#include<fstream>
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
    friend ostream& operator<<(ostream& consola, const Doctor& d) {     //nu e metoda !! (chiar daca am facut implementarea 'inline' in interiorul clasei); e functie prietena, deci nu o pot apela in main prin obiect (din cauza asta nu vedea operatorul) 
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


    //operatori fisiere
    //operator scriere in fisier << - doar pt fisiere text !
    friend ofstream& operator<<(ofstream& fisier, const Doctor& d) {
        fisier << d.nume << "\n" << d.anNastere << "\n" << d.specializare << "\n" << d.salariu << "\n" << d.salariuMinim;
        return fisier;
    }

    //operator citire din fisier >> - doar pt fisiere text ! 
    friend ifstream& operator>>(ifstream& fisier, Doctor& d) {
        fisier >> d.nume;
        int val = 0;
        fisier >> val; //citire fake an - pt atribut constant ; practic trb sa sar peste valoarea sa din fisier 
        if (d.specializare != NULL) {
            delete[]d.specializare;
        }
        char temp[100];
        fisier >> temp;
        d.specializare = new char[strlen(temp) + 1];
        strcpy_s(d.specializare, strlen(temp) + 1, temp);

        fisier >> d.salariu;
        fisier >> val; //citire fake salariu minim - pt atribut static

        return fisier;
    }

    //operator scriere in fisier binar  
    fstream& scriereFisierBinar(fstream& fisierBinar) {
        fisierBinar.write((char*)this->specializare, (sizeof(char) * strlen(this->specializare)));
        fisierBinar.write((char*)&this->anNastere, sizeof(int)); 
        fisierBinar.write((char*)&this->salariu, sizeof(float)); 
        fisierBinar.write((char*)&this->salariuMinim, sizeof(int));
        fisierBinar.close();
        return fisierBinar;
    }

    //operator citire din fisier binar
    fstream& citireFisierBinar(fstream& fisierBinar) {
        fisierBinar.read((char*)this->specializare, (sizeof(char) * strlen((this->specializare) + 1)));
        int val = 0; 
        fisierBinar.read((char*)&val, sizeof(int));
        fisierBinar.read((char*)&this->salariu, sizeof(float));
        int sal = 0; 
        fisierBinar.read((char*)&sal, sizeof(int));
        fisierBinar.close();
        return fisierBinar;
    }

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


    //metoda scriere atribut cu atribut in fisier binar
    fstream& scriereFisierBinar(fstream& fisierBinar) {
        //size_t lungimeStringNume = this->nume.length();              //salvez lungimea string-ului inainte de a-l scrie => pt a-l putea citi din fisier dupa
        //fisierBinar.write((char*)&lungimeStringNume, sizeof(size_t));
        //fisierBinar.write((char*)this->nume.c_str(), lungimeStringNume);

        fisierBinar.write((char*)this->oras, (sizeof(char) * strlen((this->oras)+1)));

       /* size_t lungimeStringDomeniu = this->domeniu.length();
        fisierBinar.write((char*)&lungimeStringDomeniu, sizeof(size_t));
        fisierBinar.write((char*)this->domeniu.c_str(), lungimeStringDomeniu);*/

        fisierBinar.write((char*)&this->anInfiintare, sizeof(int));
        fisierBinar.write((char*)&this->nrAngajati, sizeof(int));
        fisierBinar.write((char*)&this->suprafataMinimaSalon, sizeof(int));
        fisierBinar.close();
        return fisierBinar;
    }


    //metoda citire atribut cu atribut din fisier binar
    fstream& citireFisierBinar(fstream& fisierBinar) {
       /* size_t lungimeStringNume;
        fisierBinar.read((char*)&lungimeStringNume, sizeof(size_t));
        char* temp = new char[lungimeStringNume + 1];
        fisierBinar.read(temp, lungimeStringNume);
        temp[lungimeStringNume] = '\0';
        this->nume = temp;
        delete[] temp;*/

        fisierBinar.read((char*)this->oras, (sizeof(char) * strlen((this->oras)+1)));

        /*size_t lungimeStringDomeniu;
        fisierBinar.read((char*)&lungimeStringDomeniu, sizeof(size_t));
        char* temp1 = new char[lungimeStringDomeniu + 1];
        fisierBinar.read(temp1, lungimeStringDomeniu);
        temp1[lungimeStringNume] = '\0';
        this->domeniu = temp1;
        delete[] temp1;*/

        int an = 0;
        fisierBinar.read((char*)&an, sizeof(int));
        fisierBinar.read((char*)&this->nrAngajati, sizeof(int));
        int val = 0;
        fisierBinar.read((char*)&val, sizeof(int));
        fisierBinar.close();
        return fisierBinar;
    }

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

    //operatori fisier text
    //operator scriere in fisier text << 
    friend ofstream& operator<<(ofstream& fisier, const Medicament& m) {
        fisier << m.nume << "\n" << m.substantaActiva << "\n" << m.tip << "\n" << m.gramaj << "\n" << m.TVA;
        return fisier;
    }

    //operator citire din fisier text >> 
    friend ifstream& operator>>(ifstream& fisier, Medicament& m) {
        fisier >> m.nume;
        string aux;
        fisier >> aux; //citire fake pt atribut constant 
        if (m.tip != NULL) {
            delete[]m.tip;
        }
        char temp[50];
        fisier >> temp;
        m.tip = new char[strlen(temp) + 1];
        strcpy_s(m.tip, strlen(temp) + 1, temp);

        fisier >> m.gramaj;
        int val = 0;
        fisier >> val; //citire fake pt atribut static

        return fisier;
    }

    /*void test() {
        cout << this << endl;
        cout << this->nume << endl;
        cout << (*this).nume << endl;
        cout << &this->nume << endl;
        cout << &this->substantaActiva << endl;
    }*/
};
int Medicament::TVA = 9;   //initializare atribut static 


class Farmacie {
private:
    string nume;
    string oras;
    Medicament* medicamente;
    int nrMedicamente;

public:
    //constructor 
    Farmacie() {
        this->nume = "HelpNet";
        this->oras = "Bucuresti";
        this->nrMedicamente = 2;
        this->medicamente = new Medicament[this->nrMedicamente];
    }


    //constructor cu parametrii
    Farmacie(string nume, string oras, Medicament* m, int nr) {
        this->nume = nume;
        this->oras = oras;
        this->nrMedicamente = nr;
        this->medicamente = new Medicament[this->nrMedicamente];
        for (int i = 0; i < this->nrMedicamente; i++) {
            this->medicamente[i] = m[i];
        }
    }

    //constructor de copiere
    Farmacie(const Farmacie& f) {
        this->nume = f.nume;
        this->oras = f.oras;
        this->nrMedicamente = f.nrMedicamente;
        this->medicamente = new Medicament[f.nrMedicamente];
        for (int i = 0; i < f.nrMedicamente; i++) {
            this->medicamente[i] = f.medicamente[i];
        }

    }

    //operator de atribuire = 
    Farmacie& operator=(const Farmacie f) {
        this->nume = f.nume;
        this->oras = f.oras;
        this->nrMedicamente = f.nrMedicamente;
        if (this->medicamente != NULL) {
            delete[]this->medicamente;
        }
        this->medicamente = new Medicament[f.nrMedicamente];
        for (int i = 0; i < f.nrMedicamente; i++) {
            this->medicamente[i] = f.medicamente[i];
        }
        return *this;
    }

    //destructor
    ~Farmacie() {
        if (this->medicamente != NULL) {
            delete[]this->medicamente;
        }
    }

    //getteri 
    string getNume() {
        return this->nume;
    }

    string getOras() {
        return this->oras;
    }

    int getNrMedicamente() {
        return this->nrMedicamente;
    }

    /*Medicament* getMedicamente() {
        return this->medicamente;
    }*/

    void afisareVectorMedicamente() {
        for (int i = 0; i < this->nrMedicamente; i++) {
            cout << this->medicamente[i];
        }
    }

    //setteri 
    void setNume(string nume) {
        if (nume.length() > 3) {
            this->nume = nume;
        }
    }

    void setOras(string oras) {
        if (nume.length() > 3) {
            this->oras = oras;
        }
    }

    void setNrMedicamente(int nr) {
        if (nr >= 0) {
            this->nrMedicamente = nr;
        }
    }

    void setMedicamente(Medicament* m, int nr) {
        if (this->medicamente != NULL) {
            delete[]this->medicamente;
        }
        this->medicamente = new Medicament[nr];
        for (int i = 0; i < nr; i++) {
            this->medicamente[i] = m[i];
        }
    }

    //operator functie()
    int operator()() {     //calcul nr de medicamente cu substanta activa ibuprofen
        int nr = 0;
        for (int i = 0; i < this->nrMedicamente; i++) {
            if (this->medicamente[i].getSubstantaActiva() == "Ibuprofen") {
                nr += 1;
            }
        }
        return nr;
    }

    //operator afisare <<
    friend ostream& operator<<(ostream& consola, Farmacie f) {
        consola << endl << "Nume farmacie: " << f.nume << endl;
        consola << "Oras: " << f.oras << endl;
        consola << "Nr medicamente: " << f.nrMedicamente << endl;
        consola << "Vector medicamente: " << endl;
        for (int i = 0; i < f.nrMedicamente; i++) {
            consola << endl << "Nume: " << f.medicamente[i].getNume() << endl;
            consola << "Substanta activa: " << f.medicamente[i].getSubstantaActiva() << endl;
            consola << "Tip: " << f.medicamente[i].getTip() << endl;
            consola << "Gramaj: " << f.medicamente[i].getGramaj() << " mg" << endl;
            consola << "TVA: " << f.medicamente[i].getTVA() << " %" << endl;
        }

        return consola;
    }

    //operator citire >> 
    friend istream& operator>>(istream& input, Farmacie& f) {
        cout << endl << "Nume farmacie: ";
        input >> f.nume;
        cout << "Oras: ";
        input >> f.oras;
        cout << "Nr medicamente: ";
        input >> f.nrMedicamente;
        if (f.medicamente != NULL) {
            delete[]f.medicamente;
        }
        f.medicamente = new Medicament[f.nrMedicamente];

        cout << "Vector medicamente: ";
        for (int i = 0; i < f.nrMedicamente; i++) {
            input >> f.medicamente[i];
        }

        return input;
    }
};


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
    cin >> d1;

    ofstream fisierDoctor("fisierDoctor.txt", ios::out);
    fisierDoctor << d1;

    Doctor d2;
    ifstream fileInput("fisierDoctor.txt", ios::in);
    fileInput >> d2;
    cout << d2;

    Medicament m1;
    cin >> m1;

    ofstream fisierMed("fisierMedicament.txt", ios::out);
    fisierMed << m1;

    Medicament m2;
    ifstream fisierInput("fisierMedicament.txt", ios::in);
    fisierInput >> m2;
    cout << m2; 

    fstream fisierBinar("fisierBinar.cat", ios::binary | ios::out);
    Spital s1;
    cin >> s1;

    s1.scriereFisierBinar(fisierBinar);

    fstream fisierBCitire("fisierBinar.cat", ios::binary | ios::in);
    Spital s2 ("bubu", 2080, 50);
    s2.citireFisierBinar(fisierBCitire);
    cout << s2;

    fstream fisier("fisierBinarDoctor.bruh", ios::binary | ios::out); 
    Doctor d3; 
    cin >> d3; 

    d3.scriereFisierBinar(fisier); 

    fstream fisierCitire("fisierBinarDoctor.bruh", ios::binary | ios::in);
    Doctor d4; 
    d4.citireFisierBinar(fisierCitire);
    cout << d4;

    /*Medicament m;
    m.test();*/

}
