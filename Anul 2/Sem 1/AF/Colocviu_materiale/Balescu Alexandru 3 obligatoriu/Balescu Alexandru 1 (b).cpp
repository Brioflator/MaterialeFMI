#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

// Modificați algoritmul de la punctul a) astfel încât să afișați tăietura minima între  sursa și  orice  alt vârf,
// adică o mulțime de arce cu costul total minim pe care dacă le eliminăm din rețea cel puțin un vârf care era accesibil inițial din sursă după eliminare nu mai este accesibil.

int N, M, s, f;
vector<int> tata;
vector<vector<int>> capacitate;
vector<vector<int>> Rcapac; // copie a grafului pentru rezidual
vector<vector<int>> LA;

void dfs() // dfs ca sa gasesc nodurile accesibile din s
{
    vector<bool> viz(N + 1);
    viz[s] = true;
    for (int i = 0; i < M; i++)
        if (capacitate[s][i] && !viz[i])
            dfs();
}

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
    int u, v;
    for (u = 0; u < M; u++)
        for (v = 0; v < M; v++)
            Rcapac[u][v] = capacitate[u][v];

    long max_flow = 0;
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

    // pct b unde am modificat
    // flowul e maxim atm, gasesc nodurile accesibile pornind din s
    bool visited[M];
    memset(visited, false, sizeof(visited));
    dfs();
    // afisez toate muchiile care leaga un nod accesibil de un nod izolat in grafic
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            if (visited[i] && !visited[j] && Rcapac[i][j])
                cout << i << " - " << j << endl;

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
