// Balescu Alexandru 144 //
// Compiler Codeblocks //
// Eduard Smeteanca //


#include <bits/stdc++.h>

class bilet;
class card;
class card_s;
class IOI;

using namespace std;

class IOI
{
public:
    virtual istream& citi(istream& in)=0;
    virtual ostream& afisi(ostream& out)const=0;
};

class bilet
{
protected:
    string tip;
    float pret;
    int timp;
public:
    bilet();
    bilet(string tip, float pret, int timp);
    bilet(string tip, float pret);
    bilet(const bilet &b);
    bilet operator=(const bilet &b);

    friend ostream& operator<<(ostream& out, const bilet &b)
    {
        out<<"Tip bilet: "<<b.tip<<endl;
        out<<"pret: "<<b.pret<<endl;
        out<<"timp: "<<b.timp<<endl;

        return out;
    }

};

//static bilet::timp=0;

bilet::bilet()
{
    this->tip="No_type";
    this->pret=0;
    this->timp=0;
}

bilet::bilet(string tip, float pret, int timp)
{
    this->tip=tip;
    this->pret=pret;
    this->timp=timp;
}
bilet::bilet(string tip, float pret)
{
    this->tip=tip;
    this->pret=pret;
}

bilet::bilet(const bilet &b)
{
    this->tip=b.tip;
    this->pret=b.pret;
    this->timp=b.timp;
}


bilet bilet::operator=(const bilet &b)
{
    if(this!=&b)
    {
       this->tip=b.tip;
    this->pret=b.pret;
    this->timp=b.timp;
    }

    return *this;
}


class card: public virtual IOI
{
protected:
    string tip;
public:
    card()
    {
        this->tip="electronic";
    }

    //virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)
    {
        out<<"Tip card: "<<this->tip<<endl;
    }

    //friend istream& operator>>(istream& in, card_s& cs)
    friend ostream& operator<<(ostream& out, card& cs);
    card(const card &b);
    //card operator=(const card &b);
};

card::card(const card &b)
{
    this->tip=b.tip;

}


//card card::operator=(const card &b)
//{
//    if(this!=&b)
//    {
//       this->tip=b.tip;
//    }
//
//    return *this;
//}

class card_s: public virtual card
{
protected:
    vector<bilet*> suprafata;
    int contor=0;
    float suma=0;

    public:
    card_s():card()
    {
        bilet *aux= new bilet("suprafata", 2);
        suprafata.push_back(aux);
        contor++;
        suma+=2;
        if(contor%8==0)
        {
            suprafata.push_back(aux);
        contor++;
        suma+=2;
        }
    }
    void add_bilet_suprafata()
    {
        bilet *aux= new bilet("suprafata", 2);
        suprafata.push_back(aux);
        contor++;
        suma+=2;
        if(contor%8==0)
        {
            suprafata.push_back(aux);
        contor++;
        suma+=2;
        }
    }
    void add_bilet_metrou()
    {
        bilet *aux= new bilet("metrou", 2.5);
        suprafata.push_back(aux);
        contor++;
        suma+=2.5;

        if(contor%8==0)
        {
            suprafata.push_back(aux);
        contor++;
        suma+=2.5;
        }
    }

    virtual ostream& afisi(ostream& out);

    friend ostream& operator<<(ostream& out, card_s& cs);
};


ostream& operator<<(ostream& out, card_s& cs)
{
    out<<"detalii ultimul bilet"<<*cs.suprafata[cs.contor]<<endl;
    out<<"Total valoare bilete"<<cs.suma<<endl;

    return out;
}


class card_m: public card
{
protected:
    vector<bilet*> metrou;
    int contor=0;
    float suma=0;

    public:
    card_m():card()
    {
        bilet *aux= new bilet("metrou", 2.5);
        metrou.push_back(aux);
        contor++;
        suma+=2.5;
        if(contor%8==0)
        {
           metrou.push_back(aux);
        contor++;
        suma+=2.5;
        }
    }
    void add_bilet_suprafata()
    {
        bilet *aux= new bilet("metrou", 2);
        metrou.push_back(aux);
        contor++;
        suma+=2;
        if(contor%8==0)
        {
           metrou.push_back(aux);
        contor++;
        suma+=2;
        }
    }
    void add_bilet_metrou()
    {
        bilet *aux= new bilet("metrou", 2.5);
        metrou.push_back(aux);
        contor++;
        suma+=2.5;
        if(contor%8==0)
        {
           metrou.push_back(aux);
        contor++;
        suma+=2.5;
        }
    }

    virtual ostream& afisi(ostream& out);

    friend ostream& operator<<(ostream& out, card_m& cs);
};


ostream& operator<<(ostream& out, card_m& cs)
{
    out<<"detalii ultimul bilet"<<*cs.metrou[cs.contor]<<endl;
    out<<"Total valoare bilete"<<cs.suma<<endl;

    return out;
}


class card_t: public virtual card
{
protected:
    vector<bilet*> tranzit;
    int contor=0;
    float suma=0;

    public:
    card_t():card()
    {
        bilet *aux= new bilet("tranzit", 3);
        tranzit.push_back(aux);
        contor++;
        suma+=3;
        if(contor%8==0)
        {
            tranzit.push_back(aux);
            contor++;
            suma+=3;
        }
    }
    void add_bilet_tranzit()
    {
        bilet *aux= new bilet("tranzit", 3);
        tranzit.push_back(aux);
        contor++;
        suma+=3;
        if(contor%8==0)
        {
            tranzit.push_back(aux);
            contor++;
            suma+=3;
        }
    }

    virtual ostream& afisi(ostream& out);

    friend ostream& operator<<(ostream& out, card_t& cs);
};


ostream& operator<<(ostream& out, card_t& cs)
{
    out<<"detalii ultimul bilet"<<*cs.tranzit[cs.contor]<<endl;
    out<<"Total valoare bilete"<<cs.suma<<endl;

    return out;
}

class aparat
{
protected:
    string loc;
    int scans;
public:
    aparat()
    {
        this->loc="Neidentificat";
        this->scans=0;
    }
    aparat(string loc)
    {
        this->loc=loc;
    }

    aparat(const aparat &b)
    {
        this->loc=b.loc;
        this->scans=b.scans;
    }
    aparat operator=(const aparat &b)
    {
        if(this!=&b)
        {
           this->loc=b.loc;
        this->scans=b.scans;
        }

        return *this;
    }


    friend ostream& operator<<(ostream& out, aparat& cs)
    {
        out<<"numar scanari: "<<cs.scans;
        out<<"locatie: "<<cs.loc;
    }

};


int main()
{
    bilet a("m", 2);

    card_m m;
    card_s s;
    card_t t;

    cin>>m;
    cin>>s;
    cin>>t;

    cout<<a;
    cout<<endl;
    cout<<m;
    cout<<endl;
    cout<<s;
    cout<<endl;
    cout<<t;
    cout<<endl;



    return 0;
}
