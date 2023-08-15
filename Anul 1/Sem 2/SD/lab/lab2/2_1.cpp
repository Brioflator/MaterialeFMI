#include <bits/stdc++.h>

using namespace std;

void heapify(int arr[], int i, int len)
{
    int maxi=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<len && arr[left]>arr[maxi])
        maxi=left;

    if(right<len && arr[right]>arr[maxi])
        maxi=right;

    if (maxi!=i) { swap(arr[maxi], arr[i]); heapify(arr,maxi,len); }
}

void heap(int v[], int n)
{
    //rearanjez vectorul ca sa mi construiesc heap ul
    for(int i=n/2-1;i>=0;i--) heapify(v,i,n);

    //extragere de elemente
    for(int i=n-1; i>0; i--)
    {
        //decapitez
        swap(v[0], v[i]);

        heapify(v,0,i);
    }
}

int main()
{
    int n, m,i,j;
    cin>>n;
    int v[n];
    for(i=0;i<n;i++)
        cin>>v[i];
    heap(v,n);

    for(i=0;i<n;i++) cout<<v[i]<<" ";

    return 0;
}
