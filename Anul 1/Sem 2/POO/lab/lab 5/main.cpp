#include <iostream>
#include <list>
#include <iterator>
#include <vector>
using namespace std;


class Joc
{
private:
    string numeJoc;
    string dezvoltator;
    double pret;
    bool multiplayer;

public:
    Joc();
    Joc(const Joc& joc);
    Joc(string numeJoc, string dezvoltator,double pret,bool multiplayer);
    Joc operator = (const Joc& joc);

    string getNume()
    {
        return this->numeJoc;
    }

    Joc operator ++ ();
    Joc operator ++ (int);

    Joc operator += (float x);

    bool operator < (const Joc& joc);

    bool operator == (const Joc& joc);


    friend ostream& operator << (ostream& os, const Joc& joc);
    friend istream& operator >> (istream& is, Joc& joc);

};


Joc::Joc():numeJoc(""),dezvoltator(""), pret(0), multiplayer(false)
{
}

Joc::Joc(const Joc& joc)
{
    this->numeJoc = joc.numeJoc;
    this->dezvoltator = joc.dezvoltator;
    this->pret = joc.pret;
    this->multiplayer = joc.multiplayer;
}

Joc::Joc(string numeJoc, string dezvoltator,double pret,bool multiplayer)
{
    this->numeJoc =numeJoc;
    this->dezvoltator = dezvoltator;
    this->pret = pret;
    this->multiplayer = multiplayer;
}

Joc Joc::operator = (const Joc& joc)
{
    if(this != &joc)
    {
        this->numeJoc = joc.numeJoc;
        this->dezvoltator = joc.dezvoltator;
        this->pret = joc.pret;
        this->multiplayer = joc.multiplayer;
    }

    return *this;
}

Joc Joc::operator += (float x)
{
    this->pret += x;
    return *this;
}

//prefixat
Joc Joc::operator ++ ()
{
    this->pret++;
    return *this;
}

//posfixat
Joc Joc::operator ++ (int)
{
    Joc aux = *this;
    this->pret++;
    return aux;
}

bool Joc::operator < (const Joc& joc)
{
    return this->pret < joc.pret;
}

bool Joc::operator == (const Joc& joc)
{
    if(this->pret != joc.pret) return false;
    if(this->dezvoltator != joc.dezvoltator) return false;
    if(this->multiplayer != joc.multiplayer) return false;
    if(this->numeJoc != joc.numeJoc) return false;

    return true;
}


ostream& operator << (ostream& os, const Joc& joc)
{

    os << "Nume joc: " << joc.numeJoc << endl;
    os <<"Nume dezv: " << joc.dezvoltator<< endl;
    os <<"Pret " << joc.pret<< endl;
    os << "Este multiplayer: " <<joc.multiplayer<< endl;

    return os;
}

istream& operator >> (istream& is, Joc& joc)
{
    cout << "Nume joc: ";
    is >> joc.numeJoc;
    cout << "Nume dezv: ";
    is >> joc.dezvoltator;
    cout << "Pret: ";
    is >> joc.pret;
    cout << "Este multiplayer[1/0]: ";
    is >> joc.multiplayer;
    return is;
}

class GameStore
{

private:
    Joc* listaJocuri;
    int nrJocuri;
    list<int> nrExemplare;


public:
    GameStore();
    GameStore(const GameStore& gameStore);
//GameStore(Joc* listaJocuri, int nrJocuri, list<int> nrJocuri);

    GameStore operator = (const GameStore& gameStore);



    GameStore operator + (const Joc& joc);


    void setNrExemplare(int idx, int nrEx)
    {
        list<int>::iterator it = this->nrExemplare.begin();
        advance(it, idx);
        *it = nrEx;
    }
    bool operator == (string numeJoc){
        for(int i=0; i<this->nrJocuri;i++)
            if(this->listaJocuri[i].getNume()==numeJoc)
                return true;
        return false;

    }
    void sorteazaJocurileDupaPret() {
        for(int i=0; i<this->nrJocuri-1; i++)
            for(int j=i+1; j<this->nrJocuri; j++){
                if (!(this->listaJocuri[i] < this->listaJocuri[j])){
                    Joc aux = this->listaJocuri[i];
                    this->listaJocuri[i] = listaJocuri[j];
                    this->listaJocuri[j] = aux;
                    list<int>::iterator it1 = this->nrExemplare.begin();
                    list<int>::iterator it2 = this->nrExemplare.begin();
                    advance(it1, i);
                    advance(it2, j);
                    int aux2 = *it1;
                    *it1 = *it2;
                    *it2 = aux2;
                }

            }
    }
    void setPretJoc(Joc& joc, float newPret) {
        joc += newPret;
    }
    int getNrExemplarePentruJoc(int idx){

        list<int>::iterator it = this->nrExemplare.begin();
        advance(it, idx);
        return *it;
    }

int getIndexJoc (string numeJoc)
    {
        for(int i=0; i<this->nrJocuri;i++)
            if(this->listaJocuri[i].getNume()==numeJoc)
                return i;
        return -1;
    }

    friend ostream& operator << (ostream& os, GameStore& gameStore);

    friend istream& operator >> (istream& is, GameStore& gameStore);

 Joc& operator[](int index){

    if(index>=0 && index<this->nrJocuri)
        return this->listaJocuri[index];
    cout<<"Index gresit";

 }

};


ostream& operator << (ostream& os,GameStore& gameStore)
{


    list<int>::iterator it = gameStore.nrExemplare.begin();
    os << "Numar jocuri: " << gameStore.nrJocuri << "\n";

    os << "------------JOCURI------------\n";
    for(int i=0; i<gameStore.nrJocuri; i++)
    {

        os << "------------JOC NR " << i << " ------------\n";
        os << gameStore.listaJocuri[i];

        os << "Cantitate : " << *(it);
        advance(it, 1);
        os << "--------------------------------------\n";
    }

    return os;
}


istream& operator >> (istream& is, GameStore& gameStore)
{


    cout << "Numar jocuri: ";
    is >> gameStore.nrJocuri;
    int nrEx;
    if(gameStore.listaJocuri!=NULL)
        delete[] gameStore.listaJocuri;

    gameStore.listaJocuri = new Joc[gameStore.nrJocuri];
    for(int i=0; i<gameStore.nrJocuri; i++)
    {

        is >> gameStore.listaJocuri[i];
        cout << "Numar exemplare: ";
        is >> nrEx;
        gameStore.nrExemplare.push_back(nrEx);
    }

    return is;

}

GameStore GameStore::operator + (const Joc& joc)
{
    Joc* aux=NULL;

    if(this->listaJocuri!=NULL)
    {
        aux=new Joc[this->nrJocuri];
        for(int i=0; i<this->nrJocuri; i++)
        {
            aux[i] = this->listaJocuri[i];
        }

        delete[] this->listaJocuri;

    }


    this->nrJocuri++;
    this->listaJocuri = new Joc[this->nrJocuri];

    for(int i=0; i<this->nrJocuri-1; i++)
    {
        this->listaJocuri[i]= aux[i];
    }

    this->listaJocuri[this->nrJocuri-1]=joc;

    this->nrExemplare.push_back(0);
    if(aux!=NULL)
    {

        delete[] aux;
    }

    return *this;

}




GameStore::GameStore():listaJocuri(NULL), nrJocuri(0),nrExemplare({})
{
}
GameStore::GameStore(const GameStore& gameStore)
{

    this->nrJocuri = gameStore.nrJocuri;
    this->listaJocuri = new Joc[this->nrJocuri];
    for(int i=0; i<this->nrJocuri; i++)
    {
        this->listaJocuri[i] = gameStore.listaJocuri[i];
    }

    this->nrExemplare = gameStore.nrExemplare;
}


GameStore GameStore::operator = (const GameStore& gameStore)
{

    if(this != &gameStore)
    {

        this->nrJocuri = gameStore.nrJocuri;
        if(this->listaJocuri) // Joc*
        {
            delete[] this->listaJocuri;
        }
        this->listaJocuri = new Joc[this->nrJocuri];
        for(int i=0; i<this->nrJocuri; i++)
        {
            this->listaJocuri[i] = gameStore.listaJocuri[i];
        }

        this->nrExemplare = gameStore.nrExemplare; // list<int>
    }
    return *this;
}


int main()
{



    GameStore gs = GameStore();


    string option;
    int idx;


    while(true)
    {

        cout << "Comenzi(introdu exit pt a iesi):\n"
             << "1. Adaugare joc\n"
             << "2. Modificare nr exemplare\n"
             << "3. Modifica pret joc\n"
             << "4. Afisare jocuri crescator dupa pret\n";


        cin >> option;
        if(option == "exit")
        {
            break;
        }

        if(option == "1")
        {
            Joc j = Joc();
            cin >> j;
            gs = gs + j;
        }
        else if(option == "2")
        {
           string numeJoc;
           cin>>numeJoc;
           if(gs==numeJoc){

            cout<<"\n\nJocul: \n";
            cout<<gs[gs.getIndexJoc(numeJoc)];
            cout<<"Numar exemplare: "<<gs.getNrExemplarePentruJoc(gs.getIndexJoc(numeJoc))<<"\n";
            int newStock=0;

            cout<<"\nIntroduceti noul stock: ";
            cin>>newStock;
            gs.setNrExemplare(gs.getIndexJoc(numeJoc),newStock);
            cout<<"After: \n";
            cout<<gs[gs.getIndexJoc(numeJoc)];
            cout<<"Numar exemplare: "<<gs.getNrExemplarePentruJoc(gs.getIndexJoc(numeJoc))<<"\n";

           }
        }
        else if (option == "3") {
            string numeJoc;
           cin>>numeJoc;
               if(gs==numeJoc){

                cout<<"\n\nJocul: \n";
                cout<<gs[gs.getIndexJoc(numeJoc)];

                int newPret=0;

                cout<<"\nIntroduceti noul pret: ";
                cin>>newPret;
                gs.setPretJoc(gs[gs.getIndexJoc(numeJoc)], newPret);
                cout<<"After: \n";
                cout<<gs[gs.getIndexJoc(numeJoc)];
            }

        }
        else if (option == "4") {
            gs.sorteazaJocurileDupaPret();
            cout << gs;
        }



    }


    return 0;
}
