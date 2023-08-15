#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

ifstream fin("harta.in");
ofstream fout("harta.out");

// Taramul Nicaieri
// Harta "Taramului nicaieri" a fost pierduta, dar din fericire se mai stiu cateva date despre ea.
// Se stie ca exista N orase intre care se afla diferite drumuri.
// Drumurile "Taramului nicaieri" sunt un pic mai ciudate deoarece daca exista un drum care pleaca din orasul i si ajunge in orasul j nu exista in mod obligatoriu si un drum care pleaca din orasul j si ajunge in orasul i.
// De asemenea nu vor exista drumuri care pleaca si ajung in acelasi oras.
// Si nu vor exista mai multe drumuri identice(adica sa coincida si orasul din care pleaca si cel in care se ajunge).
// Pentru fiecare oras se stie cate drumuri pleaca din el si cate drumuri ajung in el.

// Cerinta
// Scrieti un program care determina drumurile de pe harta initiala.

// Date de Intrare
// Prima linie a fisierului de intrare harta.in contine numarul intreg N, reprezentand numarul de orase.
// Urmeaza apoi N linii, linia i continand doua numere x,y numarul de drumuri care pleaca din orasul i respectiv numarul de drumuri care intra in orasul i.

// Date de Iesire
// In fisierul harta.out veti afisa pe prima linie numarul M de drumuri construite,
// apoi vor urma M linii pe fiecare aflandu-se o pereche de numere a,b cu semnificatia exista un drum care pleaca din a si ajunge in b.

// Restrictii
// 1 ≤ N ≤ 100

vector<vector<int>> la;
vector<int> parinte;

int N, dest, x, y, capacitate[201][201], maxim = INT_MAX;
long max_flow = 0;

void citire()
{
    dest = 2 * N + 1;
    la.resize(201);
    parinte.resize(2 * N + 1);

    // cream un graf complet de n noduri cu ajutorul caruia avem in stanga nodurile propriu zise si in dreapta copiile lor
    // adaugam capacitatea 1 pe muchia dintre ele
    for (int i = 1; i <= N; i++)
        for (int j = 1 + N; j <= 2 * N; j++)
        {
            if (i != j - N)
            {
                la[i].push_back(j);
                la[j].push_back(i);
                capacitate[i][j] = 1;
            }
        }

    // legam nodurile de un nod fictiv 0 pentru gradul intern - capacitatea e gradul intern
    // legam o copie a nodurilor de un nod fictiv 2*n+1 pentru gradul extern - capacitatea e gradul extern
    for (int i = 1; i <= N; i++)
    {
        fin >> x >> y;
        la[0].push_back(i);
        la[i].push_back(0);
        la[dest].push_back(i + N);
        la[i + N].push_back(dest);
        capacitate[0][i] = x;
        capacitate[i + N][dest] = y;
    }
}

// BFS clasic
bool bfs()
{
    vector<bool> viz(2 * N + 1);
    queue<int> q;
    q.push(0);
    viz[0] = true;
    parinte[0] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : la[u])
        {
            if (viz[v] == false && capacitate[u][v] != 0)
            {
                parinte[v] = u;
                if (v == dest)
                    return true;
                viz[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

void EK()
{

    while (bfs())
    {
        int aux, next = dest, path_flow = maxim;
        while (next != 0)
        {
            aux = parinte[next];
            path_flow = min(capacitate[aux][next], path_flow);
            next = parinte[next];
        }
        next = dest;
        while (next != 0)
        {
            aux = parinte[next];
            capacitate[aux][next] -= path_flow;
            capacitate[next][aux] += path_flow;
            next = parinte[next];
        }
        max_flow = max_flow + path_flow;
    }
    fout << max_flow << "\n";
}

int main()
{
    // citim nr de muchii
    fin >> N;
    citire();
    EK();

    // afisam perechiile de noduri care au muchii intre ele
    for (int i = 1; i <= N; i++)
        for (int j = 1 + N; j <= 2 * N; j++)
        {
            if (capacitate[j][i])
                fout << i << " " << j - N << "\n";
        }
    return 0;
}
