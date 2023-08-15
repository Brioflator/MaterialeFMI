#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, i, j,m,p;
    cin>>n;
    int v[n];
    for(i=0;i<n;i++)
        cin>>v[i];

    for(i=0;i<n;i++)
    {
        m=9999;
        for(j=i;j<n;j++)
        {
            if(v[j]<m) m=v[j], p=j;
        }
        swap(v[p], v[i]);
    }

    for(i=0;i<n;i++)
        cout<<v[i]<<" ";


    return 0;
}