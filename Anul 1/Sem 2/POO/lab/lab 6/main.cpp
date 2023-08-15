#include <iostream>

using namespace std;

class produs{
protected:
    string nume;
    float pret;
    string UM;

public:
    produs()
    {
        this->nume="Nema";
        this->pret=0;
        this->UM="Nema";
    }
    produs(const produs &p)
    {
        this->nume=p.nume;
        this->pret=p.pret;
        this->UM=p.UM;
    }
    produs(string nume, float pret, string UM)
    {
        this->nume=nume;
        this->pret=pret;
        this->UM=UM;
    }
    produs& operator=(const produs &p)
    {
        if(this!=&p)
        {
            this->nume=p.nume;
        this->pret=p.pret;
        this->UM=p.UM;
        }
        return *this;
    }
    friend istream& operator>> (istream& in, produs &p)
    {
        cout<<"Nume: ";
        in>>p.nume;
        cout<<"Pret: ";
        in>>p.pret;
        cout<<"Unitate: ";
        in>>p.UM;

        return in;
    }
    friend ostream& operator<< (ostream& out, const produs &p)
    {
        cout<<"Nume: ";
        out<<p.nume;
        cout<<endl<<"Pret: ";
        out<<p.pret;
        cout<<endl<<"Unitate: ";
        out<<p.UM;

        return out;
    }

    virtual void calc_pret()=0;

};

class perisabil: public produs{
    string exp;
public:
    perisabil():produs(){
        this->exp="Nema";
    }

    perisabil(string nume, float pret, string UM, string exp):produs(nume, pret, UM){
        this->exp=exp;
    }

    perisabil(const perisabil &p): produs(p){
        this->exp=p.exp;
    }

    perisabil& operator=(const perisabil& p){
        if(this!=&p)
        {
            produs::operator=(p);
            this->exp=p.exp;
        }

        return *this;
    }

    friend istream& operator>>(istream& in, perisabil& p)
    {
        in>>(produs&) p;
        cout<<endl<<"Expirare: ";
        in>>p.exp;

        return in;
    }

    friend ostream& operator<<(ostream& out, perisabil& p)
    {
        out<<(produs&) p;
        cout<<endl<<"Expirare: ";
        out<<p.exp;

        return out;
    }

    void calc_pret(){cout<<"Pretul brut este: "<<this->pret<<endl;}
};

class neperisabil: public produs{
    int ani;
public:
    neperisabil():produs(){
        this->ani=0;
    }

    neperisabil(string nume, float pret, string UM, int ani):produs(nume, pret, UM){
        this->ani=ani;
    }

    neperisabil(const neperisabil &p): produs(p){
        this->ani=p.ani;
    }

    neperisabil& operator=(const neperisabil& p){
        if(this!=&p)
        {
            produs::operator=(p);
            this->ani=p.ani;
        }

        return *this;
    }

    friend istream& operator>>(istream& in, neperisabil& p)
    {
        in>>(produs&) p;
        cout<<endl<<"garantie: ";
        in>>p.ani;

        return in;
    }

    friend ostream& operator<<(ostream& out, neperisabil& p)
    {
        out<<(produs&) p;
        cout<<endl<<"garantie: ";
        out<<p.ani;

        return out;
    }

    void calc_pret(){cout<<"Pretul final este: "<<this->pret*1.25<<endl;}
};

int main()
{
    perisabil p1("test", 100, "kg", "maine");
    neperisabil p2("test", 100, "kg", 4);



    return 0;
}
