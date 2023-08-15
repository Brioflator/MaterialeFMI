#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

class angajat;
class carte;
class furnizor;
class client;

class carte
{
    string autor;
    char* titlu;
    int len_titlu;
    float pret;
    int numar_carti;
    static long total_carti;

public:
    friend istream& operator >> (istream& in, carte& c);
    friend ostream& operator << (ostream& out, const carte& c);

    int check_valabilitate();   //verifica valabilitatea
    long get_total_carti(){return total_carti;} //gettere pt informatii despre carte
    float get_pret(){return pret;}
    float get_cantitate(){return numar_carti;}
    char* get_titlu(){return titlu;}
    void set_cantitate(int );   // settere pentru informatii despre carte
    void set_pret(int );
    void set_autor(string );
    void set_titlu(char* );
    void set_len_titlu(int );
    friend class client;
    carte();    //constructor fara parametrii
    carte(char* titlu, int len_titlu, float pret, int numar_carti, string autor); //constructor cu toti parametrii
    carte(const carte& c); // copy constructor
    carte(int numar_carti, float pret); //constructor cu parametrii
    carte(string autor, char* titlu, int len_titlu ); //constructor cu parametrii
    ~carte(); //destructor

    carte operator=(const carte& c); //supraincarcare =
    carte operator -- (); //supraincarcare --a
    carte operator -- (int);//supraincarcare a--
    carte operator ++ ();//supraincarcare ++a
    carte operator ++ (int);//supraincarcare a++


    carte& operator+=(const carte& c)
    {
        pret=c.pret+pret;
        return *this;
    }

    carte operator+(carte c);
    carte operator-(carte c);

    bool operator<=(carte &c)
    {
        if (pret<=c.pret) return true;
        if (pret>c.pret) return false;
    }
    bool operator>=(carte &c)
    {
        if (pret>=c.pret) return true;
        if (pret<c.pret) return false;
    }

    bool operator==(carte c)
    {
        return pret==c.pret;
    }

    char operator[](int i);

};

long carte::total_carti=0;

char carte::operator[](int i)
{
    if (0<=i && i<this->len_titlu)
        return this->titlu[i];
    cout<<"Index gresit"<<endl;
}


carte carte::operator+(carte c)
{
    carte aux;
    aux.pret=c.pret+pret;
    return aux;
}

carte carte::operator-(carte c)
{
    carte aux;
    aux.pret=pret-c.pret;
    return aux;
}

carte carte::operator -- ()
{
    this->numar_carti--;
    total_carti--;
    return *this;
}


carte carte::operator -- (int)
{
    carte aux = *this;

    this->numar_carti--;
    total_carti--;
    return aux;
}

carte carte::operator ++ ()
{
    this->numar_carti++;
    total_carti++;
    return *this;
}


carte carte::operator ++ (int)
{
    carte aux = *this;

    this->numar_carti++;
    total_carti++;
    return aux;
}

carte::carte(string autor, char* titlu, int len_titlu)
{
    this->autor=autor;
    this->len_titlu=len_titlu;
    this->titlu=new char[len_titlu+1];
    strcpy( this->titlu, titlu);

}

istream& operator >> (istream& in, carte& c)
{
    char titlu_aux[100];

    cout<<"Titlu: ";
    in>>titlu_aux;
    if (c.titlu!=NULL)
        delete[]c.titlu;
    c.titlu=new char[strlen(titlu_aux)+1];
    strcpy(c.titlu, titlu_aux);
    cout<<"Autor: ";
    in>>c.autor;
    cout<<"Pret: ";
    in>>c.pret;
    cout<<"Numar carti: ";
    in>>c.numar_carti;

    c.total_carti=c.total_carti+c.numar_carti;

    return in;
}

ostream& operator << (ostream& out, const carte& c)
{
    out << "Titlu: " << c.titlu<<endl;
    out << "Autor: " << c.autor<<endl;
    out << "Pret: " << c.pret<<endl;

    return out;
}

int carte::check_valabilitate()
{
    if(numar_carti>0)
        return 1;
    else return 0;

}

void carte::set_cantitate(int m)
{
    numar_carti=m;
    total_carti=total_carti+numar_carti;
}

void carte::set_pret(int m)
{
    pret=m;
}

void carte::set_len_titlu(int m)
{
    len_titlu=m;
}

void carte::set_autor(string m)
{
    autor=m;
}

void carte::set_titlu(char m[100])
{
        if (this->titlu!=NULL)
            delete[]this->titlu;
        this->titlu=new char[strlen(m)+1];
        strcpy(this->titlu, m);
}


carte::carte()
{
    this->len_titlu=strlen("No_title")+1;
    titlu=new char[len_titlu];
    strcpy( this->titlu,"No_title");

    this->autor="Anonim";
    this->numar_carti=0;
    this->pret=0;

}


carte::carte(char* titlu, int len_titlu, float pret, int numar_carti, string autor)
{
    this->autor=autor;
    this->len_titlu=len_titlu;
    this->pret=pret;
    this->numar_carti=numar_carti;
    this->titlu=new char[len_titlu+1];
    strcpy( this->titlu, titlu);
    //total_carti=total_carti+numar_carti;
}

carte::carte(const carte &c)
{
    this->autor=c.autor;
    this->pret=c.pret;
    this->autor=c.autor;
    this->numar_carti=c.numar_carti;
    this->len_titlu=c.len_titlu;
    this->titlu=new char[c.len_titlu];
    for(int i=0; i<c.len_titlu; i++)
        this->titlu[i]=c.titlu[i];
    //c.total_carti=c.total_carti+c.numar_carti;

}


carte carte::operator=(const carte& c)
{
    if(this != &c)
        {
            if (this->titlu != NULL)
                delete[] this->titlu;

            this->autor=c.autor;
            this->pret=c.pret;
            this->autor=c.autor;
            this->numar_carti=c.numar_carti;
            this->len_titlu=c.len_titlu;
            this->titlu=new char[c.len_titlu];
            for(int i=0; i<c.len_titlu; i++)
                this->titlu[i]=c.titlu[i];

            //c.total_carti=c.total_carti+c.numar_carti;


        }
    return *this;

}

carte::~carte()
{
    if(this->titlu!=NULL)
        delete[] this->titlu;
}

class angajat
{

    int var1;
    string nume_librarie;
    static long total_carti_diferite;
    const int var4=0;


public:
        vector <carte> librarie;

    friend istream& operator >> (istream& in, angajat& a);
    friend ostream& operator << (ostream& out, const angajat& a);

    int get_total_carti_diferite()
    {
        return total_carti_diferite;
    }

    friend class client;

    void citire()
    {

        while(true)
            {
                string p;
                cout<<endl<<"Apasati 1 k sa adaugati sau altceva ca sa va opriti:";
                cin>>p;
                if (p=="1")
                    {
                        carte c;
                        cin>>c;
//                        cout<<"Titlu: ";
//                        char t[100];
//                        cin>>t;
//                        c.set_titlu(t);
//
//                        c.set_len_titlu(strlen(t));
//
//                        cout<<"Autor: ";
//                        string aut;
//                        cin>>aut;
//                        c.set_autor(aut);
//
//                        cout<<"Pret: ";
//                        double pre;
//                        cin>>pre;
//                        c.set_pret(pre);
//
//                        cout<<"Numar exemplare: ";
//                        int nr_ex;
//                        cin>>nr_ex;
//                        c.set_cantitate(nr_ex);
//                        cout<<endl;
//
                        librarie.push_back(c);
                        total_carti_diferite++;
                    }

                else return;
            }
    }


    string get_nume_librarie()
    {
        return nume_librarie;
    }

    angajat(); //
    angajat(string nume_librarie, int var1, vector <carte> librarie); //
    angajat(const angajat& a); //
    angajat(int var1, vector<carte> librarie); //
    angajat(string nume_librarie); //
    ~angajat(); //

    angajat operator=(const angajat& a); //

    bool operator<=(angajat &a) //
    {
        if (var1<=a.var1) return true;
        if (var1>a.var1) return false;
    }
    bool operator>=(angajat &a) //
    {
        if (var1>=a.var1) return true;
        if (var1<a.var1) return false;
    }

    bool operator==(angajat a) //
    {
        return var1==a.var1;
    }
};

long angajat::total_carti_diferite = 0;

angajat::angajat(string nume_librarie, int var1, vector<carte> librarie)
{
    this->nume_librarie=nume_librarie;
    this->var1=var1;
    this->librarie=vector<carte>();
}

angajat::angajat(string nume_librarie)
{
    this->nume_librarie=nume_librarie;
}

angajat::angajat()
{
    this->var1=0;
    this->nume_librarie="";
    this->librarie=vector <carte> ();
}

angajat::~angajat() {};

angajat::angajat(const angajat& a)
{
    this->var1=a.var1;
    this->nume_librarie=a.nume_librarie;
    this->total_carti_diferite=a.total_carti_diferite;
    this->librarie=a.librarie;
}

angajat angajat::operator=(const angajat& a)
{
    if(this!=&a)
        {
            this->var1=a.var1;
            this->nume_librarie=a.nume_librarie;
            this->total_carti_diferite=a.total_carti_diferite;
            this->librarie=a.librarie;
        }

    return *this;
}


istream& operator >> (istream& in, angajat& a)
{
    cout<<"var1:";
    in>>a.var1;

    return in;
}
ostream& operator << (ostream& out, const angajat& a)
{
    cout<<"var1:";
    out<<a.var1;

    return out;
}



class client
{

    string nume;
    string prenume;
    double buget;
    float total;
    int contor;


public:

    vector <carte> cosul;

    friend istream& operator >> (istream& in, client& c);
    friend ostream& operator << (ostream& in, client& c);

    float get_total()
    {
        return total;
    }
    void set_total(float k)
    {
        total=k;
    }
    friend class carte;
    int get_contor(){return contor;}
    void set_contor(int k){contor=k;}

    client(); //
    client(string nume, string prenume, double buget, vector <carte> cosul); //
    client(const client& c); //
    client(double buget, vector<carte> cosul); //
    client(string nume, string prenume); //
    ~client();

    client operator=(const client& c); //

    client operator+(carte &c)
    {
        client aux;
        aux.buget=buget+c.pret;
        return aux;
    }

    client operator-(carte &c)
    {
        client aux;
        aux.buget=buget-c.pret;
        return aux;
    }

    bool operator<=(client &c) //
    {
        if (buget<=c.buget) return true;
        if (buget>c.buget) return false;
    }
    bool operator>=(client &c) //
    {
        if (buget>=c.buget) return true;
        if (buget<c.buget) return false;
    }
    friend class angajat;
    bool operator==(client c) //
    {
        return buget==c.buget;
    }
};

client::client(string nume,  string prenume,double buget, vector<carte> cosul )
{
    this->nume=nume;
    this->prenume=prenume;
    this->buget=buget;
    this->cosul=cosul;
};

client::client(string nume, string prenume)
{
    this->nume=nume;
    this->prenume=prenume;
};

client::client(double buget, vector<carte> cosul)
{
    this->buget=buget;
    this->cosul=vector<carte>();
}

client client::operator=(const client& c)
{
    if(this != &c)
        {

            this->nume=c.nume;
            this->prenume=c.prenume;
            this->buget=c.buget;
            this->cosul=c.cosul;

        }
    return *this;
}

client::client()
{
    this->nume="Anonim";
    this->prenume="Anonim";
    this->buget=0.0;
    this->cosul=vector<carte> ();
}

client::client(const client& c)
{
    this->nume=c.nume;
    this->prenume=c.prenume;
    this->buget=c.buget;
    this->cosul=c.cosul;
}

client::~client() {};

istream& operator >> (istream& in, client& c)
{
    cout<<"buget:";
    in>>c.buget;

    return in;
}
ostream& operator << (ostream& out, client& c)
{
    cout<<"buget:";
    out<<c.buget;

    return out;
}



class furnizor{
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

    friend istream& operator>>(istream& in, furnizor& f);
    friend ostream& operator<<(ostream& out, const furnizor& f);

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

istream& operator>>(istream& in, furnizor& f)
{
    cout<<"var1: ";
    in>>f.var1;
    cout<<"var2: ";
    in>>f.var2;
    cout<<"var3: ";
    in>>f.var3;
    cout<<"var4: ";
    in>>f.var4;

    return in;

}

ostream& operator<<(ostream& out, const furnizor& f)
{
    cout<<"var1: ";
    out<<f.var1;
    cout<<"var2: ";
    out<<f.var2;
    cout<<"var3: ";
    out<<f.var3;
    cout<<"var4: ";
    out<<f.var4;

    return out;

}


int main()
{
    cout<<"-----------------------MENIU-------------------------"<<endl;
    cout<<"                        Pentru inchidere scrieati 420"<<endl;
    cout<<"                        In loc de spatii, folositi _"<<endl;
    cout<<"Selectare rol:"<<endl;
    cout<<"     1.ANGAJAT"<<endl;
    cout<<"     2.CLIENT"<<endl;
    int o;
    cin>>o;
    angajat vanzator("Karhte");
    if(o==420) return 0;
    if (o==1)
        {
            cout<<"Introduceti parola: ";
            string p="vreau_sa_trec";
            string l;
            cin>>l;
            if(l==p)
                {
                    cout<<"Ai trecut"<<endl;

                    cout << "--------------------------------Libraria " << vanzator.get_nume_librarie() << "--------------------------------\n";
                    cout << "                                         Pentru inchidere scrieti 69"<<endl;
                    cout << "1.Adaugati carti in librarie:"<<endl;
                    cout << "2.Verificare stoc"<<endl;
                    cout << "3.Aprovizionare"<<endl;
                    while(true)
                        {
                            cout<<"Optiune: ";
                            int pl;
                            cin>>pl;
                            if(pl==69) break;
                            if(pl==1)   vanzator.citire(); //introducerea cartilor inlibrarie
                            if(pl==2)   //verificarea numarului de carti
                                {
                                    carte c;
                                    cout<<c.get_total_carti()<<endl;
                                }
                            if(pl==3)   //aprovizionarea magazinului
                            {
                                for(int i=0;i<=vanzator.get_total_carti_diferite()-1;i++)
                                   vanzator.librarie[i].set_cantitate(vanzator.librarie[i].get_cantitate()+10);
                            }
                        }

                }
        }
    system("CLS");
    cout<<"S-a deschis libraria!"<<endl;
    cout<<"Cumparaturi placute!"<<endl;
    cout<<"Introdu bugetul:";
    double bani;
    cin>>bani;
    cout<<"Cautarea se face prin introducerea titlului"<<endl;
    client cumparator;
    cumparator.set_contor(0);
    cumparator.set_total(0);
    cout<<"Adauga carti in cos"<<endl;
    string input;
    while(true)
        {
            cout << "Press 1 to add, press anything else to stop: ";
            cin >> input;
            if(input == "1")
                {
                    char m[100];
                    cin>>m;
                    for(int i=0; i<=vanzator.get_total_carti_diferite()-1; i++)     //cautam cartea in librarie, daca este in librarie o punem in cosul
                        {
                            if(vanzator.librarie[i].get_cantitate()!=0)
                                {
                                    if (strcmp(m, vanzator.librarie[i].get_titlu())==0)
                                        {
                                            vanzator.librarie[i]--;
                                            cumparator.cosul.push_back(vanzator.librarie[i]);
                                        }
                                }

                        }
                        cumparator.set_contor(cumparator.get_contor()+1);   //crestem numarul total de carti

                }
            else break;
        }


    cout<<"Vreti sa eliminati carti din cos?"<<endl;
    cout<<"DA/NU"<<endl;

    string input_3;
    cin>>input_3;

    if(input_3=="DA"||input_3=="da"||input_3=="Da")
        {
            string input_2;
            while(true)
                {
                    cout << "Press 2 to remove, press anything else to stop: ";
                    cin >> input;
                    if(input=="2")
                        {
                            char m[100];
                            cin>>m;
                            for(int j=0; j<=vanzator.get_total_carti_diferite()-1; j++)
                                if (strcmp(m, vanzator.librarie[j].get_titlu())==0)
                                    vanzator.librarie[j]++;
                            for(int i=0; i<=cumparator.get_contor()-1; i++)     //daca vrem sa stergem o carte o resetam cu constructorul fara parametrii
                                if (strcmp(m, cumparator.cosul[i].get_titlu())==0)
                                    {
                                        cumparator.cosul[i]=carte();

                                    }
                        }
                    else break;

                }
        }
    system("CLS");
    cout<<"Rezumat comanda: "<<endl;

    for(int i=0; i<=cumparator.get_contor()-1; i++)
        {
            cumparator.set_total(cumparator.get_total()+cumparator.cosul[i].get_pret());
        }
    bani=bani-cumparator.get_total();
    if(bani<0){cout<<"Nu va permiteti cosul, la revedere!"; return 0;}
    cout<<"Totalul comenzii este de "<<cumparator.get_total()<<"lei si mai aveti la dizpozitie ";

    cout<< bani;
    cout<<" lei"<<endl;

    for(int i=0; i<=cumparator.get_contor()-1; i++)
        {
            if(strcmp("No_title", cumparator.cosul[i].get_titlu())!=0)  //daca cartea e in cos, o afisam
                {
                    cout<<cumparator.cosul[i];
                    cout<<endl;
                }
        }



    return 0;
}
