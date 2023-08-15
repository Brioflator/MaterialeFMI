#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

#define inf 1000001

using namespace std;

ifstream fin("retea2.in");
ofstream fout("retea2.out");

// Retea2
// Damia s-a hotarat sa-si deschida N centrale electrice. In orasul ei sunt M blocuri care trebuie sa primeasca curent. Un bloc primeste curent eletric daca este conectat la alt bloc care primeste curent electric sau daca este conectat la o centrala eletrica. Stiindu-se coordonatele celor N centrale si a celor M blocuri, si stiindu-se faptul ca pentru a conecta doua dintre aceste puncte trebuie platit un cost egal cu distanta euclidiana dintre ele, ajutati-o pe Damia sa determine costul minim pentru a transmite curent eletric catre toate blocurile.

// Date de intrare
// Fişierul de intrare retea2.in se gasesc doua numere naturale N si M. Pe ficare dintre urmatoarele N linii se va gasi cate o pereche de numere intregi reprezentand coordonatele in plan ale unei centrale. Pe fiecare dintre urmatoarele M linii se va gasi cate o pereche de numere intregi reprezentand coordonatele unui bloc de locutine.

// Date de ieşire
// În fişierul de ieşire retea2.out se va gasi un singur numar real, reprezentand costul minim pentru a transmite curent eletric blocurilor in modul descris in enunt.

// Restricţii
// 1 ≤ N ≤ 2000
// 0 ≤ M ≤ 2000
// Coordonatele punctelor vor fi mai mici in modul ca 106.
// Rezultatul trebuie afisat cu o precizie de 6 zecimale.
// Pentru teste in valoare de 50 puncte, N + M ≤ 1000.
// Pentru teste in valoare de 20 puncte, N,M ≤ 10.

struct punct
{
    double x, y;
};

// calculeaza distanta euclidiana intre doua puncte
double distanta(punct a, punct b)
{
    return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

int n, m;
vector<punct> centrale(2001);
vector<punct> blocuri(2001);

double dist[2001];
bool viz[2001];
double cost_total = 0;

void cit()
{
    fin >> n >> m;

    blocuri[0] = {0, 0};
    centrale[0] = {0, 0};

    double x, y;

    // citire centrale
    for (long int i = 1; i <= n; i++)
    {
        fin >> x >> y;
        centrale[i] = {x, y};
    }

    // citire blocuri
    for (long int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        blocuri[i] = {x, y};
        // initializam cu max posibil ca sa aflam distanta minima
        dist[i] = inf;
    }
}

// tinem in vectorul dist distanta dintre bloc si cea mai apropiata centrala
void distanta_minima_centrale()
{
    for (long int j = 1; j <= m; j++)
        for (long int i = 1; i <= n; i++)
            dist[j] = min(dist[j], distanta(centrale[i], blocuri[j]));
}

double distanta_totala()
{
    for (long int i = 1; i <= m; i++)
    {
        // initializam asa ca sa calculam costul minim
        double cost = inf;
        int pozitie = 0;
        for (int j = 1; j <= m; j++)
            // viz[j] e fals pt blocurile care inca nu au fost incluse in sol finala
            // updatam pozitia numai in cazul in care dist[j] e mai mic decat cost
            if (viz[j] == false && dist[j] < cost)
            {
                cost = dist[j];
                pozitie = j;
            }
        // marcam ca parte din solutie si actualizam costul final
        viz[pozitie] = true;
        cost_total += cost;

        // verificam posibilitatea in care e mai avantajos sa legam un bloc de un bloc decat un bloc de o centrala
        // un fel de relaxare de arc
        for (long int j = 1; j <= m; j++)
        {
            if (viz[j] == false && dist[j] > distanta(blocuri[pozitie], blocuri[j]))
                dist[j] = distanta(blocuri[pozitie], blocuri[j]);
        }
    }

    return cost_total;
}

int main()
{
    cit();
    distanta_minima_centrale();
    fout << setprecision(6) << fixed << distanta_totala();
    return 0;
}
