#include <bits/stdc++.h>

using namespace std;

class meniu;
class produs;
class carte;
class DVD;
class DVD_F;
class DVD_M;
class colectie;
class figurina;
class poster;

class IOI
{
public:
    virtual istream& citi(istream& in)=0;
    virtual ostream& afisi(ostream& out)const=0;
};

class produs: public IOI
{
protected:
    float pret;
    int cantitate;
public:
    produs();
    produs(float pret, float cantitate);
    ~produs(){};
    produs(const produs& p);
    friend meniu;
    produs operator=(const produs& p);
    bool operator>=(produs p)
    {
        if(pret>=p.pret) return true;
        return false;
    }

    void set_pret(float p){pret=p;}
    float get_pret(){return pret;}

    void set_cantitate(int c){cantitate=c;}
    int get_cantitate(){return cantitate;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, produs &p);
    friend ostream& operator<<(ostream& out, const produs &p);
};

    istream& produs::citi(istream& in)
    {
        cout<<"pret: ";
        in>>this->pret;
        cout<<"cantitate: ";
        in>>this->cantitate;

        return in;
    }
    ostream& produs::afisi(ostream& out)const
    {
        out<<"pret: "<<this->pret<<endl;
        out<<"cantitate: "<<this->cantitate<<endl;

        return out;
    }

     istream& operator>>(istream& in, produs &p){return p.citi(in);};
     ostream& operator<<(ostream& out, const produs &p){return p.afisi(out);};

produs::produs()
    {
        this->pret=0;
        this->cantitate=0;
    }
produs::produs(float pret, float cantitate)
{
    this->pret=pret;
    this->cantitate=cantitate;
}

produs::produs(const produs& p)
{
    this->pret=p.pret;
    this->cantitate=p.cantitate;
}

produs produs::operator=(const produs& p)
{
    if(this!=&p)
    {
        this->pret=p.pret;
    this->cantitate=p.cantitate;
    }
    return *this;
}
// #############################################################################
class carte: virtual public produs
{
protected:
    string autor;
    string titlu;
    string editura;
public:
    carte();
    carte(float pret, int cantitate, string  autor, string  titlu, string editura);
    ~carte(){};
    carte(const carte& c);
    carte operator=(const carte& c);

    void set_autor(string  c){autor=c;}
    string  get_autor(){return autor;}

    void set_titlu(string c){titlu=c;}
    string get_titlu(){return titlu;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, carte &c);
    friend ostream& operator<<(ostream& out, const carte &c);
};

    istream& carte::citi(istream& in)
    {
        produs::citi(in);
        in.get();
        cout<<"autor: ";
        getline(in, autor);
        cout<<"titlu: ";
        getline(in, titlu);
        cout<<"editura: ";
        getline(in, editura);

        return in;
    }
    ostream& carte::afisi(ostream& out)const
    {
        produs::afisi(out);

        out<<"autor: "<<this->autor<<endl;
        out<<"titlu: "<<this->titlu<<endl;
        out<<"editura: "<<this->editura<<endl;

        return out;
    }

     istream& operator>>(istream& in, carte &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const carte &c){return c.afisi(out);};

carte::carte()
    {
        produs();
        this->autor="Anonim";
        this->titlu="Unknown";
        this->editura="Ioc";
    }
carte::carte(float pret, int cantitate, string  autor, string  titlu, string editura):produs(pret, cantitate)
{
    this->autor=autor;
    this->titlu=titlu;
    this->editura=editura;
}

carte::carte(const carte& c):produs(c)
{
    this->autor=c.autor;
    this->titlu=c.titlu;
    this->editura=c.editura;
}

carte carte::operator=(const carte& p)
{
    if(this!=&p)
    {
        this->autor=p.autor;
        this->titlu=p.titlu;
        this->editura=p.editura;
    }
    return *this;
}
// #####################################################################################################################################

class DVD: virtual public produs
{
protected:
    int minute;
public:
    DVD();
    DVD(float pret, int cantitate, int minute);
    ~DVD(){};
    DVD(const DVD& c);
    DVD operator=(const DVD& c);

    void set_minute(int  c){minute=c;}
    int  get_minute(){return minute;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, DVD &c);
    friend ostream& operator<<(ostream& out, const DVD &c);
};

    istream& DVD::citi(istream& in)
    {
        produs::citi(in);

        cout<<"minute: ";
        in>>this->minute;

        return in;
    }
    ostream& DVD::afisi(ostream& out)const
    {
        produs::afisi(out);

        out<<"minute: "<<this->minute<<endl;

        return out;
    }

     istream& operator>>(istream& in, DVD &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const DVD &c){return c.afisi(out);};

DVD::DVD()
    {
        produs();
        this->minute=0;
    }
DVD::DVD(float pret, int cantitate,int minute):produs(pret, cantitate)
{
    this->minute=minute;
}

DVD::DVD(const DVD& c):produs(c)
{
    this->minute=c.minute;
}

DVD DVD::operator=(const DVD& p)
{
    if(this!=&p)
    {
        this->minute=p.minute;
    }
    return *this;
}

// ##########################################################################################

class DVD_M:  public DVD
{
protected:
    string album;
    string cantareti;
public:
    DVD_M();
    DVD_M(float pret, int cantitate, string album, string cantareti);
    ~DVD_M(){};
    DVD_M(const DVD_M& c);
    DVD_M operator=(const DVD_M& c);

    void set_album(int  c){album=c;}
    string  get_album(){return album;}

    void set_cantareti(int  c){cantareti=c;}
    string  get_cantareti(){return cantareti;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, DVD_M &c);
    friend ostream& operator<<(ostream& out, const DVD_M &c);
};

    istream& DVD_M::citi(istream& in)
    {
        DVD::citi(in);
in.get();
        cout<<"album: ";
        getline(in,album);

        cout<<"cantareti: ";
        getline(in,cantareti);

        return in;
    }
    ostream& DVD_M::afisi(ostream& out)const
    {
        DVD::afisi(out);

        out<<"album: "<<this->album<<endl;
        out<<"cantareti: "<<this->cantareti<<endl;

        return out;
    }

     istream& operator>>(istream& in, DVD_M &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const DVD_M &c){return c.afisi(out);};

DVD_M::DVD_M()
    {
        DVD();
        this->cantareti="Indefinit";
        this->album="Nema";
    }
DVD_M::DVD_M(float pret, int cantitate,string album, string cantareti):DVD(pret, cantitate, minute)
{
    this->album=album;
    this->cantareti=cantareti;
}

DVD_M::DVD_M(const DVD_M& c):DVD(c)
{
    this->album=c.album;
    this->cantareti=c.cantareti;
}

DVD_M DVD_M::operator=(const DVD_M& p)
{
    if(this!=&p)
    {
        this->album=p.album;
        this->cantareti=p.cantareti;
    }
    return *this;
}

// #########################################################################################

class DVD_F:  public DVD
{
protected:
    string titlu;
    string gen;
public:
    DVD_F();
    DVD_F(float pret, int cantitate, string titlu, string gen);
    ~DVD_F(){};
    DVD_F(const DVD_F& c);
    DVD_F operator=(const DVD_F& c);

    void set_titlu(int  c){titlu=c;}
    string  get_titlu(){return titlu;}

    void set_gen(int  c){gen=c;}
    string  get_gen(){return gen;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, DVD_F &c);
    friend ostream& operator<<(ostream& out, const DVD_F &c);
};

    istream& DVD_F::citi(istream& in)
    {
        DVD::citi(in);
in.get();
        cout<<"titlu: ";
        getline(in, titlu);

        cout<<"gen: ";
        getline(in, gen);

        return in;
    }
    ostream& DVD_F::afisi(ostream& out)const
    {
        DVD::afisi(out);

        out<<"titlu: "<<this->titlu<<endl;
        out<<"gen: "<<this->gen<<endl;

        return out;
    }

     istream& operator>>(istream& in, DVD_F &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const DVD_F &c){return c.afisi(out);};

DVD_F::DVD_F()
    {
        DVD();
        this->gen="Indefinit";
        this->titlu="Nema";
    }
DVD_F::DVD_F(float pret, int cantitate,string titlu, string gen):DVD(pret, cantitate, minute)
{
    this->titlu=titlu;
    this->gen=gen;
}

DVD_F::DVD_F(const DVD_F& c):DVD(c)
{
    this->titlu=c.titlu;
    this->gen=c.gen;
}

DVD_F DVD_F::operator=(const DVD_F& p)
{
    if(this!=&p)
    {
        this->titlu=p.titlu;
        this->gen=p.gen;
    }
    return *this;
}

// ##########################################################################################

class colectie: virtual public produs
{
protected:
    string denumire;
public:
    colectie();
    colectie(float pret, int cantitate, string denumire);
    ~colectie(){};
    colectie(const colectie& c);
    colectie operator=(const colectie& c);

    void set_denumire(string c){denumire=c;}
    string get_denumire(){return denumire;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, colectie &c);
    friend ostream& operator<<(ostream& out, const colectie &c);
};

    istream& colectie::citi(istream& in)
    {
        produs::citi(in);
in.get();
        cout<<"denumire: ";
        getline(in, denumire);

        return in;
    }
    ostream& colectie::afisi(ostream& out)const
    {
        produs::afisi(out);

        out<<"denumire: "<<this->denumire<<endl;

        return out;
    }

     istream& operator>>(istream& in, colectie &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const colectie &c){return c.afisi(out);};

colectie::colectie()
    {
        produs();
        this->denumire="Nestiuta";
    }
colectie::colectie(float pret, int cantitate,string denumire):produs(pret, cantitate)
{
    this->denumire=denumire;
}

colectie::colectie(const colectie& c):produs(c)
{
    this->denumire=c.denumire;
}

colectie colectie::operator=(const colectie& p)
{
    if(this!=&p)
    {
        this->denumire=p.denumire;
    }
    return *this;
}

// ##############################################################################################################

class poster: virtual public colectie
{
protected:
    string format;
public:
    poster();
    poster(float pret, int cantitate, string format);
    ~poster(){};
    poster(const poster& c);
    poster operator=(const poster& c);

    void set_format(string c){format=c;}
    string get_format(){return format;}

    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, poster &c);
    friend ostream& operator<<(ostream& out, const poster &c);
};

    istream& poster::citi(istream& in)
    {
        colectie::citi(in);
        cout<<"format: ";
        getline(in, format);

        return in;
    }
    ostream& poster::afisi(ostream& out)const
    {
        colectie::afisi(out);

        out<<"format: "<<this->format<<endl;

        return out;
    }

     istream& operator>>(istream& in, poster &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const poster &c){return c.afisi(out);};

poster::poster()
    {
        colectie();
        this->format="Nestiuta";
    }
poster::poster(float pret, int cantitate,string format):colectie(pret, cantitate, denumire)
{
    this->format=format;
}

poster::poster(const poster& c):colectie(c)
{
    this->format=c.format;
}

poster poster::operator=(const poster& p)
{
    if(this!=&p)
    {
        this->format=p.format;
    }
    return *this;
}

// ###########################################################################################################

class figurina: virtual public colectie
{
protected:
    string categorie;
    string brand;
    string material;

public:
    figurina();
    figurina(float pret, int cantitate, string categorie, string brand, string material);
    ~figurina(){};
    figurina(const figurina& c);
    figurina operator=(const figurina& c);

    void set_categorie(string c){categorie=c;}
    string get_categorie(){return categorie;}

    void set_brand(string c){brand=c;}
    string get_brand(){return brand;}

    void set_material(string c){material=c;}
    string get_material(){return material;}


    virtual istream& citi(istream& in);
    virtual ostream& afisi(ostream& out)const;

    friend istream& operator>>(istream& in, figurina &c);
    friend ostream& operator<<(ostream& out, const figurina &c);
};

    istream& figurina::citi(istream& in)
    {
        colectie::citi(in);

        cout<<"categorie: ";
        getline(in, categorie);

        cout<<"brand: ";
        getline(in, brand);

        cout<<"material: ";
        getline(in, material);


        return in;
    }
    ostream& figurina::afisi(ostream& out)const
    {
        colectie::afisi(out);

        out<<"categorie: "<<this->categorie<<endl;
        out<<"brand: "<<this->brand<<endl;
        out<<"material: "<<this->material<<endl;

        return out;
    }

     istream& operator>>(istream& in, figurina &c){return c.citi(in);};
     ostream& operator<<(ostream& out, const figurina &c){return c.afisi(out);};

figurina::figurina()
    {
        colectie();
        this->categorie="Nestiuta";
        this->brand="Nestiuta";
        this->material="Nestiuta";
    }
figurina::figurina(float pret, int cantitate,string categorie, string brand, string material):colectie(pret, cantitate, denumire)
{
    this->categorie=categorie;
    this->brand=brand;
    this->material=material;
}

figurina::figurina(const figurina& c):colectie(c)
{
    this->categorie=c.categorie;
    this->brand=c.brand;
    this->material=c.material;
}

figurina figurina::operator=(const figurina& p)
{
    if(this!=&p)
    {
        this->categorie=p.categorie;
        this->brand=p.brand;
        this->material=p.material;
    }
    return *this;
}

class meniu
{
protected:
    vector<produs* > inventar;
    int n;
public:
    friend produs;

    void citire()
    {
        string tip;
        produs* p=NULL;
        cout<<"Introduceti numarul de produse: ";
        cin>>n;

        cout<<"Introduceti tipul produsului: "<<endl;
        cout<<"carte"<<endl;
        cout<<"DVD_M"<<endl;
        cout<<"DVD_F"<<endl;
        cout<<"figurina"<<endl;
        cout<<"poster"<<endl;

        for(int i=0;i<n;i++)
        {
            cout<<"Tip ales: ";
            cin>>tip;
            if(tip=="carte") p=new carte;
            else if(tip=="DVD_M") p=new DVD_M;
            else if(tip=="DVD_F") p=new DVD_F;
            else if(tip=="figurina") p=new figurina;
            else if(tip=="poster") p=new poster;
            else {cout<<"Nu e obiect valid, incercati iar."; i--;}

            cin>>*p;
            inventar.push_back(p);

            cout<<endl;
        }
    }

    void afisare()
    {
        cout<<"Produsele sunt: "<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<"ID: "<<i<<endl;
            cout<<*inventar[i]<<endl;
        }

    }

    void ordonare()
    {
        for(int i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
            if(*inventar[i]>=*inventar[j])
                {
                    produs* aux=NULL;
                    aux=inventar[i];
                    inventar[i]=inventar[j];
                    inventar[j]=aux;
                }
    }

    void max_cantitate()
    {
        int maxi=-1;
        produs* aux=NULL;
        for(int i=0;i<n;i++)
        {
            if(inventar[i]->get_cantitate()>=maxi)
            {
                maxi=inventar[i]->get_cantitate();
                aux=inventar[i];
            }
        }
        cout<<"Produsul cu cea mai mare cantitate disponibila: "<<endl;
        cout<<*aux;
    }

};


int main()
{
    meniu m;
    m.citire();
    m.max_cantitate();

    return 0;
}
