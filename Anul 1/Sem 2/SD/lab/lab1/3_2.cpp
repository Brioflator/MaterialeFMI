#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m,i,j;
    cin>>n;
    int om[n][2];
    for(i=1;i<=n;i++)
    {
        cin>>om[i][0]>>om[i][1];
    }

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            {
                if(om[i][0]>om[j][0]) {swap(om[i][0], om[j][0]); swap(om[i][1], om[j][1]);}
                if(om[i][0]==om[j][0] && om[i][1]>om[j][1]) {swap(om[i][0], om[j][0]); swap(om[i][1], om[j][1]);}

            }
    }

    int k=1;
    j=0;
    for(i=1;i<=n;i++)
    {
        if(om[i][0]>=om[i+1][0] && om[i][1]>=om[i+1][1]) k++;
        else
        {
            if (k>j) j=k;
            k=1;
        }
    }
    cout<<j;
    return 0;
}
