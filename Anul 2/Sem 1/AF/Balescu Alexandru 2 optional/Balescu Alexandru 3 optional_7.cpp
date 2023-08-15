class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &A)
    {
        int N = A.size(), rezultat = 0, nod_curent = 0;
        // initailizez lista de distante cu infinit
        vector<int> dist(N, INT_MAX), viz(N);

        for (int i = 0; i < N - 1; ++i)
        {
            // iau coordonatele
            int x = A[nod_curent][0], y = A[nod_curent][1];
            // marchez punctul ca fiind vizitat
            viz[nod_curent] = 1;

            for (int j = 0; j < N; ++j)
            {
                // daca a fost deja vizitat, sarim cu for ul
                if (viz[j])
                    continue;
                // gasim distantele intre nodul curent si celelalte noduri
                dist[j] = min(dist[j], abs(A[j][0] - x) + abs(A[j][1] - y));
            }
            // iau coordonata urmatorului nod pentru care o sa reiterez
            nod_curent = min_element(begin(dist), end(dist)) - begin(dist);
            // adaug costul la suma
            rezultat += dist[nod_curent];
            // am grija ca lista cu distante sa fie mereu ocupata cu infinit ca sa nu incurce la alte iterari
            dist[nod_curent] = INT_MAX;
        }
        return rezultat;
    }
};