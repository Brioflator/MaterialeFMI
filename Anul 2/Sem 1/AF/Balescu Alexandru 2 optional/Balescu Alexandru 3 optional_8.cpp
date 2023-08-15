class UnionFind
{
    vector<int> parents;

public:
    // fiecare nod o sa fie propriul parinte;
    UnionFind(int n) : parents(n)
    {
        iota(begin(parents), end(parents), 0);
    }

    // unim doi arbori prin faptul ca schimbam parintele nodului x cu y
    void connect(int a, int b)
    {
        int x = find(a), y = find(b);
        if (x == y)
            return;
        parents[x] = y;
    }

    bool connected(int i, int j) { return find(i) == find(j); }

    int find(int a)
    {
        return parents[a] == a ? a : (parents[a] = find(parents[a]));
    }
};
class Solution
{
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &E, vector<vector<int>> &Q)
    {
        vector<bool> raspuns(Q.size());

        for (int i = 0; i < Q.size(); ++i)
            Q[i].push_back(i); // alocam fiecarui query un id, ca sa facem vectorul rezultat

        sort(begin(Q), end(Q), [&](auto &a, auto &b)
             { return a[2] < b[2]; }); // sortam queriurile dupa limita
        sort(begin(E), end(E), [&](auto &a, auto &b)
             { return a[2] < b[2]; }); // sortam muchiile dupa greutate

        UnionFind uf(n);
        int i = 0;
        for (auto &q : Q)
        { // parcurgem queriurile de la cel mai mic la cel mai mare
            int u = q[0], v = q[1], limit = q[2], querry_id = q[3];
            // vizitam doar laturile care au greutatea mai mica decat limita
            for (; i < E.size() && E[i][2] < limit; ++i)
                uf.connect(E[i][0], E[i][1]);

            // daca primul cu ultimul nod sunt conectati, atunci raspunusl e true
            raspuns[querry_id] = uf.connected(u, v);
        }
        return raspuns;
    }
};