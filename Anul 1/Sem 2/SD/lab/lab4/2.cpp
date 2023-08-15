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

char *no_space(char* s)
{
    int i,j;
    i=j=0;
    while(s[i])
        {
            if(s[i]!=' ') s[j++]=s[i];
            i++;
        }
    s[j]='\0';
    return s;
}

int main()
{
    nod* head=new nod;
    nod* tail=new nod;
    head=tail=NULL;

    char expresie[105];
    cin.getline(expresie,100);
    no_space(expresie);

    int semn_paranteza=0;
    int grad_paranteza=0;
    int max_g=0;
    int i=1;
    int j;
    int v[100]= {1};

    if(expresie[0]=='(')
        {
            grad_paranteza++;
            semn_paranteza=1;
            v[grad_paranteza]=semn_paranteza;
            if(max_g<grad_paranteza) max_g=grad_paranteza;
        }

    if(expresie[i]==')') grad_paranteza--;

    while(expresie[i])
        {
            j=i-1;
            int numar=0;
            if(expresie[i]=='(')
                {
                    grad_paranteza++;
                    if(expresie[j]=='-') semn_paranteza=-1;
                    if(expresie[j]=='+') semn_paranteza=1;
                    v[grad_paranteza]=semn_paranteza;
                    if(max_g<grad_paranteza) max_g=grad_paranteza;
                }

            if(expresie[i]==')') grad_paranteza--;

            if(expresie[j]=='-' && strchr("1234567890", expresie[i])!=0 && strchr("1234567890", expresie[i+1])==0)
                {
                    numar=expresie[i]-'0';
                    numar=numar*(-1);
                }

            if((expresie[j]=='+' or expresie[j]=='(') && strchr("1234567890", expresie[i])!=0 && (strchr("1234567890", expresie[i+1])==0 or expresie[i+1]=='\0'))
                {
                    numar=expresie[i]-'0';
                }

            if(i==1)
                {
                    if(strchr("1234567890", expresie[0])!=0 && ( strchr("1234567890", expresie[1])==0 or expresie[1]!='\0'))
                        {
                            numar=expresie[0]-'0';
                        }
                }

            if(strchr("1234567890", expresie[j])!=0 && strchr("1234567890", expresie[i])!=0)
                {
                    numar=expresie[j]-'0';

                    numar=numar*10+(expresie[i]-'0');
                    i++;
                    while(strchr("1234567890", expresie[i])!=0 and expresie[i]!='\0')
                        {
                            numar=numar*10+(expresie[i]-'0');
                            i++;
                        }
                    if(expresie[j-1]=='-') numar=numar*-1;
                    i--;
                }

            if(numar!=0)
                {
                    Insert(head,tail,numar*v[grad_paranteza],grad_paranteza);
                }

            i++;
        }

    int sum=0;

    nod* in=new nod;
    in=head;
    nod* jn=new nod;
    jn=head;

    while(in!=NULL)
        {
            jn=in->next;
            while(jn!=NULL)
                {
                    if(in->grad<jn->grad)
                        {
                            swap(in->grad,jn->grad);
                            swap(in->data,jn->data);

                        }
                    jn=jn->next;
                }
            in=in->next;
        }
    nod* pn=new nod;
    pn=head;
    while(pn!=NULL)
        {
            sum=sum+pn->data;
            pn=pn->next;
        }
    cout<<endl<<sum<<endl;

    return 0;
}
