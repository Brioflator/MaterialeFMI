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
