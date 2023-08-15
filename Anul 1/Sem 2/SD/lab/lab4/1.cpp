#include <bits/stdc++.h>

using namespace std;

struct nod
{
    int data;
    int grad;
    nod* next;
};

void afisare(nod* n)
{
    while(n!=NULL)
        {
            cout<<n->data<<" "<<n->grad<<endl;
            n=n->next;
        }
}

void Delete(nod* &head)
{
    if(head==NULL)
    {
        cout<<"Underflow";
    }
    else
    {
        int N=head->data;
        int G=head->grad;
        nod* temp=head;
        head=head->next;
        delete temp;
    }


}

void Insert(nod* &head, nod* &tail, int n, int g)
{
    nod* p=new nod();
    if(p==NULL)
    {
        cout<<"Overflow";
    }
    else
    {
        p->data=n;
        p->grad=g;
        p->next=NULL;
        if(tail==NULL) head=p;
        else tail->next=p;
        tail=p;
    }



}

int main()
{
    nod* head=new nod;
    nod* tail=new nod;

    cin>>head->data;
    cin>>head->grad;
    cin>>tail->data;
    cin>>tail->grad;

    head->next=tail;
    tail->next=NULL;


    while(true)
        {
            int t;
            cout<<"1 ca sa continuati: ";
            cin>>t;
            if (t==1)
                {
                    int n, g;
                    cin>>n>>g;
                    Insert(head,tail,n,g);

                }
            else break;

        }

    afisare(head);

    nod* i=new nod;
    i=head;
    nod* j=new nod;
    j=head;

    while(i!=NULL)
        {
            j=i->next;
            while(j!=NULL)
            {
                if(i->grad>j->grad)
                {
                    swap(i->grad,j->grad);
                    swap(i->data,j->data);

                }
                j=j->next;
            }
            i=i->next;
        }

    afisare(head);

    return 0;
}
