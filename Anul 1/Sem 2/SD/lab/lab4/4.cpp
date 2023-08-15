#include <iostream>

using namespace std;

int xp, ip, jp;

struct nod
{
    int data;
    int i;
    int j;
    nod *next;
};

void afisare(nod *&peak)
{
    nod *n = new nod;
    if (peak == NULL)
        cout << "Stiva goala " << endl;
    else
    {
        n = peak;
        while (n != NULL)
        {
            cout << n->data << " " << endl;
            n = n->next;
        }
    }
}

// void Delete(nod* &head)
//{
//     if(head==NULL)
//         {
//             cout<<"Underflow";
//         }
//     else
//         {
//             int N=head->data;
//             int G=head->grad;
//             nod* temp=head;
//             head=head->next;
//             delete temp;
//         }
//
//
// }
//
// void Insert(nod* &head, nod* &tail, int n, int g)
//{
//     nod* p=new nod();
//     if(p==NULL)
//         {
//             cout<<"Overflow";
//         }
//     else
//         {
//             p->data=n;
//             p->grad=g;
//             p->next=NULL;
//             if(tail==NULL) head=p;
//             else tail->next=p;
//             tail=p;
//         }
//
//
//
// }

void Push(nod *&peak, int n, int i, int j)
{
    nod *p = new nod();
    if (p == NULL)
    {
        cout << "Overflow" << endl;
    }
    else
    {
        p->data = n;
        p->i = i;
        p->j = j;
        p->next = peak;
        peak = p;
    }
}

void Pop(nod *&peak)
{
    nod *tmp;
    if (peak == NULL)
    {
        cout << "Underflow" << endl;
    }
    else
    {
        tmp = peak;
        xp = tmp->data;
        ip = tmp->i;
        jp = tmp->j;
        peak = peak->next;
        delete tmp;
    }
}

int main()
{
    nod *top = new nod;
    top = NULL;

    int a[105][105] = {0};

    int n, grad;
    cin >> n;
    grad = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];


    for (int i = 0; i <= n+1; i++)
        for (int j = 0; j <= n+1; j++)
        {
            if (a[i][j] == 1)
            {
                if (a[i][j + 1] == 1 || a[i + 1][j] == 1 || a[i][j - 1] == 1 || a[i - 1][j] == 1)
                    Push(top, a[i][j], i, j);

                if (a[i][j + 1] == 0 && a[i + 1][j] == 0)
                {
                    grad++;
                    Push(top, a[i][j], i, j);

                    while (top != NULL)
                    {
                        Pop(top);
                        a[ip][jp] = grad;
                    }
                }
            }
        }

    cout << endl;
    for (int i = 1; i <= n; i++)

    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    return 0;
}
