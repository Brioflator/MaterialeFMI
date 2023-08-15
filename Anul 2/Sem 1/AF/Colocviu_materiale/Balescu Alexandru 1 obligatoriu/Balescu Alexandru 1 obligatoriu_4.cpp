#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <map>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

// Componente tare conexe
// Se dă un graf orientat G = (V, E). O componentă tare conexă a grafului orientat G este o mulţime maximală de vârfuri U inclusă în V, astfel încât, pentru fiecare pereche de vârfuri u şi v din U avem atât drum de la u la v cât şi drum de la v la u. Cu alte cuvinte, vâfurile u şi v sunt accesibile unul din celălalt.

// Cerinţă
// Dându-se un graf orientat G = (V, E) se cere să se determine componentele sale tare conexe.

// Date de intrare
// Fişierul de intrare ctc.in conţine pe prima linie două numere naturale N si M ce reprezintă numărul de noduri din G şi numărul muchiilor. Pe următoarele M linii se vor afla câte două numere naturale x şi y, separate prin spaţiu, reprezentând muchia orientată (x, y).

// Date de ieşire
// În fişierul de ieşire ctc.out se va afişa pe prima linie un singur număr reprezentând numărul componentelor tare conexe. Pe fiecare din următoarele linii se va scrie câte o componentă tare conexă prin enumerarea nodurilor componente. Acestea pot fi afişate în orice ordine.

// Restricţii
// 1 ≤ N ≤ 100 000
// 1 ≤ M ≤ 200 000
// Pentru 30% din teste, 1 ≤ N ≤ 100 si 1 ≤ M ≤ 500
// Pentru 60% din teste, 1 ≤ N ≤ 5 000 si 1 ≤ M ≤ 25 000
// Pentru aflarea corectă doar a numărului componentelor tare conexe se va acorda 40% din punctaj

class GRAF
{
public:
    int n;
    list<int> *adiacenta;
    GRAF(int n);                     // constructor cu parametru
    GRAF Transpusa();                // pentru transpunerea grafului
    void DFS(int n, bool vizitat[]); // dfs standard
    void add_edge(int a, int b);     // pt adaugarea muchiilor in lista de adiacenta
    void fillOrder(int node, stack<int> &stack, bool vizitat[]);
    void afisare_CTC(); // pentru afisare
};

GRAF::GRAF(int n)
{
    this->n = n;
    adiacenta = new list<int>[n + 1];
}

void GRAF::add_edge(int a, int b)
{
    adiacenta[a].push_back(b); // adaugam b la lista lui a
}

void GRAF::DFS(int node, bool vizitat[])
{
    // marcam nodul ca vizitat si il afisam
    vizitat[node] = true;
    fout << node << " ";
    // daca nu e vizitat, aplicam dfs
    list<int>::iterator i;
    for (i = adiacenta[node].begin(); i != adiacenta[node].end(); i++)
        if (!vizitat[*i])
            DFS(*i, vizitat);
}

GRAF GRAF::Transpusa()
{
    GRAF g(n);
    // cream transpusa in g
    for (int i = 1; i <= n; i++)
    {
        list<int>::iterator it;
        // adaugam in g "opusul" muchiei din lista de adiacenta
        for (it = adiacenta[i].begin(); it != adiacenta[i].end(); it++)
            g.adiacenta[*it].push_back(i);
    }
    return g;
}

void GRAF::fillOrder(int node, stack<int> &stiva, bool vizitat[]) // un dfs adaptat ca sa ne dam seama de ordine

{
    // nodul curent devine vizitat
    vizitat[node] = true;

    list<int>::iterator i;
    for (i = adiacenta[node].begin(); i != adiacenta[node].end(); i++)
        if (!vizitat[*i])
            fillOrder(*i, stiva, vizitat);

    // punem in stiva toate nodurile verificate care au fost deja utilizate
    // din moment ce o sa refolosim vectorul de vizitate, avem nevoie de nodurile vizitate in graful normal
    stiva.push(node);
}

int counter = 0;

void GRAF::afisare_CTC()
{
    bool *vizitat = new bool[n];

    // consideram initial toate nodurile ca fiind nevizitate
    stack<int> stiva;
    for (int i = 1; i <= n; i++)
        vizitat[i] = false;

    // punem varfurile in stiva in functie de cum au fost parcursi
    for (int i = 1; i <= n; i++)
        if (vizitat[i] == false)
            fillOrder(i, stiva, vizitat);

    // graf inversat
    GRAF gr = Transpusa();

    for (int i = 1; i <= n; i++)
        vizitat[i] = false;

    // Folosim varfurile in functie de cum au intrat in stiva
    while (stiva.empty() == false)
    {
        // Luam un varf din stiva
        int v = stiva.top();
        stiva.pop();

        // Zona unde afisam componentele tari conexe care contin varful
        // Cand intram in acest if inseamna ca s-a gasit o noua CTC si se face un dfs pe transpusa
        // Ca sa fim siguri ca e CTC ne am folosit deja de proprietatea ca CTC sunt aceleasi si in graful transpus si in cel normal
        if (vizitat[v] == false)
        {
            // Counter pentru a numara componentele tari conexe
            counter++;
            gr.DFS(v, vizitat);

            fout << endl;
        }
    }
    fout << counter;
}

int main()
{
    int n, m;
    fin >> n >> m;
    GRAF g(n);

    int x, y;
    for (int i = 1; i <= m; i++)
        do
        {
            fin >> x >> y;
            g.add_edge(x, y);                                 // construire graf
        } while (x == y || x > n || x < 1 || y > n || y < 1); // prevenirea datelor eronate

    g.afisare_CTC();

    return 0;
}
