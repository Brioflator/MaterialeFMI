
// You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].
// Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.
// If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.

// Constraints:

// 2 <= n <= 10^4
// 0 <= start, end < n
// start != end
// 0 <= a, b < n
// a != b
// 0 <= succProb.length == edges.length <= 2*10^4
// 0 <= succProb[i] <= 1
// There is at most one edge between every two nodes.

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end)
    {
        // crearea listei de adiacenta a grafului
        vector<vector<pair<int, double>>> adiacenta(n);
        for (int i = 0; i < edges.size(); ++i)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            double sprob = succProb[i];
            adiacenta[u].push_back({v, sprob});
            adiacenta[v].push_back({u, sprob});
        }

        priority_queue<pair<double, int>> qu; //{probabilitate, index}
        vector<double> visited(n), prob(n);

        prob[start] = 1;
        qu.push({1, start});

        // Dijkstra, dar cu cat e probabilitatea mai mare, cu atat mai bine
        while (!qu.empty())
        {
            int nod = qu.top().second;
            qu.pop();

            // am ajuns in nodul dorit
            if (nod == end)
                return prob[nod];

            if (visited[nod] == 1)
                continue;

            // marchez ca vizitat
            visited[nod] = 1;

            for (auto &vecin : adiacenta[nod])
            {
                double vertex = vecin.first;
                double weight = vecin.second;
                if (visited[vertex] == 0 && prob[vertex] < prob[nod] * weight)
                {
                    prob[vertex] = prob[nod] * weight;
                    qu.push({prob[vertex], vertex});
                }
            }
        }

        return 0;
    }
};