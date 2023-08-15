#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;



int main() {
    int n;
    cin>> n;

    int x_st[n], //x>=
        y_st[n], //y>=
        x_dr[n], //x<=
        y_dr[n]; //y<=
    for (int i=0; i<n; i++)
        y_st[i]=-9999;

    for (int i=0; i<n; i++)
        y_dr[i]=9999;

    for (int i=0; i<n; i++)
        x_st[i]=-9999;

    for (int i=0; i<n; i++)
        x_dr[i]=9999;

    for(int i=0; i<n; i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if (a<0)
            x_st[i]=c/abs(a);

        else if (a>0)
            x_dr[i]=(c*-1)/abs(a);

        else
            if (b<0)
                y_st[i]=c/abs(b);
            else if (b>0)
                y_dr[i]=(c*-1)/abs(b);

    }

    int max_x_st = *max_element(x_st, x_st+n);
    int max_y_st = *max_element(y_st, y_st+n);
    int min_x_dr = *min_element(x_dr, x_dr+n);
    int min_y_dr = *min_element(y_dr, y_dr+n);

//    cout<<"x>= "<<max_x_st<<endl;
//    cout<<"x<= "<<min_x_dr<<endl;
//    cout<<"y>= "<<max_y_st<<endl;
//    cout<<"y<= "<<min_y_dr<<endl;


    if ( max_x_st > min_x_dr && max_y_st < min_y_dr)
        cout<<"VOID";

    else if (max_x_st !=-9999 && min_x_dr!=9999 && max_y_st !=-9999 && min_y_dr!=9999)
        cout<<"BOUNDED";

    else
        cout<<"UNBOUNDED";


    return 0;
}