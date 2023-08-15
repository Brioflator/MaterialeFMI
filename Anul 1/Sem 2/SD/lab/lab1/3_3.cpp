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
    int k=0;
    for(i=1;i<=n;i++)
        if (v[i]==m) {j=1; break;}
        else k++;
    if (j==0) cout<<"Nema";
    else cout<<k;

    return 0;
}