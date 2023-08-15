#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, m,i,j;
    cin>>n;
    cin>>m;
    int v[n+m], a[n+m];
    for(i=0;i<n;i++)
        cin>>v[i];

    int f[m];
    for(i=0;i<m;i++)
        cin>>f[i];

    i=n, j=m;
    int k=n+m+1;
    while(i>=0&&j>=0)
    {
        if(v[i]>=f[j]) v[k--]=v[i], i--;
        else v[k--]=f[j], j--;

    }

    while(i>=0) {v[k]=v[i]; k--; i--;}

    while(j>=0) {v[k]=f[j]; k--; j--;}

    for(i=0;i<n+m;i++) cout<<v[i]<<" ";

    return 0;
}
