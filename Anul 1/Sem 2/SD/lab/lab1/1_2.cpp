#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, i, ci, j;
    cin>>n;
    int v[n];
    for(i=0;i<n;i++)
        cin>>v[i];

    //incepe de la 1 deoarece subsecventa are lungimea !=0
    for(i=1;i<n;i++)
    {
        j=v[i]; //fac o copie a elementului pe care urmeaza sa l introduc in subsecventa
        ci=i-1;
        // mut toate elem care sunt mai mari decat j cu o pozitie la dreapta
        while(ci>=0 && v[ci]>j)
        {
            v[ci+1]=v[ci];
            ci--;
        }
        //introduc elem pe pozitia corecta in subsecventa
        v[ci+1]=j;
    }

    for(i=0;i<n;i++)
        cout<<v[i]<<" ";


    return 0;
}