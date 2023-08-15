#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, i, j=0,m,p;
    cin>>n;
    cin>>m;
    int v[n];
    for(i=1;i<=n;i++)
        cin>>v[i];
    for(i=1;i<=n;i++)
        if (v[i]==m) {cout<<i; j=1; break;}
    if (j==0) cout<<"Nema";

    return 0;
}