
# informatii despre un nod din arborele de parcurgere (nu nod din graful initial)
class Nod:
    def __init__(self, info, parinte=None):
        self.info = info  # eticheta nodului
        self.parinte = parinte  # parintele din arborele de parcurgere

    def __str__(self):
        return str(self.info)

    def __repr__(self):
        # afisarea unui nod va fi de forma "c (a -> b -> c)"
        return "({}, ({}))".format(self.info, "->".join([str(x) for x in self.drumRadacina()]))

    # va returna o listă cu toate nodurile ca obiecte de la rădăcină până la nodul curent
    def drumRadacina(self):
        l = []
        while self is not None:
            l.insert(0, self)
            self = self.parinte  # trec la parintele din arborele de parcurgere
        return l

    # verifică dacă nodul a fost vizitat (informatia lui e in propriul istoric)
    def vizitat(self):
        nod = self.parinte
        while nod is not None:
            if self.info == nod.info:
                return True
            nod = nod.parinte
        return False


class Graf:  # graful problemei

    def __init__(self, mat, start, scopuri):
        self.mat = mat  # matricea de adiacenta
        self.start = start  # informatia nodului de start
        self.scopuri = scopuri  # lista cu informatiile nodurilor scop

    # verifica daca nodul curent este un nod scop
    def scop(self, infoNod):
        return infoNod in self.scopuri

    # va genera succesorii sub forma de noduri in arborele de parcurgere
    def succesori(self, nodCurent):
        Succ = []
        for i in range(len(self.mat)):
            if self.mat[nodCurent.info][i] == 1:
                nodNou = Nod(i, nodCurent)
                if not nodNou.vizitat():
                    Succ.append(nodNou)
        return Succ

#########################################################################

# e luata de la colegi
m = [
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
]

start = 0
scopuri = [5, 9]
gr = Graf(m, start, scopuri)


# BFS:
# pentru mai multe solutii folosim nrSol, pentru o singura solutie nu l mai folosim
# si oprim algoritmul la prima solutie

def BFS(gr, nrSol=1):
    # in coada avem noduri (obiecte de tip Nod)
    q = [Nod(gr.start)]

    while len(q) > 0:
        nodCurent = q.pop(0)  # sterg primul element din coada

        if gr.scop(nodCurent.info):  # daca nodul curent este scop
            print("SOL: ", end="")  # afisez solutia
            print(repr(nodCurent))
            nrSol -= 1  # am gasit o solutie, deci scad nr de solutii
            if nrSol == 0:
                return
        # generez succesorii nodului curent
        lSuccesori = gr.succesori(nodCurent)
        q += lSuccesori


# apeul initial se face fara parametrul nodCurent deoarece trebuie ca DFS ul sa inceapa de la nodul de start
def DFS(gr, nrSol=1, nodCurent=Nod(gr.start)):
    if nrSol <= 0:
        return nrSol

    if gr.scop(nodCurent.info):  # daca nodul curent este scop
        print("SOL: ", end="")  # afisez solutia
        print(repr(nodCurent))
        nrSol -= 1  # am gasit o solutie, deci scad nr de solutii
        if nrSol == 0:
            return nrSol
    lSuccesori = gr.succesori(nodCurent)  # generez succesorii nodului curent

    for succ in lSuccesori:  # pentru fiecare succesor apelez recursiv DFS pana cand gasesc nr de solutii dorite
        if nrSol != 0:
            nrSol = DFS(gr, nrSol, succ)

    return nrSol


def DFS_nerec(nrSol):
    # in stiva pun nodul de start (obiecte de tip Nod)
    # consider varful stivei in dreapta
    stiva = [Nod(gr.start)]

    # cat timp stiva nevida
    while stiva:
        nodCurent = stiva.pop()  # scot varful stivei
        if gr.scop(nodCurent.info):  # daca nodul curent este scop
            print("SOL: ", end="")  # afisez solutia
            print(repr(nodCurent))
            nrSol -= 1  # am gasit o solutie, deci scad nr de solutii
            if nrSol == 0:
                return
        # adaug in stiva succesorii nodului curent (in ordinea inversa)
        # in ordinea inversa pentru a avea la varful stivei primul succesor
        stiva += gr.succesori(nodCurent)[::-1]


print("============================= \nBreadthfirst\n")
BFS(gr, 3)
print("============================= \nDepthFirst recursiv\n")
DFS(gr, 3)
print("============================= \nDepthFirst nerecursiv\n")
DFS_nerec(3)
