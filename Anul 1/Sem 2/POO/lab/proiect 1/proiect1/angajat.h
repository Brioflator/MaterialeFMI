class angajat
{

    int var1;
    string nume_librarie;
    static long total_carti_diferite;
    const int var4=0;


public:

    friend istream& operator >> (istream& in, angajat& a);
    friend ostream& operator << (ostream& out, const angajat& a);

    int get_total_carti_diferite()
    {
        return total_carti_diferite;
    }

    friend class client;

    void ordonare()
    {
        for(long i=0; i<total_carti_diferite-1; i++)
            for(long j=i+1; j<total_carti_diferite; j++)
                {
                    if(this->librarie[i]>=this->librarie[j])
                        {
                            carte aux=librarie[i];
                            this->librarie[i]=librarie[j];
                            this->librarie[j]=librarie[i];

                        }
                }
        cout<<"Cartile au fost ordonate crescator in functie de pret."<<endl;
    }

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


    vector <carte> librarie;

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



