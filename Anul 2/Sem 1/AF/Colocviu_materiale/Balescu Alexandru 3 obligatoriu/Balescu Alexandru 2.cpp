#include <bits/stdc++.h>

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

// Cuplaj maxim in graf bipartit
// Se dă un graf neorientat bipartit G = (V = (L, R), E).
// Un cuplaj în G este o submulţime de muchii M astfel încât pentru toate vârfurile v din V, există cel mult o muchie în M incidentă în v.
// Un cuplaj maxim este un cuplaj de cardinalitate maximă.

// Cerinţa
// Dându-se un graf neorientat bipartit G să se determine un cuplaj maxim.

// Date de intrare
// Fişierul de intrare cuplaj.in conţine pe prima linie trei numere naturale N, M şi E, unde N reprezintă cardinalul mulţimii L iar M cardinalul mulţimii R.
// Pe următoarele E linii se vor afla câte două numere naturale, separate între ele printr-un spaţiu, u şi v, cu semnificaţia că există muchie de la nodul u din L la nodul v din R.

// Date de ieşire
// În fişierul de ieşire cuplaj.out veţi afişa pe prima linie un singur număr reprezentând cuplajul maxim.
// Pe fiecare din următoarele linii veţi afişa câte două numere x şi y, separate între ele prin spaţiu, cu semnificaţia că nodul x din L a fost cuplat cu nodul y din R.

// Restricţii
// 1 ≤ N, M ≤ 10 000
// 0 ≤ E ≤ minim(100 000, N * M)
// Pentru 20% dintre teste: 1 ≤ N ≤ 100, 1 ≤ M ≤ 20
// Pentru 50% dintre teste: 1 ≤ (N + M) * E ≤ 5 * 106
// Pentru determinarea corectă a cuplajului maxim se va acorda 40% din punctaj şi încă 60% dacă s-a determinat o submulţime M validă.

bool vizitat[20005];
int pre[20005], C[10005][20005], flux[10005][20005], n, d;

vector<int> G[20005];
queue<int> Q;

// ideea de rezolvare este sa adaugam o sursa si destinatie, conectam sursa de nodurile din prima multime prin muchii de capacitate egala cu 1
//  iar nodurile din a doua multime de destinatie cu muchii de capacitate tot 1
// muchiile din input se vor transforma in muchii intre cele 2 multimi tot de capacitate 1
// facem algoritmul pt fluxul maxim, iar muchiile saturate reprezinta conexiunile cautate din enunt
// complexitatea este O(M* (N+M) ) deoarece fluxul maxim e egal cu nr de muchii care trebuie adaugate

/// sursa e nodul 0, destinatia nodul n+m+1, iar nodurile sunt de la 1 la n, respectiv de la n+1 la n+m

void bfs()
{
    int nod, vecin, i;
    for (i = 0; i <= 2 * n + 1; i++)
    {
        vizitat[i] = 0;
        pre[i] = 0;
    }

    vizitat[0] = 1;
    pre[0] = -1;
    Q.push(0);

    while (!Q.empty())
    {
        nod = Q.front();
        Q.pop();
        for (i = 0; i < G[nod].size(); i++)
        {
            vecin = G[nod][i];
            if (!vizitat[vecin] && C[nod][vecin] > flux[nod][vecin])
            {
                vizitat[vecin] = 1;
                pre[vecin] = nod;
                Q.push(vecin);
            }
        }
    }
}

int main()
{
    int i, m, fluxtotal = 0, mini, x, y, c, nod, urm, s, e;
    fin >> n >> m >> e;
    s = 0;
    d = n + m + 1;
    for (i = 1; i <= e; i++)
    {
        fin >> x >> y;
        y = n + y;
        C[s][x] = 1;
        C[y][d] = 1;

        G[s].push_back(x);
        G[x].push_back(s);

        G[d].push_back(y);
        G[y].push_back(d);

        C[x][y] = 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    while (1)
    {
        bfs();
        if (!vizitat[d])
            break;
        for (i = 0; i < G[d].size(); i++)
            if (vizitat[G[d][i]] && C[G[d][i]][d] > flux[G[d][i]][d])
            {
                nod = G[d][i];
                urm = d;
                mini = C[nod][urm] - flux[nod][urm];
                while (nod >= 0)
                {
                    mini = min(mini, C[nod][urm] - flux[nod][urm]);
                    urm = nod;
                    nod = pre[nod];
                }
                if (mini)
                {
                    nod = G[d][i];
                    urm = d;
                    while (nod >= 0)
                    {
                        flux[nod][urm] += mini;
                        flux[urm][nod] -= mini;
                        urm = nod;
                        nod = pre[nod];
                    }
                }
                fluxtotal += mini;
            }
    }
    fout << fluxtotal << '\n';
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n + m; j++)
            if (flux[i][j] == 1)
                fout << i << " " << j - n << '\n';

    return 0;
}
