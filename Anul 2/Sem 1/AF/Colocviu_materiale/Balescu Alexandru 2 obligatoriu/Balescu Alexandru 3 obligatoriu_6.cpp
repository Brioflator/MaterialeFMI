#include <bits/stdc++.h>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

// Se dă un graf orientat aciclic cu N noduri şi M muchii. Fiecare nod i are o valoare v[i].
// Să se găsească şi să se afişeze suma maximă a unui lanţ din graf.
// Suma unui lanţ este suma valorilor nodurilor conţinute de acesta.

// Date de intrare
// Fişierul de intrare easygraph.in conţine pe prima linie numărul de teste, T.
// În continuare, pentru fiecare test, se vor găsi pe prima linie două numere naturale N şi M, având semnificaţia din enunţ.
// Pe cea de-a doua linie, se vor găsi N numere întregi, elementele vectorului v[i].
// Pe următoarele M linii se vor găsi câte două numere x şi y, cu semnificaţia că există un arc de la nodul x la nodul y.

// Date de ieşire
// În fişierul de ieşire easygraph.out se vor găsi T linii, pe linia i găsindu-se răspunsul pentru testul i.

// Restricţii
// T = 20
// 1 ≤ N ≤ 15.000
// 1 ≤ M ≤ 30.000
// -106 ≤ v[i] ≤ 106
// Pot exista mai multe arce între aceleaşi noduri X şi Y.
// Lanţul găsit de sumă maximă trebuie să conţină cel puţin 1 nod.

long long int n, m, t;

// sortare topologica
vector<long long int> sortare_topologica(vector<long long int> &grad_intern, vector<vector<long long int>> &adiacenta)
{
    vector<long long int> rezultat;
    queue<long long int> qu;

    // punem in coada nodurile cu gradul intern 0
    for (long long int i = 1; i <= n; i++)
        if (grad_intern[i] == 0)
            qu.push(i);

    while (!qu.empty())
    {
        long long int nod = qu.front();
        rezultat.push_back(nod);
        qu.pop();

        // practic "eliminam" nodul de pe prima pozitie din coada

        for (auto nod_curent : adiacenta[nod])
        { // pentru toti vecinii din lista de adiacenta scadem 1
            grad_intern[nod_curent]--;
            // daca gasim noduri al caror grad intern a devenit 0, le punem in coada
            if (grad_intern[nod_curent] == 0)
                qu.push(nod_curent);
        }
    }

    return rezultat; // returnam vectorul raspuns(sortarea topologica)
}
int main()
{
    // nr cazuri
    fin >> t;

    for (long long int k = 1; k <= t; k++)

    {
        long long int rezultat = -999999;

        fin >> n >> m;
        vector<long long int> grad_intern(15005, 0);
        vector<long long int> v(15005);   // v= vector cu valorile nodurilor
        vector<long long int> sum(15005); // suma= vector continand suma maxima pana la un anume nod
        vector<vector<long long int>> adiacenta(15005), vector_tati(15005);

        // cit val v
        for (long long int i = 1; i <= n; i++)
            fin >> v[i];

        // cit arce
        long long int x, y;
        for (long long int i = 0; i < m; i++)
        {
            fin >> x >> y;

            adiacenta[x].push_back(y); // adaugam in list de adiacenta
            grad_intern[y]++;          // contorizam gradul de interne

            vector_tati[y].push_back(x); // vector de tati
        }

        // aplicam sortarea topologica
        vector<long long int> sortare = sortare_topologica(grad_intern, adiacenta);

        for (auto i : sortare)
        {
            sum[i] = v[i]; // initial suma este valoarea nodului
            for (auto t : vector_tati[i])
                // maxim dintre suma elem si (suma tatalui + valoare_nod)
                // verificam aceasta conditie cu toti tatii nodului
                sum[i] = max(sum[i], sum[t] + v[i]);
        }
        // alegem lantul cu valoarea maxima dintre toate celelalte lanturi
        for (long long int i = 1; i <= n; i++)
            rezultat = max(rezultat, sum[i]);

        fout << rezultat << endl;
    }
    return 0;
}