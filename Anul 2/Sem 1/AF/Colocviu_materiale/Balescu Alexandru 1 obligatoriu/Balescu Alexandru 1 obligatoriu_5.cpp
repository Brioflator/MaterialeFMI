#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

// Se dă o rețea neorientată cu n noduri și o listă de noduri reprezentând puncte de control pentru rețeaîn fișierul graf.in, în formatul precizat la începutul laboratorului;
// în plus, pe ultima linie din fișier se află punctele de control separate prin spațiu.
// Să se determine pentru fiecare nod din rețea distanța până la cel mai apropiat punct de control de acesta.
// În fișierul graf.out se vor afișa pentru fiecare nod de la 1 la n acestedistanțe separate prin spațiu.

// pt crearea listei de adiacenta
void add_edge(vector<long int> adiacenta[], long int a, long int b)
{
    adiacenta[a].push_back(b);
    adiacenta[b].push_back(a);
}

// citirea muchiilor
void read(vector<long int> adiacenta[], long int &n, long int &m)
{
    long int x, y;
    for (long int i = 1; i <= m; i++)
        do
        {
            fin >> x >> y;
            add_edge(adiacenta, x, y);
        } while (x == y || x > n || x < 1 || y > n || y < 1); // prevenirea datelor eronate
}

// parcurgem graful cu ajutorul unui bfs
// datorita modului de functionare a bfs ului, la fiecare pas putem sa asociem o distanta care reprezlong inta distanta unui nod fata de nodul din care porneste bfs ul
//  spre ex, elem din lista de adiacenta a unui nod au distanta =1

long int min_dist_bfs(vector<long int> adiacenta[], long int u, long int v, long int n)
{
    // vectorul de vizitat
    vector<bool> vizitat(n + 1, 0);

    // vectorul in care o sa fie pastrate distantele relative fata de nodul u
    vector<long int> distanta(n + 1, 0);

    queue<long int> que;
    // distanta fata de nodul de start este 0
    distanta[u] = 0;

    que.push(u);
    // marcam nodul curent ca fiind vizitat
    vizitat[u] = true;

    while (!que.empty())
    {
        // luam pe rand nodurile din coada
        long int x = que.front();
        que.pop();

        for (long int i = 0; i < adiacenta[x].size(); i++)
        {
            // daca e deja vizitat atunci se continua
            if (vizitat[adiacenta[x][i]])
                continue;

            que.push(adiacenta[x][i]);                   // punem noul nod in coada
            distanta[adiacenta[x][i]] = distanta[x] + 1; // incrementam distanta
            vizitat[adiacenta[x][i]] = 1;                // il marcam drept vizitat
        }
    }

    // returnam distanta nodului
    return distanta[v];
}

int main()
{
    long int n, m, c1, c2;
    vector<long int> adiacenta[10005];
    // citire numar noduri si muchii
    fin >> n >> m;

    // citire muchii
    read(adiacenta, n, m);

    // citire puncte critice
    fin >> c1 >> c2;

    for (long int i = 1; i <= n; i++)
        // vedem fata de care punct critic e mai aproape nodul curent
        if (min_dist_bfs(adiacenta, i, c1, n) < min_dist_bfs(adiacenta, i, c2, n))
            fout << min_dist_bfs(adiacenta, i, c1, n) << " ";
        else
            fout << min_dist_bfs(adiacenta, i, c2, n) << " ";
    return 0;
}
