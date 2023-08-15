#include <iostream>

using namespace std;

void quick (int v[100001], int st, int dr)
{
  int i=st,j=dr;
  int pi=v[(st+dr)/2];
  while(i<=j)
  {
    while(v[i]>pi)
      i++;
    while(v[j]<pi)
      j--;
    if(i<=j)
    {
      swap(v[i],v[j]);
      i++;
      j--;
    }
  }
  if(st<j) quick(v,st,j);
  if(i<dr) quick(v,i,dr);
}

int main()
{
    int n,i,v[100001];
    cin>>n;
    for(i=1;i<=n;i++)
      cin>>v[i];
    quick(v,1,n);
    for(i=1;i<=n;i++)
      cout<<v[i]<<" ";
    return 0;
}
