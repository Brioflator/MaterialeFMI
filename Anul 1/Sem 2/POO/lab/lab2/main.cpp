#include <iostream>
#include <string.h>
#include<vector>
using namespace std;

class Persoana
{
private:
    char* nume;  //pointeri  char nume[100]
    int varsta;
    const int iDPersoana; // nu exista setter
    bool angajat;

    float* cheltuieliInUltimeleNLuni; // la fel si pentru int*, long* etc Persoane*
    int luni;

    string* cumparaturiInUltimaLuna;
    int nrArticoleCumparate;

    char initialaTata;
    static int contorId;
protected:
    string prenume;
public:
    Persoana();
    Persoana(char* nume, string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate, string* cumparaturiInUltimaLuna,char initialaTata);
    Persoana(const Persoana& per);
    Persoana operator=(const Persoana& per);
    void citire();
    void afisare();
    friend istream& operator>>(istream& in, Persoana& per);
    friend ostream& operator<<(ostream& out, const Persoana& per);
    ~Persoana();
};
    int Persoana::contorId = 1000;

    Persoana::Persoana(char* nume, string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate, string* cumparaturiInUltimaLuna,char initialaTata):iDPersoana(contorId++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);

        this->varsta=varsta;
        this->angajat=angajat;
        this->prenume=prenume;
        this->initialaTata=initialaTata;
        this->luni=luni;
        this->nrArticoleCumparate=nrArticoleCumparate;

        this->cheltuieliInUltimeleNLuni=new float[luni];
        for(int i=0; i<luni; i++)
            this->cheltuieliInUltimeleNLuni[i]=cheltuieliInUltimeleNLuni[i];

        this->cumparaturiInUltimaLuna=new string[nrArticoleCumparate];
        for(int i=0; i<nrArticoleCumparate; i++)
            this->cumparaturiInUltimaLuna[i]=cumparaturiInUltimaLuna[i];

    }
    Persoana::Persoana():iDPersoana(contorId++)
    {
        nume=new char[strlen("Anonim")+1];
        strcpy( this->nume,"Anonim");

        this->varsta=0;
        this->angajat=false;
        this->cheltuieliInUltimeleNLuni=NULL;// nullptr
        this->luni=0;
        this->cumparaturiInUltimaLuna=NULL;
        this->nrArticoleCumparate=0;
        this->initialaTata='q';
        this->prenume="Anonim";
    }
    Persoana::Persoana(const Persoana& per):iDPersoana(contorId++) {
        this->nume=new char[strlen(per.nume)+1];
        strcpy( this->nume, per.nume);

        this->varsta=per.varsta;
        this->angajat=per.angajat;
        this->prenume=per.prenume;
        this->initialaTata=per.initialaTata;
        this->luni=per.luni;
        this->nrArticoleCumparate=per.nrArticoleCumparate;

        this->cheltuieliInUltimeleNLuni=new float[per.luni];
        for(int i=0; i<per.luni; i++)
            this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

        this->cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
        for(int i=0; i<nrArticoleCumparate; i++)
            this->cumparaturiInUltimaLuna[i]=cumparaturiInUltimaLuna[i];
    }
    Persoana Persoana::operator=(const Persoana& per) {
        if(this != &per) {
            if (this->nume != NULL)
                delete[] this->nume;
            if (this->cheltuieliInUltimeleNLuni != NULL)
                delete[] this->cheltuieliInUltimeleNLuni;
            if (this->cumparaturiInUltimaLuna != NULL)
                delete[] this->cumparaturiInUltimaLuna;

            this->nume=new char[strlen(per.nume)+1];
            strcpy( this->nume, per.nume);

            this->varsta=per.varsta;
            this->angajat=per.angajat;
            this->prenume=per.prenume;
            this->initialaTata=per.initialaTata;
            this->luni=per.luni;
            this->nrArticoleCumparate=per.nrArticoleCumparate;

            this->cheltuieliInUltimeleNLuni=new float[per.luni];
            for(int i=0; i<per.luni; i++)
                this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

            this->cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
            for(int i=0; i<nrArticoleCumparate; i++)
                this->cumparaturiInUltimaLuna[i]=cumparaturiInUltimaLuna[i];
        }
        return *this;

    }

    void Persoana::citire() {
        char numeaux[100];

        cout<<"Nume: ";
        cin>>numeaux;
        if (this->nume!=NULL)
            delete[]this->nume;
        this->nume=new char[strlen(numeaux)+1];
        strcpy(this->nume, numeaux);

        cout<<"Varsta: ";
        cin>>this->varsta;
        cout<<"Angajat: ";
        cin>>this->angajat;
        cout<<"Prenume: ";
        cin>>this->prenume;
        cout << "Initiala tata: ";
        cin >> this->initialaTata;
        cout<< "Luni: ";
        cin >> this->luni;
        cout<<"Cheltuieli in ultimile n luni: ";

        if(this->cheltuieliInUltimeleNLuni!=NULL)
            delete[] this->cheltuieliInUltimeleNLuni;
        this->cheltuieliInUltimeleNLuni=new float[this->luni];
        for(int i=0; i<this->luni; i++){
            cout<<"Cheltuieli in luna "<<i+1<<" valoreaza ";
            cin>>this->cheltuieliInUltimeleNLuni[i];
        }
        cout<<"Cumparaturi in ultimile n luni: ";
        if(this->cumparaturiInUltimaLuna!=NULL)
            delete[] this->cumparaturiInUltimaLuna;
        cout<<"Nr articole cumparate: ";
        cin >> this->nrArticoleCumparate;
        this->cumparaturiInUltimaLuna=new string[this->nrArticoleCumparate];
        for(int i=0; i<this->luni; i++){
            cout<<"Cumparaturi in luna "<<i+1<<" valoreaza ";
            cin>>this->cumparaturiInUltimaLuna[i];
        }

    }

    void Persoana::afisare() {
        cout << "Numele este " << this->nume;
        cout << "\nPrenumele este " << this->prenume;
        cout << "\nVarsta este " << this->varsta;
        cout << "\nEste engajat?" << this->angajat;
        cout<<"\nCheltuieli in ultimile n luni: ";
        for(int i=0; i<this->luni; i++)
            cout<<"Cheltuieli in luna "<<i+1<<" valoreaza " << this->cheltuieliInUltimeleNLuni[i];
        cout<<"\nCumparaturi in ultimile n luni: ";
        for(int i=0; i<this->luni; i++)
            cout<<"Cumparaturi in luna "<<i+1<<" valoreaza " << this->cumparaturiInUltimaLuna[i];
    }

    istream& operator>>(istream& in, Persoana& per) {
        char numeaux[100];

        cout<<"Nume: ";
        in>>numeaux;
        if (per.nume!=NULL)
            delete[]per.nume;
        per.nume=new char[strlen(numeaux)+1];
        strcpy(per.nume, numeaux);

        cout<<"Varsta: ";
        in>>per.varsta;
        cout<<"Angajat: ";
        in>>per.angajat;
        cout<<"Prenume: ";
        in>>per.prenume;
        cout << "Initiala tata: ";
        in >> per.initialaTata;
        cout<< "Luni: ";
        in >> per.luni;
        cout<<"Cheltuieli in ultimile n luni: ";

        if(per.cheltuieliInUltimeleNLuni!=NULL)
            delete[] per.cheltuieliInUltimeleNLuni;
        per.cheltuieliInUltimeleNLuni=new float[per.luni];
        for(int i=0; i<per.luni; i++){
            cout<<"Cheltuieli in luna "<<i+1<<" valoreaza ";
            in>>per.cheltuieliInUltimeleNLuni[i];
        }
        cout<<"Cumparaturi in ultimile n luni: ";
        if(per.cumparaturiInUltimaLuna!=NULL)
            delete[] per.cumparaturiInUltimaLuna;
        cout<<"Nr articole cumparate: ";
        in >> per.nrArticoleCumparate;
        per.cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
        for(int i=0; i<per.luni; i++){
            cout<<"Cumparaturi in luna "<<i+1<<" valoreaza ";
            in>>per.cumparaturiInUltimaLuna[i];
        }
    }

    ostream& operator<<(ostream& out, const Persoana& per) {
        out << "Numele este " << per.nume;
        out << "\nPrenumele este " << per.prenume;
        out << "\nVarsta este " << per.varsta;
        out << "\nEste engajat?" << per.angajat;
        out<<"\nCheltuieli in ultimile n luni: ";
        for(int i=0; i<per.luni; i++)
            out<<"Cheltuieli in luna "<<i+1<<" valoreaza " << per.cheltuieliInUltimeleNLuni[i];
        out<<"\nCumparaturi in ultimile n luni: ";
        for(int i=0; i<per.luni; i++)
            out<<"Cumparaturi in luna "<<i+1<<" valoreaza " << per.cumparaturiInUltimaLuna[i];
    }

    Persoana::~Persoana() {
        if (this->nume != NULL)
            delete[] this->nume;
        if (this->cheltuieliInUltimeleNLuni != NULL)
            delete[] this->cheltuieliInUltimeleNLuni;
        if (this->cumparaturiInUltimaLuna != NULL)
            delete[] this->cumparaturiInUltimaLuna;
    }

int main() {
    Persoana p, p1 = p, p3;
    p3 = p1;
    cin >> p1;
    cout << p1;
    return 0;
}

