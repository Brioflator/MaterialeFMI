#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

// Paduri de multimi disjuncte
// Se dau N multimi de numere, initial fiecare multime i continand un singur element, mai exact elementul i. Asupra acestor multimi se pot face 2 tipuri de operatii, astfel:

// operatia de tipul 1: se dau doua numere naturale x si y, intre 1 si N. Se cere sa reuneasca multimile in care se afla elementul x, respectiv elementul y (se garanteaza ca x si y nu se vor afla in aceeasi multime)
// operatia de tipul 2: se dau doua numere naturale x si y, intre 1 si N. Se cere sa afiseze DA daca cele 2 elemente se afla in aceeasi multime, respectiv NU in caz contrar.
// Date de intrare
// Pe prima linie a fisierului de intrare disjoint.in se vor afla 2 numere, N si M, reprezentand numarul de multimi, respectiv numarul de operatii efectuate.
// Pe urmatoarele M linii se vor afla cate 3 numere, cod, x si y, cod reprezentand tipul operatiei, iar x si y avand semnificatia din enunt.

// Date de ieşire
// In fisierul de iesire disjoint.out se vor afisa mai multe linii, fiecare linie continand DA sau NU, reprezentand raspunsul la interogarea corespunzatoare din fisierul de intrare.

// Restricţii
// 1 ≤ N ≤ 100 000
// 1 ≤ M ≤ 100 000

int n, m;
vector<int> parents(100001);
vector<int> rang(100001);

// Gaseste parintele unui nod, facand in acelasi timp si compresia drumului.
int find_parent(int x)
{
    // este radacina
    if (parents[x] == x)
    {
        return x;
    }
    // repetam cu tatal nodului pana ajungem la radacina
    return parents[x] = find_parent(parents[x]);
}

int main()
{
    fin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        // fieacare nod incepe ca fiind propriul parinte
        // parent[1] = 2 inseamna ca 2 e parintele lui 1
        parents[i] = i;
        rang[i] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        int cod, x, y;
        fin >> cod >> x >> y;

        // legam arborele mai mic de cel mai mare
        if (cod == 1)
        {
            int rx = find_parent(x);
            int ry = find_parent(y);

            // daca arborele care l contine pe y e mai mic, atunci il atasam de arborele mai mare, anume ce l care l contine pe x
            if (rang[rx] > rang[ry])
            {
                // actualizam parintele arborelui y (cel mai mic) cu parintele arborelui lui x (cel mai mare)
                parents[ry] = rx;
                // modificam rangul/inaltimea arborelui mai mare
                rang[rx] += rang[ry];
            }
            else
            {
                parents[rx] = ry;
                rang[ry] += rang[rx];
            }
        }
        else
        {
            int rx = find_parent(x);
            int ry = find_parent(y);

            if (rx == ry)
                fout << "DA\n";
            else
                fout << "NU\n";
        }
    }
    return 0;
}
