#include <bits/stdc++.h>

using namespace std;

int bin(int v[],int st,int dr, int x)
{
    if(dr>=st)
    {
        int m=(st+dr-1)/2;
        if (v[m]==x) return m;
        if (x>v[m]) return bin(v, m+1, dr, x);
        return bin(v, st, m-1, x);
    }
    return -1;

}

int main()
{
    int n, i, j=0,m,p;
    cin>>n;
    cin>>m;
    int v[n];
    for(i=1;i<=n;i++)
        cin>>v[i];
    cout<<bin(v,1,n,m);

    return 0;
}

/*

int bin(int v[],int st,int dr, int x)
{
    if(dr>=st)
    {
        int m=(st+dr-1)/2;
        if (v[m]==x) return m;
        if (x>v[m]) st=m+1;
        if (x<v[m]) dr=m-1;
        return bin(v, st, dr, x);
    }
    return -1;

}

*/