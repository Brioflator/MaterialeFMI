#include <bits/stdc++.h>

using namespace std;

class Vector{

    int n;
    int *v;
    int max_len;

public:

    int get_poz(int m){
        return v[m];
    }

    void set_len(int m){
    n=m;
    }

    int get_len(){
    return n;
    }

    void get_vecc(){
    for (int j=0;j<n;j++)
        cout<<v[j]<<" ";
    }

    void append(int m){
        if(n+1>max_len){
            max_len+=4;
            int *p;
            p=new int(max_len);
            for(int i=0;i<n;i++){
                p[i]=v[i];
            }
            delete v;
            v=p;
            v[n++]=m;
        }
        else v[n++]=m;
    }

    void pop(int m){
        if (n==0) {cout<<"Empty array"; return;}
        n--;
    }

    Vector(Vector &m)
    {
        n=m.n;
        max_len=m.max_len;
        v=new int[max_len];
        for(int i=0;i<n;i++){v[i]=m.v[i];}
    }

    Vector()
    {
        n=0;
        max_len=1000;
        v=new int[max_len];
    }

    Vector(int n, int vctor[100])
    {
        v=new int[n];
        this->n=n;
        max_len=n;
        for(int p=0; p<this->n; p++)
            v[p]=vctor[p];
    }

    ~Vector(){
        delete v;
        n=0;
        max_len=0;
    }

};

int main()
{
    Vector k;
    k.append(1);
    k.get_vecc();

    return 0;
}
