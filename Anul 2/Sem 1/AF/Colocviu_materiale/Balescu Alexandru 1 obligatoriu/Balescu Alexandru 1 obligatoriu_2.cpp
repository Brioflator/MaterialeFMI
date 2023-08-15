#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// One of the most popular algorithms for traversing a graph is the Depth First Search (DFS).
// The DFS is usually implemented as a recursive function. First we call the function for the starting node. For each call, we go through the adjacency list of the current node, and recursively call the function for the unvisited neighbours.
// Notice that if we permute the adjacency lists of the nodes, the order in which we visit them might differ.

// In this problem you are given a graph with  N nodes and  M edges and a permutation P of size N.
// If you are allowed to shuffle the adjacency lists, is it possible to visit the nodes during a DFS starting in node 1 in the order given by P?

// Standard input
// The first line contains two integers N and M.
// The second line contains a permutation of size N. The first elements is always equal to 1.
// Each of the next M lines contains two integer a and b representing two nodes that share an edge.

// Standard output
// If it's possible to visit the nodes in the given order print 1, otherwise print 0.

const long int MN = 1000000; // nr max de noduri posibil
long int ord[MN];

vector<long int> NODURI[MN];

// vector de frecventa ca sa vedem daca un nod a fost vizitat in dfs
bool vizited[MN];
// vectorul in care o sa memoram ordinea parcurgerii grafului
vector<long int> dfs_ord;

// parcurgere folosind dfs
void vf_dfs(long int node)
{
    dfs_ord.push_back(node);
    vizited[node] = true; // marcam nodul curent ca fiind vizitat
    for (auto iterat : NODURI[node])
    {
        if (not vizited[iterat])
        {
            vf_dfs(iterat);
        }
    }
}

int main()
{
    long int n, m; // n e numarul de noduri si m e nr de muchii
    cin >> n >> m;

    vector<long int> permutare(n);
    for (long int i = 0; i < n; i += 1)
    {
        long int x;
        cin >> x;
        permutare[i] = x;
        ord[x] = i; // tin minte inte ordinea in care vor sa iasa
                    // il tin minte asa ca sa il folosesc in ordonarea listelor de adiacenta
                    // practic e o inversa a permutareutarii astfel incat functia din sortare sa ordoneze ca in permutareutarea dorita
    }

    // cream lista de adiacenta
    for (long int i = 0; i < m; i += 1)
    {
        long int a, b;
        cin >> a >> b;
        // il adaugam pe b in lista de adiacenta a lui a
        NODURI[a].push_back(b);
        // il adaugam pe a in lista de adiacenta a lui b
        NODURI[b].push_back(a);
    }

    //    for( const auto &i : NODURI )      // for elements in A, i is vector<long int>
    //    {
    //    for( const auto &j : i )  // for sub elements in A, j is long int
    //    {
    //        cout<<j;
    //    }
    //    }

    for (long int i = 1; i <= n; i += 1)
    {
        sort(NODURI[i].begin(), NODURI[i].end(), [&](long int a, long int b)
             { return ord[a] < ord[b]; });
        // fct lambda ca mi a fost lene pt una normala
        // sortez listele de adiacenta astfel incat atunci cand fac dfs pe lista de adiacenta, parcurgea sa dea ca permutareutarea
    }

    //    for( const auto &i : NODURI )      // for elements in A, i is vector<long int>
    //    {
    //    for( const auto &j : i )  // for sub elements in A, j is long int
    //    {
    //        cout<<j;
    //    }
    //    }

    vf_dfs(1);

    cout << (permutare == dfs_ord) << '\n';
    return 0;
}
