#include <iostream>

using namespace std;

class furnizor;
class ST;

class IOI
{
public:
    virtual ostream& afis(ostream&) const=0;
    virtual istream& citi(istream&)=0;

};

class furnizor: public IOI
{
    int var1;
    bool var2;
    int var3;
    string var4;

public:
    furnizor();
    furnizor(int var1, bool var2, int var3, string var4);
    furnizor(int var1, bool var2);
    furnizor(int var3, string var4);
    furnizor(const furnizor& f);
    ~furnizor();

    furnizor operator=(const furnizor& f);
    bool operator==(furnizor f) {return var1==f.var1;}
    bool operator<=(furnizor &f)
    {
        if(var1<=f.var1) return true;
        if(var1>f.var1) return false;
    }

    bool operator>=(furnizor &f)
    {
        if(var1>=f.var1) return true;
        if(var1<f.var1) return false;
    }

    furnizor operator ++ ();
    furnizor operator ++ (int);

    furnizor operator + (furnizor f);
    furnizor operator - (furnizor f);

    char operator[](int i)
{
    int x=var4.length();
    if (0<=i && i<x)
        return this->var4[i];
    cout<<"Index gresit"<<endl;
}

    virtual ostream& afis(ostream&)const;
    virtual istream& citi(istream&);

    friend istream& operator>>(istream& in, furnizor& f);
    friend ostream& operator<<(ostream& out, const furnizor& f);

    void set_var1(int m)
    {
        this->var1=m;
    }

    int get_var1()
    {
        return var1;
    }

};

furnizor::furnizor()
{
    this->var1=0;
    this->var2=false;
    this->var3=0;
    this->var4="GOL";
}

furnizor::furnizor(int var1, bool var2, int var3, string var4)
{
    this->var1=var1;
    this->var2=var2;
    this->var3=var3;
    this->var4=var4;
}

furnizor::furnizor(int var1, bool var2)
{
    this->var1=var1;
    this->var2=var2;
}

furnizor::furnizor(int var3, string var4)
{
    this->var3=var3;
    this->var4=var4;
}

furnizor::furnizor(const furnizor& f)
{
    this->var1=f.var1;
    this->var2=f.var2;
    this->var3=f.var3;
    this->var4=f.var4;
}

furnizor furnizor::operator=(const furnizor& f)
{
    if(this!=&f)
    {
        this->var1=f.var1;
    this->var2=f.var2;
    this->var3=f.var3;
    this->var4=f.var4;
    }

    return *this;

}

furnizor furnizor::operator++()
{
    this->var1++;
    return *this;
}

furnizor furnizor::operator++(int)
{
    furnizor aux=*this;
    this->var1++;
    return aux;
}

furnizor furnizor::operator+(furnizor f)
{
    furnizor aux;
    aux.var1=var1+f.var1;
    return aux;
}

furnizor furnizor::operator-(furnizor f)
{
    furnizor aux;
    aux.var1=var1-f.var1;
    return aux;
}

    ostream& furnizor::afis(ostream& out)const
    {
        out<<"var1: "<<this->var1<<endl;
        out<<"var2: "<<this->var2<<endl;
        out<<"var3: "<<this->var3<<endl;
        out<<"var4: "<<this->var4<<endl;

        return out;
    }
    istream& furnizor::citi(istream& in)
    {
        cout<<"var1: ";
        in>>this->var1;
        cout<<"var2: ";
        in>>this->var2;
        cout<<"var3: ";
        in>>this->var3;
        cout<<"var4: ";
        in>>this->var4;

        return in;
    }


istream& operator>>(istream& in, furnizor& f)
{
    return f.citi(in);

}

ostream& operator<<(ostream& out, const furnizor& f)
{
    return f.afis(out);

}

class ST
{
private:
    static ST *obj;
    furnizor f;

    ST()
    {
        f.set_var1(1);
    }

public:
    ST(const ST&)=delete;           //pt a fi cu adv singleton
    static ST* get_insta()
    {
        if(!obj) obj=new ST();
        return obj;
    }

    void afisare_editura()
    {
       cout<<"Putem sa avem o singura editura partenera, iar aceasta este: "<<f.get_var1()<<endl;
    }

    int get_edy() {return this->f.get_var1();}
    void set_edy (int a) {this->f.set_var1(a);}
};
ST* ST::obj=0;


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
    return 0;
}
