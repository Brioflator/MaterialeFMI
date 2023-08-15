#include <iostream>
#include <vector>

using namespace std;

class IOInterface {
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
};

class Produs:public IOInterface {
protected:
    string nume;
    float pret;
    string uom;
public:
    Produs() {
        this->nume = "necunoscut";
        this->pret = 0;
        this->uom = "necunoscut";
    }

    Produs(string nume, float pret, string uom) {
        this->nume = nume;
        this->pret = pret;
        this->uom = uom;
    }
    Produs(const Produs& p) {
        this->nume = p.nume;
        this->pret = p.pret;
        this->uom = p.uom;
    }
    Produs& operator=(const Produs& p) {
        if(this != &p) {
            this->nume = p.nume;
            this->pret = p.pret;
            this->uom = p.uom;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        cout << "nume: ";
        in >> this->nume;
        cout << "pret: ";
        in >> this->pret;
        cout << "unitate de masura: ";
        in >> this->uom;
        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        out << "nume: "<< this->nume << endl;
        out << "pret: " << this->pret << endl;
        out << "unitate de masura: " << this->uom << endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, const Produs& p) {
        return p.afisare(out);
    }

     friend istream& operator>>(istream& in, Produs& p) {
        return p.citire(in);
    }

    virtual void calculeazaPret() = 0;
};

class ProdusPerisabil:public Produs {
    string dataExp;
public:
    ProdusPerisabil():Produs(){
        this->dataExp = "necunoscuta";
    }
    ProdusPerisabil(string nume, float pret, string uom, string dataExp):Produs(nume, pret, uom) {
        this->dataExp = dataExp;
    }
    ProdusPerisabil(const ProdusPerisabil& p):Produs(p) {
        this->dataExp = p.dataExp;
    }
    ProdusPerisabil& operator=(const ProdusPerisabil& p){
        if (this != &p) {
            Produs::operator=(p);
            this->dataExp = p.dataExp;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Produs::citire(in);
        cout << "data expirare: ";
        in >> this->dataExp;
        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        Produs::afisare(out);
        out << "data expirare: " << this->dataExp << endl;
        return out;
    }

    void calculeazaPret() {
        cout << "pretul final este: " << this->pret*1.5 << endl;
    }
};

class ProdusNeperisabil:public Produs {
    int anGarantie;
public:
    ProdusNeperisabil():Produs(){
        this->anGarantie = 0;
    }
    ProdusNeperisabil(string nume, float pret, string uom, int anGarantie):Produs(nume, pret, uom) {
        this->anGarantie = anGarantie;
    }
    ProdusNeperisabil(const ProdusNeperisabil& p):Produs(p) {
        this->anGarantie = p.anGarantie;
    }
    ProdusNeperisabil& operator=(const ProdusNeperisabil& p){
        if (this != &p) {
            Produs::operator=(p);
            this->anGarantie = p.anGarantie;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Produs::citire(in);
        cout << "ani garantie: ";
        in >> this->anGarantie;
        return in;
    }

    virtual ostream& afisare(ostream& out) {
        Produs::afisare(out);
        out << "ani garantie: " << this->anGarantie << endl;
        return out;
    }

    void calculeazaPret() {
        cout << "pretul final este: " << this->pret*1.25 << endl;
    }
};



int main()
{
    vector<Produs*> listaProduse;

    while (true) {
        int inputValue;
        cout << "Apasa 1 ca sa adaugi un produs perisabil\n";
        cout << "Apasa 2 ca sa adaugi un produs neperisabil\n";
        cout << "Apasa 3 ca sa afisezi\n";

        cin >> inputValue;
        if (inputValue == 1) {
            ProdusPerisabil* p = new ProdusPerisabil();
            cin >> *p;
            listaProduse.push_back(new ProdusPerisabil(p));
        }
        else if (inputValue == 2) {
            ProdusNeperisabil* p = new ProdusNeperisabil();
            cin >> *p;
            listaProduse.push_back(new ProdusPerisabil(p));
        }
        else if (inputValue == 3) {
            for(int i = 0; i < listaProduse.size(); i++) {
                cout << *listaProduse[i];
            }
        }
        else
            break;
    }
    return 0;
}
