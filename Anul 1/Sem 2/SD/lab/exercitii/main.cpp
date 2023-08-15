#include <bits/stdc++.h>

using namespace std;


class Node
{
public:
    //in d tinem caracterul, iar in f, frecventa
    char d;
    int f;

    Node* L; //tinem in L copilul din stanga al nodului curent
    Node* R; //tinem in R copilul din dreapta al nodului curent


    Node(char d, int f) //constructorul cu care initializam nodul curent
    {
        this->d=d;
        this->f=f;
        R=L=NULL;
    }

};

class cmp
{
public:
    //suprascriu operatorul() a.i. sa mi arate prioritatea dintre doua noduri din arbore in functie de frecventa
    bool operator()(Node* m, Node* n) { return m->f > n->f; }
};

//generarea Codarii Huffman
Node* generator(priority_queue<Node*, vector<Node*>, cmp> PQ)
{
    // rulam pana mai ramane un singur nod in priority queue
    while(PQ.size()!=1)
    {
        // scot nodul cu cea mai mica frecventa
        Node* l= PQ.top();
        PQ.pop();

        // scot nodul cu cea mai mica frecventa
        Node* r= PQ.top();
        PQ.pop();

        //am scos ultimile 2 noduri cu cea mai mica frecventa din priority queue
        // urmeaza sa formez un nod interior format din suma frecventelor ultimelor 2 noduri
        // cum nu vrem sa afisam nodurile interioare, o sa le notam cu "@" (ne intereseaza doar frecventa pe care acestea o au)
        Node* N=new Node('@', l->f+r->f);
        N->L=l;
        N->R=r;

        // adaugam nodul interior creat in priority queue
        PQ.push(N);

    }
    return PQ.top();
}

void afisare_cod(Node* root, int c[], int vf)
{
    // nodul din stanga ia valoare 0 si reapelez
    if(root->L)
    {
        c[vf]=0;
        afisare_cod(root->L, c, vf+1);
    }

    // nodul din dreapta ia valoare 1 si reapelez
    if(root->R)
    {
        c[vf]=1;
        afisare_cod(root->R, c, vf+1);
    }

    //daca am ajuns la frunza, atunci afisam si root->d si codul pe care l-am generat in vectorul c
    if(!root->L && !root->R)
    {
        cout<<root->d<<" ";
        for(int i=0;i<vf; i++) cout<<c[i];
        cout<<endl;
    }
}

void Cod_Huffman(char ch[], int fr[], int len)
{
    //imi deeclar PQ, folosindu-ma de comparatorul custom de mai sus
    priority_queue<Node*, vector<Node*>, cmp> PQ;

    //punem datele in PQ
    for(int i=0; i< len; i++)
    {
        Node* nn= new Node(ch[i], fr[i]);
        PQ.push(nn);
    }

    //generam codarea
    Node* root=generator(PQ);

    //afisam codurile
    int v[50], vf=0;
    afisare_cod(root, v, vf);
}


int main()
{
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    Cod_Huffman(data, freq, size);


    return 0;
}
