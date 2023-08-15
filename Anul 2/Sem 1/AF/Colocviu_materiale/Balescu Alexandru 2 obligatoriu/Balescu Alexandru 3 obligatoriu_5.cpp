#include <bits/stdc++.h>

using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

const int INF = 0x3f3f3f3f;

int castel[36001];
int distanta[36001];

// Catun
// Intr-un regat feudal exista mai multe asezari omenesti, numerotate de la 1 la N, intre care sunt construite drumuri de diverse lungimi.
// Dintre aceste asezari, o parte sunt fortarete, iar restul sunt simple catune. Fiecare fortareata trebuie sa aprovizioneze trupele stationate in ea, deci are nevoie de feude.
// In calitate de mare sfetnic al monarhului, vi se cere sa indicati feudele aservite fiecarei fortarete, respectiv toate acele catune care se afla mai aproape de fortareata in discutie decat de oricare alta.
// Daca un catun este la distanta egala de doua fortarete, se va considera ca apartine fortaretei cu numarul de identificare minim.

// Cerinta
// Sa se determine pentru fiecare catun carei fortarete apartine.

// Date de Intrare
// In fisierul de intrare catun.in se vor afla numarele N, M, K, indicand, in aceasta ordine, numarul de asezari, numarul de drumuri si numarul de fortarete.
// Cea de a doua linie a fisierului va contine K numere naturale distincte indicand numerele de ordine ale fortaretelor.
// Pe urmatoarele M linii, pana la sfarsitul fisierului, se vor gasi triplete de forma (x y z), semnificand faptul ca exista un drum bidirectional intre asezarile x si y de lungime z, exprimata in unitatea de masura pentru lungimi a Evului Mediu.

// Date de Iesire
// Fisierul de iesire catun.out va contine o singura linie pe care se afla N numere naturale, al i-lea numar fiind 0, daca asezarea a i-a este o fortareata sau este un catun de la care nu se poate ajunge la nici o fortareata din cele K,
// sau numarul fortaretei de care se leaga asezarea a i-a, in caz contrar.

// Restrictii si precizari
// 1 ≤ K ≤ N ≤ 36 000
// 1 ≤ M ≤ 72 000
// Intre oricare doua asezari exista maxim un drum

vector<pair<int, int>> adiacenta[36001];
// folosim o coada de prioritati, nu un min heap
priority_queue<pair<int, int>> priority_q;
int n, m, k;

void dijkstra()
{
    // executam pana golim coada
    while (!priority_q.empty())
    {
        // extragem nod_curentul curent care e in a doua jumatate a pairului
        // in prima jumatate e distanta
        int nod_curent = priority_q.top().second;
        priority_q.pop();

        // luam vecinii nodului curent din lista de adiacenta
        for (auto &vecin : adiacenta[nod_curent])
        {
            // daca exista o cale mai scurta spre vecin prin nodul curent, actualizam distanta vecinului
            // stabilim practic daca arcul relazeaza drumul
            if (distanta[nod_curent] + vecin.second < distanta[vecin.first])
            { // actualizam distanta si il bagam in coada
                distanta[vecin.first] = distanta[nod_curent] + vecin.second;
                priority_q.push({-distanta[vecin.first], vecin.first}); // punem - ca sa luam valoarea minima a drumului, iar coada de prioritati pune in varf elementul .first-ul de val maxima
                castel[vecin.first] = castel[nod_curent];               // actualizam castelul de care se va lega drumul minim
            }
            else if (distanta[nod_curent] + vecin.second == distanta[vecin.first])
            {
                castel[vecin.first] = min(castel[vecin.first], castel[nod_curent]); // daca am gasit un drum de aceeasi lungime, actualizam castelul catunului cu castelul cu cea mai mica valoare de identificare
            }
        }
    }
}

int main()
{

    fin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
        distanta[i] = INF; // initializam distanta cu infinit

    for (int i = 1; i <= k; i++)
    {
        int x;
        fin >> x;
        castel[x] = x;           // pentru fiecare castel, il marcam ca propriul castel
        priority_q.push({0, x}); // adaugam castelul in coada drept nod sursa
        distanta[x] = 0;         // distanta de la castelul x la ea insasi este 0
    }
    // cream lista de adiacenta, tinem cont ca toate drumurile sunt bidirectionale
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        fin >> x >> y >> z;
        adiacenta[x].push_back(make_pair(y, z));
        adiacenta[y].push_back(make_pair(x, z));
    }

    dijkstra();

    for (int i = 1; i <= n; i++)
        if (castel[i] == i) // daca este castel, distanta minima este 0
            fout << 0 << " ";
        else
            fout << castel[i] << " "; // altfel, afisam castelul corespunzator catunului
    return 0;
}
