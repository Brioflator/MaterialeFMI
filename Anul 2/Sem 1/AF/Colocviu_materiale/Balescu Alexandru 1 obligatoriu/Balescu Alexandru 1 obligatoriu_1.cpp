// We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.

// Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.

// Example 1:

// Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
// Explanation: The first group has [1,4], and the second group has [2,3].
// Example 2:

// Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
// Output: false
// Explanation: We need at least 3 groups to divide them. We cannot put them in two groups.

// Constraints:

// 1 <= n <= 2000
// 0 <= dislikes.length <= 104
// dislikes[i].length == 2
// 1 <= ai < bi <= n
// All the pairs of dislikes are unique.

class Solution
{
    bool vfB(vector<vector<int>> &adiacenta, int N, int nod, vector<int> &color)
    {
        queue<int> q;
        // Asignam culoare primului nod
        q.push(nod);
        color[nod] = 1;
        // Prelucram componentele cu BFS
        while (!q.empty())
        {
            int curent = q.front();
            q.pop();

            for (int element : adiacenta[curent])
            {
                // Pentru cicluri de lungime impara
                if (color[element] == color[curent])
                    return false;
                // Nod nevizitat
                if (color[element] == -1)
                    color[element] = 1 - color[curent], q.push(element); // dam culoarea opusa si il adaugam in coada
            }
        }
        return true;
    }

public:
    bool possibleBipartition(int n, vector<vector<int>> &dislikes)
    {
        ios_base::sync_with_stdio(false); // optimizare, nu sunt sigur daca e necesara, dar nu strica :D
        cin.tie(NULL);
        int i = 0;
        vector<vector<int>> adiacenta(n + 1); // vector de adiacenta facut in functie de dislikes
        // Construim vectorul de adiacenta
        for (i; i < dislikes.size(); ++i)
        {
            adiacenta[dislikes[i][0]].push_back(dislikes[i][1]);
            adiacenta[dislikes[i][1]].push_back(dislikes[i][0]);
        }
        i = 1;
        vector<int> color(n + 1, -1);
        for (i; i <= n; ++i)
            if (color[i] == -1)
                if (!vfB(adiacenta, n, i, color))
                    return false;
        return true;
    }
};