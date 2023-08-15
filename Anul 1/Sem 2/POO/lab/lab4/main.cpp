#include <iostream>
#include <list>
#include <iterator>



using namespace std;




class Produs
{




private:
    string nume;
    string dataExp;
    float pret;
public:
    Produs(string nume, string dataExp, float pret);
    Produs(const Produs& p);



    Produs& operator = (const Produs& produs);




    // prefixat
    Produs operator ++ ();



    //posfixat
    Produs operator ++ (int);



    friend ostream& operator << (ostream& out, const Produs& p);
    friend istream& operator >> (istream& in, Produs& p);



    ~Produs();




};



Produs::Produs(string nume="", string dataExp="", float pret=0): nume(nume), dataExp(dataExp), pret(pret)
{
}




Produs::Produs(const Produs& p)
{



    this->nume = p.nume;
    this->dataExp = p.dataExp;
    this->pret = p.pret;



}



// Supraincarcarea operatorului ++ pentru obiecte de tip Produs
Produs Produs::operator ++ ()
{
    this->pret++;
    return *this;
}




Produs Produs::operator ++ (int)
{



    Produs aux = *this;

    this->pret++;
    return aux;
}



// Supraincarcarea operatorului egal pentru obiecte de tip Produs
Produs& Produs::operator = (const Produs& produs)
{




    /**
    if(this == &produs) {
        cout << "SAME OBJ";
    }
    **/




    //if(this != &produs) {
    this->nume = produs.nume;
    this->dataExp = produs.dataExp;
    this->pret = produs.pret;
    //}
    return *this;
}




ostream& operator << (ostream& out, const Produs& p)
{
    out << "Numele produsului este : " << p.nume << endl;
    out << "Data expirarii produsului este : " << p.dataExp << endl;
    out << "Pretul produsului este : " << p.pret << endl;
    return out;
};





istream& operator >> (istream& in, Produs& p)
{




    cout << "Numele produsului este : ";
    in>>p.nume;
    cout << "Data expirarii produsului este : ";
    in >> p.dataExp;
    cout << "Pretul produsului este : ";
    in >> p.pret;



    return in;
}





Produs::~Produs()
{
}





class Magazin
{



private:
    string numeMagazin;





public:



    // todo getter
    list<Produs> listaProduse;



    Magazin(string numeMagazin, list<Produs> listaProduse);



    Magazin(const Magazin& m);





    friend istream& operator >> (istream& out, Magazin& p);
    friend ostream& operator << (ostream& out, Magazin& p);




};



Magazin::Magazin(string numeMagazin="", list<Produs> listaProduse = list<Produs>()): numeMagazin(numeMagazin),
    listaProduse(listaProduse)
{ };








ostream& operator << (ostream& out, Magazin& p)
{





    list<Produs>::iterator it;
    out << "-----MAGAZIN " << p.numeMagazin << "-----\n";
    out << "In magazin exista urm produse:\n";
    for (it = p.listaProduse.begin(); it != p.listaProduse.end(); ++it)
        cout << *it << "\n";



    return out;



}




istream& operator >> (istream& in, Magazin& p)
{
    cout << "Introduceti numele magazinului:";
    in>>p.numeMagazin;



    string input;
    while(true)
        {
            cout << "Introdu optiunea(1 add, anything else stop):";
            in >> input;
            if(input == "1")
                {
                    Produs prod = Produs();
                    in>>prod;
                    p.listaProduse.push_back(prod);
                }
            else break;



        }
    return in;
}





int main()
{




    Produs p = Produs("Banane", "25-03-2022", 3.5);




    cout << p;
    /**
    cout << p;





    cin >> p;
    cout<<"\n\n\n";
    cout<<p;



    **/




    Magazin magazin = Magazin("Mega Image Dorobanti");



    cin >> magazin;



    cout<<"\n\n\n";



    cout << magazin;




    return 0;
}
