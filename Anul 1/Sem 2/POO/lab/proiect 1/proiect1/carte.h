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

    int check_valabilitate();
    long get_total_carti(){return total_carti;}
    float get_pret(){return pret;}
    float get_cantitate(){return numar_carti;}
    char* get_titlu(){return titlu;}
    void set_cantitate(int );
    void set_pret(int );
    void set_autor(string );
    void set_titlu(char* );
    void set_len_titlu(int );
    friend class client;
    carte();
    carte(char* titlu, int len_titlu, float pret, int numar_carti, string autor);
    carte(const carte& c);
    carte(int numar_carti, float pret);
    carte(string autor, char* titlu, int len_titlu );
    ~carte();

    carte operator=(const carte& c);
    carte operator -- ();
    carte operator -- (int);
    carte operator ++ ();
    carte operator ++ (int);

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
