#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

// Flux maxim
// O retea de transport este un graf orientat in care fiecare muchie are asociata o capacitate si o anumita cantitate de flux.
// Fluxul primit de fiecare muchie trebuie sa fie mai mic sau egal decat capacitatea acesteia.
// De asemenea, pentru fiecare nod, fluxul care intra in nod trebuie sa fie egal cu cantitatea de flux care iese din nod.
// Cu alte cuvinte, suma fluxurilor asociate muchiilor care intra intr-un nod trebuie sa fie egala cu suma fluxurilor asociate muchiilor care ies din nod, exceptie facand nodurile speciale S si D, denumite sursa, respectiv, destinatie.
// Din nodul sursa poate doar iesi flux, in timp ce in nodul destinatie poate doar intra flux.
// Valoarea fluxului unei astfel retele este egal cu suma fluxului care iese din sursa sau cu suma fluxului care intra in destinatie (cele doua fluxuri sunt egale).

// Cerinta 
// Dandu-se o retea de transport, in care initial fluxul pe fiecare muchie este 0, sa se calculeze fluxul maxim care poate fi trimis prin aceasta retea.

// Date de intrare
// Fisierul de intrare maxflow.in va contine pe prima linie 2 numere, N si M, reprezentand numarul de noduri si numarul de muchii din retea.
// Pe fiecare din urmatoarele M linii, se vor afla cate 3 numere naturale, x, y si z, cu semnificatia ca exista o muchie care porneste de la nodul x, ajunge in nodul y si are capacitatea z.

// Date de ieşire
// In fisierul de iesire maxflow.out se va afla un singur numar F, reprezentand fluxul maxim ce poate fi trimis prin retea.

// Restricţii
// 2 ≤ N ≤ 1 000
// 1 ≤ M ≤ 5 000
// Nodul 1 este nodul sursa, iar nodul N este nodul destinatie.
// Pentru fiecare muchie, capacitatea va fi un numar natural in intervalul [1, 110 000].
// Nu exista nici o muchie x y astfel incat x sa fie egal cu N sau y sa fie egal cu 1.
// Intre oricare doua noduri x si y exista maxim un arc, însă arcele x -> y şi y -> x pot exista simultan.
// In practica, retelele de flux contin adesea un numar mare de noduri vecine cu destinatia.
// Testele folosite la evaluarea vitezei algoritmului de flux de la aceasta problema au aceeasi proprietate.

int N, M, s, f;
vector<int> tata;
vector<vector<int>> capacitate;
vector<vector<int>> LA;

bool bfs()
{
    vector<bool> viz(N + 1);
    queue<int> q;
    q.push(s);
    viz[s] = true;
    tata[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : LA[u])
        {
            if (viz[v] == false && capacitate[u][v] != 0)
            {
                tata[v] = u;
                if (v == f)
                    return true;
                viz[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

int EdmondsKarp()
{
    long max_flow = 0;
    while (bfs())
    {
        int u, v;
        int path_flow = INT_MAX;
        for (v = f; v != s; v = tata[v])
        {
            // gasesc flow ul necesar ca sa nu se creeze bottleneck
            u = tata[v];
            path_flow = min(path_flow, capacitate[u][v]);
        }
        for (v = f; v != s; v = tata[v])
        {
            u = tata[v];
            capacitate[u][v] -= path_flow; // scad flowul gasit din capacitate pe arcele normale
            capacitate[v][u] += path_flow; // adun flow ul gasit pe arcele reverse
        }
        max_flow += path_flow; // adaug flowul gasit la total
    }
    return max_flow;
}

int main()
{
    fin >> N >> M;
    s = 1;
    f = N;
    LA.resize(N + 1);
    tata.resize(N + 1);
    capacitate.resize(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= M; i++)
    {
        int u, v;
        long c;
        fin >> u >> v >> c;
        LA[u].push_back(v);
        LA[v].push_back(u);
        capacitate[u][v] = c;
    }
    fout << EdmondsKarp();
    return 0;
}