#include <bits/stdc++.h>

using namespace std;

int xp;

struct nod
{
    int data;
    nod* next;
};

void afisare(nod* &peak)
{
    nod* n=new nod;
    if(peak==NULL) cout<<"Stiva goala "<<endl;
    else
    {
        n=peak;
        while(n!=NULL)
        {
            cout<<n->data<<" "<<endl;
            n=n->next;
        }
    }

}

void Push(nod* &peak, int n)
{
    nod* p=new nod();
    if(p==NULL)
        {
            cout<<"Overflow"<<endl;
        }
    else
        {
            p->data=n;
            p->next=peak;
            peak=p;
        }
}

void Pop(nod* &peak)
{
    nod* tmp;
    if(peak==NULL)
    {
        cout<<"Underflow"<<endl;
    }
    else
    {
        tmp=peak;
        xp=tmp->data;
        peak=peak->next;
        delete tmp;
    }
}


int main()
{
    nod* top=new nod;
    top=NULL;

    int pini;
    int pr[1005];
    int f[1005]={0};
    int k=1;
    cin>>pini;

    for(int i=1; i<=pini;i++) cin>>pr[i];

    for(int i=1; i<=pini;i++)
    {
        if(f[pr[i]]==1)
        {
            Pop(top);
            cout<<xp<<" "<<pr[i]<<endl;
            if (xp!=pr[i]) k=0;
        }
        if(f[pr[i]]==0) f[pr[i]]++, Push(top, pr[i]);

    }

    if(k==1) cout<<"Config valid";
    else cout<<"Config invalid";

    return 0;
}
