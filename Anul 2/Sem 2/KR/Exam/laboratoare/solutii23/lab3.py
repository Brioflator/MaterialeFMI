from queue import PriorityQueue
import cProfile
import time

# informatii despre un nod din arborele de parcurgere (nu nod din graful initial)
class NodParcurgere:
    def __init__(self, info, g = 0, h = 0, parinte=None):
        self.info = info  # eticheta nodului, de exemplu: 0,1,2...
        self.parinte = parinte  # parintele din arborele de parcurgere
        self.g = g
        self.h = h
        self.f = g + h

    def drumRadacina(self):
        l = []
        nod = self
        while nod:
            l.insert(0, nod)
            nod = nod.parinte
        return l


    def vizitat(self): #verifică dacă nodul a fost vizitat (informatia lui e in propriul istoric)
        nodDrum = self.parinte
        while nodDrum:
            if (self.info == nodDrum.info):
                return True
            nodDrum = nodDrum.parinte

        return False

    def __str__(self):
        return str(self.info)

    def __repr__(self):
        sir = str(self.info) + "("
        drum = self.drumRadacina()
        sir += ("->").join([str(n.info) for n in drum])
        sir += ")"
        return sir

    def __eq__(self, other):
        return self.g + self.h == other.g + other.h

    def __lt__(self, other):
        return (self.g + self.h < other.g + other.h) or ((self.g + self.h == other.g + other.h) and (self.g > other.g))

class Graph:  # graful problemei

    def __init__(self, matrice, start, scopuri, lista_estimari):
        self.matrice = matrice
        self.nrNoduri = len(matrice)
        self.start = start  # informatia nodului de start
        self.scopuri = scopuri  # lista cu informatiile nodurilor scop
        self.lista_estimari = lista_estimari

    # va genera succesorii sub forma de noduri in arborele de parcurgere
    def succesori(self, nodCurent):
        listaSuccesori = []
        for i in range(self.nrNoduri):
            if self.matrice[nodCurent.info][i] > 0:
                nodNou = NodParcurgere(info=i,
                                       g = nodCurent.g + self.matrice[nodCurent.info][i],
                                       h = self.estimeaza_h(i),
                                       parinte=nodCurent)
                if not nodNou.vizitat():
                    listaSuccesori.append(nodNou)
        return listaSuccesori

    def scop(self, infoNod):
        return infoNod in self.scopuri

    def estimeaza_h (self, infoNod):
        return self.lista_estimari[infoNod]



##############################################################################################
#                                 Initializare problema                                      #
##############################################################################################

m = [ [0, 3, 5, 10, 0, 0, 100],
      [0, 0, 0, 4, 0, 0, 0],
      [0, 0, 0, 4, 9, 3, 0],
      [0, 3, 0, 0, 2, 0, 0],
      [0, 0, 0, 0, 0, 0, 0],
      [0, 0, 0, 0, 4, 0, 5],
      [0, 0, 3, 0, 0, 0, 0]]

start = 0
scopuri = [4, 6]
h_part = [0, 1, 6, 2, 0, 3, 0]
# pt modificare de valori putem sa scadem 1 din 3 valori [0, 1, 5, 1, 0, 2, 0]
# ca sa nu mai fie admisibila, h_part poate fi [0, 1, 8, 2, , 3, 0]
gr = Graph(m, start, scopuri, h_part)


#### algoritm BF
# presupunem ca vrem mai multe solutii (un numar fix) prin urmare vom folosi o variabilă numită nrSolutiiCautate
# daca vrem doar o solutie, renuntam la variabila nrSolutiiCautate
# si doar oprim algoritmul la afisarea primei solutii

def breadth_first(gr, nrSolutiiCautate=1):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.start)]

    while len(c) > 0:
        #print("Coada actuala: " + str(c))
        #input()
        nodCurent = c.pop(0)

        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.info) for n in drum]))
            print("\n----------------\n")
            #input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        c+=gr.succesori(nodCurent)


def depth_first(gr, nrSolutiiCautate=1):
    # vom simula o stiva prin relatia de parinte a nodului curent
    df(NodParcurgere(gr.start), nrSolutiiCautate)


def df(nodCurent, nrSolutiiCautate):
    if nrSolutiiCautate <= 0:  # testul acesta s-ar valida doar daca in apelul initial avem df(start,if nrSolutiiCautate=0)
        return nrSolutiiCautate
    #print("Stiva actuala: " + repr(nodCurent.drumRadacina()))
    #input()
    if gr.scop(nodCurent.info):
        print("Solutie: ", end="")
        drum = nodCurent.drumRadacina()
        print(("->").join([str(n.info) for n in drum]))
        print("\n----------------\n")
        #input()
        nrSolutiiCautate -= 1
        if nrSolutiiCautate == 0:
            return nrSolutiiCautate
    lSuccesori = gr.succesori(nodCurent)
    for sc in lSuccesori:
        if nrSolutiiCautate != 0:
            nrSolutiiCautate = df(sc, nrSolutiiCautate)

    return nrSolutiiCautate

def cautare_binara(listaNoduri, nodNou, left, right):
    if right <= 0:
        return 0
    if left == right:
        if nodNou.f < listaNoduri[left].f:
            return left
        elif nodNou.f > listaNoduri[left].f:
            return right + 1
        else: # f-uri egale
            if nodNou.g < listaNoduri[left].g: # preferam nodul cu g ul mai mare
                return right + 1
            else:
                return left
    else:
        mid = (left + right) // 2
        if nodNou.f > listaNoduri[mid].f:
            return cautare_binara(listaNoduri, nodNou, mid + 1, right)
        elif nodNou.f < listaNoduri[mid].f:
            return cautare_binara(listaNoduri, nodNou, left, mid)
        else:
            if nodNou.g < listaNoduri[mid].g:
                return cautare_binara(listaNoduri, nodNou, mid + 1, right)
            else:
                return cautare_binara(listaNoduri, nodNou, left, mid)

def aStarSolMultiple(gr, nrSolutiiCautate=1):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.start)]

    while len(c) > 0:
        nodCurent = c.pop(0)

        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.info) for n in drum]))
            print("Cost: ", nodCurent.f)
            print("\n----------------\n")
            #input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        for succ in gr.succesori(nodCurent):
            index = cautare_binara(c, succ, 0, len(c) - 1)
            c.insert(index, succ)

def aStarSolMultiplePQ(gr, nrSolutiiCautate=1):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = PriorityQueue()
    c.put(NodParcurgere(gr.start))

    while not c.empty():
        #print("Coada actuala: " + str(c))
        #input()
        nodCurent = c.get()

        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.info) for n in drum]))
            print("Cost: ", nodCurent.f)
            print("\n----------------\n")
            #input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        for succ in gr.succesori(nodCurent):
            c.put(succ)


# df(a)->df(b)->df(c)->df(f)
#############################################

def df_nerecursiv(nrSolutiiCautate):
    stiva = [NodParcurgere(gr.start)]
    #consider varful stivei in dreapta
    while stiva: #cat timp stiva nevida
        nodCurent=stiva.pop() #sterg varful
        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.info) for n in drum]))
            print("\n----------------\n")
            #input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        stiva+=gr.succesori(nodCurent)[::-1] #adaug in varf succesoii in ordine inversa deoarece vreau sa expandez primul succesor generat si trebuie sa il pun in varf

"""
Mai jos puteti comenta si decomenta apelurile catre algoritmi. Pentru moment e apelat doar breadth-first
"""

# print("====================================================== \nBreadthfirst")
# breadth_first(gr, nrSolutiiCautate=4)
# print("====================================================== \nDepthFirst recursiv")
# depth_first(gr, nrSolutiiCautate=4)
# print("====================================================== \nDepthFirst nerecursiv")
# df_nerecursiv(nrSolutiiCautate=4)
aStarSolMultiple(gr, nrSolutiiCautate=2)
aStarSolMultiplePQ(gr, nrSolutiiCautate=2)

cProfile.run("aStarSolMultiple(gr, nrSolutiiCautate=2)")
# 183 function calls (164 primitive calls) in 0.001 seconds

cProfile.run("aStarSolMultiplePQ(gr, nrSolutiiCautate=2)")
# 353 function calls in 0.001 seconds

time1 = time.time()
aStarSolMultiple(gr, nrSolutiiCautate=2)
print(time1)        # 1678417043.4935997

time2 = time.time()
aStarSolMultiplePQ(gr, nrSolutiiCautate=2)
print(time2)        # 1678417043.4935997

