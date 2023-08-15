# Clustering.
# Fişierul cuvinte.inconţine cuvinte pe mai multe linii, cuvintelede pe o linie fiind separate prin spaţiu.
# Se citeşte de la tastatură un număr natural k. Se consideră distanţa Levenshtein între două cuvinte.
# Să se împartă cuvintele dinfişier în k clase(categorii)nevide astfel încât gradul de separare al claselor să fie maxim(=distanţa minimă între două cuvinte din clase diferite) - v. curs
# se vor afişape câte o linie cuvintele din fiecare clasă și pe o altă linie gradul de separare al claselor.

# calculeaza distanta dintre 2 cuvinte date a si b cu Levenshtein


def L_dist(a, b):

    if len(b) == 0:
        return len(a)
    elif len(a) == 0:
        return len(b)
    elif a[0] == b[0]:
        return L_dist(a[1:], b[1:])
    else:
        return 1 + min(L_dist(a[1:], b),
                       L_dist(a, b[1:]),
                       L_dist(a[1:], b[1:]))


cuvinte = ["martian", "care", "este", "sinonim", "ana",
           "case", "apa", "arbore", "partial", "minim"]
k = 3  # nr de clase unice cerute

n = 10
muchii = []
# creez graful si calculez distanta intre fiecare cuvant => graf ponderat complet
for i in range(n-1):
    for j in range(i+1, n):
        d = L_dist(cuvinte[i], cuvinte[j])
        muchii.append((i, j, d))


# kruskal varianta 2

# Gaseste parintele unui nod, facand in acelasi timp si compresia drumului.
def find_parent(u):

    global parents
    # e radacina
    if parents[u] == 0:
        return u
    # repetam cu tatal nodului pana ajungem la radacina
    parents[u] = find_parent(parents[u])
    return parents[u]

# reuniune ponderata


def reuneste(u, v):

    global parents, rang
    ru = find_parent(u)
    rv = find_parent(v)
    # daca arborele care l contine pe v e mai mic, atunci il atasam de arborele mai mare, anume ce-l care-l contine pe u
    if rang[ru] > rang[rv]:
        parents[rv] = ru

    # daca arborele care l contine pe u e mai mic, atunci il atasam de arborele mai mare, anume ce-l care-l contine pe v
    else:
        parents[ru] = rv
        if rang[ru] == rang[rv]:
            rang[rv] = rang[rv]+1


# initializare
parents = [0]*(n)
rang = [0]*(n)

# sortez crescator dupa cost
muchii = sorted(muchii, key=(lambda t: t[2]))

nrmsel = 0  # nr muchii selectate (arbore -> n-1 muchii)
cost = 0
arbore = []
i = 0
while i < len(muchii):
    m = muchii[i]
    # daca nu fac parte din ac componenta (adica nu avem ciclu)
    if find_parent(m[0]) != find_parent(m[1]):
        # printez muchiile
        arbore.append((m[0], m[1]))
        reuneste(m[0], m[1])
        cost = cost+m[2]
        nrmsel = nrmsel+1

        if nrmsel == n - k:  # il opresc cand am pus n-k muchii ca sa am k clustere
            break
    i += 1

# afisare cuvinte
for i in range(n):
    if parents[i] == 0:
        print(cuvinte[i], end=" ")
        for j in range(n):
            if parents[j] == i:
                print(cuvinte[j], end=" ")
        print()
# urmatoarea muchie pe care as fi selectat-o este gradul de separare
print("gradul se separare: ", muchii[i+1][2])
