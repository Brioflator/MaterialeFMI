#include <bits/stdc++.h>

using namespace std;
// bool pt a opri sortarea mai devreme

int main()
{
    int n, i, cn;
    cin>>n;
    cn=n;
    int v[n];
    for(i=0;i<n;i++)
        cin>>v[i];
    while(n>0)
    {
        i=1;
        while(i<n)
        {
            if (v[i]<v[i-1]){swap(v[i], v[i-1]);}
            i++;
        }
        n--;
    }

    for(i=0;i<cn;i++)
        cout<<v[i]<<" ";


    return 0;
}
