#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point{
    int x,y;
};

int is_inside(point p, vector<point>&points)
{
    int n = points.size();
    int i, j, c = 0;
    for (i = 0, j = n-1; i < n; j = i++)
    {
        if(((points[i].y>p.y) != (points[j].y>p.y)) &&(p.x*points[i].y+p.y*points[j].x+points[i].x*points[j].y-points[i].y*points[j].x-points[j].y*p.x-points[i].x*p.y==0)) //verificare daca punctul este pe muchie
            return -1;
        if ( ((points[i].y>p.y) != (points[j].y>p.y)) &&    // prima conditie verifica daca punctul se afla in "inaltimea" muchiei
        (p.x < (points[j].x-points[i].x) * (p.y-points[i].y) / (points[j].y-points[i].y) + points[i].x) ) // a doua conditie verifica daca punctul se afla in stanga muchiei
            c++;

    }
    return c%2;
}


int main()
{

    int n,m;

    //citire puncte poligon
    cin>>n;
    vector<point>points(n);
    for(int i=0;i<n;i++)
        cin>>points[i].x>>points[i].y;

    //citire puncte test
    cin>>m;
    vector<point>test(m);
    for(int i=0;i<m;i++)
        cin>>test[i].x>>test[i].y;

    for(int i=0;i<m;i++)
        if(is_inside(test[i], points)==1)
            cout<<"INSIDE"<<endl;
        else if (is_inside(test[i], points)==0)
            cout<<"OUTSIDE"<<endl;
        else
            cout<<"BOUNDARY"<<endl;

    return 0;
}