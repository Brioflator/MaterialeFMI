#include <bits/stdc++.h>

using namespace std;

struct nod
{
    int data;
    nod* next;
};

void afisare(nod* n)
{
    while(n!=NULL)
        {
            cout<<n->data<<" ";
            n=n->next;
        }
}

void nou_head(nod* &head, int x)
{
    nod* p=NULL;
    p=new nod;

    p->data=x;
    p->next=head;

    head=p;
}

void stergere_head(nod* &head)
{
    nod* aux=head;
    head=head->next;
    delete aux;
}

void stergere_lista(nod* &head)
{
    while(head!=NULL)
        stergere_head(head);
    cout<<endl<<"Lista stearsa"<<endl;
}

void stergere(nod* &prev)
{
    nod* aux=prev->next;
    prev->next=aux->next;
    delete aux;
}

void inserare(nod* prev, int x)
{
    nod* n=new nod();

    if (prev == NULL)
        {
            cout << "Nodul anterior nu poate sa fie NULL";
            return;
        }

    n->data= x;
    n->next=prev->next;

    prev->next=n;
}

//void adaugare_sortata(nod* &head, int n)
//{
//    nod* elem=new nod;
//    elem->data=x;
//    elem->urm=NULL;
//}

void nou_tail(nod* &tail, int x)
{
    nod* p=NULL;
    p=new nod;

    p->data=x;
    p->next=tail->next;

    if (tail->next==NULL)
    {
        tail->next=p;
    }
}

int main()
{
    nod* head=new nod;
    nod* tail=new nod;

    //head=NULL;
    //tail=NULL;

    cin>>head->data;
    cin>>tail->data;

    head->next=tail;
    tail->next=NULL;

    if(head->data> tail->data) swap(head->data, tail->data);

    int maxi=tail->data;

//    int n;
//    cin>>n;
//    if(n<head->data) nou_head(head, n);
//    else
//    {
//        if(maxi>n) inserare(head, n);
//        else maxi=n, inserare(tail, n);
//    }

    while(true)
        {
            int t;
            cout<<"1 ca sa continuati: ";
            cin>>t;
            if (t==1)
                {
                    nod* temp=new nod;
                    int n;
                    cin>>n;
                    temp->data=n;
                    temp->next=head;
                    if(n<head->data) nou_head(head,n);
                    else
                        {
                            while(temp->next!=NULL&&temp->next->data<n)
                                temp=temp->next;
                            inserare(temp,n);
                        }
                    if(maxi<n) maxi=n;

                }
            else break;

        }

    afisare(head);

    nod* temp=new nod;
    int n;
    cin>>n;
    temp->data=n;
    temp->next=head;
    if(n==head->data) stergere_head(head);
    else
        {
            while(temp->next!=NULL&&temp->next->data!=n)
                temp=temp->next;
            stergere(temp);
        }

    afisare(head);
    stergere_lista(head);

    return 0;
}
