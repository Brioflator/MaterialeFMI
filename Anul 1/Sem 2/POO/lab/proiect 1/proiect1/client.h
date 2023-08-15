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

