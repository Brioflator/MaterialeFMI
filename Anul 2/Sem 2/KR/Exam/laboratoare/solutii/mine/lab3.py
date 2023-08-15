from queue import PriorityQueue
import cProfile
import time

class NodArbore:
    def __init__(self, info, parinte=None, g=0, h=0):
        self.info = info
        self.parinte = parinte
        self.g = g
        self.h = h
        self.f = g+h

    def drumRadacina(self):
        l = []
        nod = self
        while nod is not None:
            l.insert(0, nod)
            nod = nod.parinte
            return l

    def vizitat(self):
        nod = self.parinte
        while nod is not None:
            if nod.info == self.info:
                return True
            nod = nod.parinte
        return False

    def __str__(self):
        return "{} ({}, {})".format(self.info, self.g, self.f)

    def __repr__(self):
        return "({}, ({}), cost:{})".format(self.info, "->".join([str(x) for x in self.drumRadacina()]), self.f)

    def __eq__(self, other):
        return self.g + self.h == other.g + other.h

    def __lt__(self, other):
        return (self.g + self.h < other.g + other.h) or ((self.g + self.h == other.g + other.h) and (self.g > other.g))


class Graf:
    def __init__(self, matr, start, scopuri, h):
        self.matr = matr
        self.start = start
        self.scopuri = scopuri
        self.estimari = h

    def scop(self, infoNod):
        return infoNod in self.scopuri

    def succesori(self, nod):
        l = []
        for i in range(len(self.matr)):
            if self.matr[nod.info][i] > 0:
                nodNou = NodArbore(i, nod, nod.g+self.matr[nod.info][i], self.calculeaza_h(i))
                if not nodNou.vizitat():
                    l.append(nodNou)
        return l

    def calculeaza_h(self, info):
        return self.estimari[info]


def bin_search(listaNoduri, nodNou, ls, ld):
    if len(listaNoduri) == 0:
        return 0
    if ls == ld:
        if nodNou.f < listaNoduri[ls].f:
            return ls
        elif nodNou.f > listaNoduri[ls].f:
             return ld+1
        else: # f-uri egale
            if nodNou.g < listaNoduri[ls].g:
                return ld + 1
            else:
                return ls
    else:
        mij = (ls+ld)//2
        if nodNou.f < listaNoduri[mij].f:
            return bin_search(listaNoduri, nodNou, ls, mij)
        elif nodNou.f > listaNoduri[mij].f:
            return bin_search(listaNoduri, nodNou, mij+1, ld)
        else:
            if nodNou.g < listaNoduri[mij].g:
                return bin_search(listaNoduri, nodNou, mij + 1, ld)
            else:
                return bin_search(listaNoduri, nodNou, ls, mij)


def aStarSolMultiple(gr, nrSolutiiCautate=1):
# in coada vom avea doar noduri de tip NodArbore (nodurile din arborele de parcurgere)
    c = [NodArbore(gr.start)]
    while len(c) > 0:
    # print("Coada actuala: " + str(c))
    # input()
        nodCurent = c.pop(0)
        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print("->".join([str(n.info) for n in drum]))
            print("cost:", nodCurent.g)
            print("\n----------------\n")
            # input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
            # [2,4,7,8,10,14]
            # c+=gr.succesori(nodCurent)
        for s in gr.succesori(nodCurent):
            indice = bin_search(c, s, 0, len(c)-1)
            if indice == len(c):
                c.append(s)
            else:
                c.insert(indice, s)


def aStarSolMultiplePQ(gr, nrSolutiiCautate=1):
    c = PriorityQueue()
    c.put(NodArbore(gr.start))

    while not c.empty():
        #print("Coada actuala: " + str(c))
        #input()
        nodCurent = c.get()

        if gr.scop(nodCurent.info):
            print("SolutiePQ:")
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

m = [
    [0, 3, 5, 10, 0, 0, 100],
    [0, 0, 0, 4, 0, 0, 0],
    [0, 0, 0, 4, 9, 3, 0],
    [0, 3, 0, 0, 2, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 4, 0, 5],
    [0, 0, 3, 0, 0, 0, 0],
    ]

start = 0
scopuri = [4, 6]
h = [0, 1, 6, 2, 0, 3, 0]

gr = Graf(m, start, scopuri, h)
#aStarSolMultiple(gr, nrSolutiiCautate=3)
#aStarSolMultiplePQ(gr, nrSolutiiCautate=2)

cProfile.run("aStarSolMultiple(gr, nrSolutiiCautate=2)")
# 186 function calls (171 primitive calls) in 0.001 seconds

cProfile.run("aStarSolMultiplePQ(gr, nrSolutiiCautate=2)")
# 353 function calls in 0.001 seconds

time1 = time.time()
aStarSolMultiple(gr, nrSolutiiCautate=2)
print(time1)        # 1683706835.7305527
print()
time2 = time.time()
aStarSolMultiplePQ(gr, nrSolutiiCautate=2)
print(time2)        # 1678417043.4935997

