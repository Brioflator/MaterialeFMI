#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point{
    int x,y;
};

int square_distance(point a, point b) {return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}

//alta varianta de test de orientare
int cross_product(point a, point b)  {return a.x*b.y-b.x*a.y;}


int is_inside(point p, vector<point>&points)
{
    point pq = {p.x-points[0].x, p.y-points[0].y};
    point p1 = {points[points.size()-1].x-points[0].x, points[points.size()-1].y-points[0].y}; //caz special pt primul si ultimul punct
    point p2 = {points[1].x-points[0].x, points[1].y-points[0].y}; //caz special pt primul si al doilea punct

    if(!(cross_product(p1, pq)<=0 && cross_product(p2,pq)>=0)) return -1; // verificare ca punctul sa fie in dreapta primelor 2 laturi

    //cautare binara in nodurile poligonului
    int l = 0, r = points.size();
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        point cur = {points[mid].x-points[0].x, points[mid].y-points[0].y};
        if (cross_product(cur, pq)<0)
            r = mid;
        else
            l = mid;
    }


    if(l == points.size()-1)
    {
        if (square_distance(points[0], p) <= square_distance(points[0], points[l]))
            return 1;
        else
            return -1;
    }
    else
    {
        point l1 = {points[l+1].x-points[l].x, points[l+1].y-points[l].y};
        point l2 = {p.x-points[l].x, p.y-points[l].y};
        if(cross_product(l1,l2) == 0) //punctul este pe muchie
            return 0;
        else if(cross_product(l1,l2) > 0)
            return 1; //punctul este in interiorul poligonului
        else
            return -1; //punctul este in exteriorul poligonului
    }
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
            cout<<"BOUNDARY"<<endl;
        else
            cout<<"OUTSIDE"<<endl;

    return 0;
}