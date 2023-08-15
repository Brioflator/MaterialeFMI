
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
// Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

// Constraints:

// 1 <= numCourses <= 2000
// 0 <= prerequisites.length <= numCourses * (numCourses - 1)
// prerequisites[i].length == 2
// 0 <= ai, bi < numCourses
// ai != bi
// All the pairs [ai, bi] are distinct.

class Solution
{
public:
    vector<int> findOrder(int numar, vector<vector<int>> &Prq)
    {
        vector<vector<int>> adiacenta(numar);
        vector<int> rez, grad_intern(numar);

        for (auto &iter : Prq)
        {
            // formam lista de adiacenta pt fiecare nod
            adiacenta[iter[1]].push_back(iter[0]);

            // pt fiecare nod tinem minte gradul intern
            grad_intern[iter[0]]++;
        }

        queue<int> que;
        // parcurgem nodurile si bagam in coada nodurile cu gradul intern 0
        for (int i = 0; i < numar; i++)
            if (grad_intern[i] == 0)
                que.push(i);

        while (que.size())
        {
            // transferam din coada in solutie nodurile cu grad 0
            // ordinea este cea data de coada
            auto nod = que.front();
            que.pop();
            rez.push_back(nod);

            // se parcurg nodurile adiacente nodului curent si li se scade gradul intern cu 1
            for (auto nod_urm : adiacenta[nod])
            {
                // avand vedere ca decrementam gradele interne tuturor nodurilor, o sa se creeze noi noduri cu gradul intern 0
                grad_intern[nod_urm]--;

                // nodurile respective le adaugam in coada
                if (grad_intern[nod_urm] == 0)
                    que.push(nod_urm);
            }
        }
        // daca rezultatul contine toate nodurile insemna ca exista o solutie
        // daca nu sunt toate nodurile, atunci exista o bucla si nu avem solutie
        if (rez.size() == numar)
            return rez;

        // cazul de iesire
        return {};
    }
};