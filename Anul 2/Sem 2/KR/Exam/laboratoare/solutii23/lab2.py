# lab 1 KR

# problema 1
#Definiți o clasa Nod, care va reprezenta un nod dintr-un arbore de parcurgere,
# cu câmpurile: informatie, parinte (care e un obiect de tip Nod).
# In constructor, vom defini pentru parinte ca valoare implicită None.
class Nod:
    def __init__(self, info, par = None):
        self.informatie = info
        self.parinte = par
    # drumRadacina() care va returna o listă cu toate nodurile ca obiecte
    # (nu informatia nodurilor) de la rădăcină până la nodul curent
    def drumRadacina(self):
        nod_aux = self
        tata = []
        while nod_aux.parinte != None:
            tata.append(nod_aux.parinte)
            nod_aux = nod_aux.parinte
        return tata
    #vizitat() care verifică dacă nodul a fost vizitat pe drumul curent
    # (deci nu în tot arborele) caz în care returnează True, altfel
    # (dacă nu a fost vizitat) False.
    # Reformulat: dacă informația se mai găsește în drumul de dinaintea
    # nodului curent, returnăm True.

    def vizitat(self):
        nodDrum = self.parinte
        while nodDrum:
            if (self.informatie == nodDrum.informatie):
                return True
            nodDrum = nodDrum.parinte
        return False

    # funcția __repr__  care va returna un string continand informatia nodului,
    # urmata de un spatiu, urmat de o paranteză în care se află tot drumul
    # de la rădăcină până la acel nod). De exemplu "c (a->b->c)"
    # unde c e informația nodului curent și a,b,c sunt informațiile
    # nodurilor din drumul de la rădăcină(a) către el.

    def __repr__(self):
        sir = str(self.informatie) + "("
        drum = self.drumRadacina()
        sir += ("->").join([str(n.informatie) for n in drum])
        sir += ")"
        return sir

    # funcția __str__ care va returna un string doar cu informația nodului
    def __str__(self):
        return str(self.informatie)


class Graph:
    # un constructor prin care se transmit informațiile grafului.
    def __init__(self, n, m, start, scopuri):
        self.N = n
        self.M = m
        self.start = Nod(start)  # informatia nodului de start
        self.scopuri = scopuri  # lista cu informatiile nodurilor scop

    # o metoda scop(informatieNod) care primește o informație de nod
    # și verifică dacă e nod scop
    def scop(self, infoNod):
        return infoNod in self.scopuri

    # o metoda (care va fi folosită în algoritmi pentru generarea arborelui
    # de căutare), numită  succesori(nod) care primește un nod al arborelui
    # de parcurgere și parcurge nodurile adiacente din graf, returnand o
    # lista de obiecte de clasa Nod ce reprezinta sucesori direcți ai
    # nodului (care vor fi fii în arborele de căutare), care nu au fost
    # vizitati pe ramura curentă. Toți succesorii vor avea, evident,
    # parintele egal cu nod
    def succesori(self, nodCurent):

        def conditie(mis, can):
            return mis == 0 or mis >= can

        listaSuccesori = []
        # (canibali mal st, misionari mal st, barca) -- barca = 1 mal initial, barca = 0 mal final
        # mal curent = mal cu barca
        # mal opus = mal spre care vine barca
        #print(type(nodCurent.informatie), nodCurent.informatie, end= "\n\n")
        if nodCurent.informatie[2] == 1:
            canMalCurent = nodCurent.informatie[0]
            misMalCurent = nodCurent.informatie[1]
            canMalOpus = self.N - canMalCurent
            misMalOpus = self.N - misMalCurent
        else:
            canMalOpus = nodCurent.informatie[0]
            misMalOpus = nodCurent.informatie[1]
            canMalCurent = self.N - canMalOpus
            misMalCurent = self.N - misMalOpus

        maxMisionariBarca = min(self.M, misMalCurent)
        for misBarca in range(maxMisionariBarca + 1):
            if misBarca == 0:
                minCanBarca = 1
                maxCanBarca = min(self.M, canMalCurent)
            else:
                minCanBarca = 0
                maxCanBarca = min(self.M-misBarca, canMalCurent, misBarca)

            for canBarca in range(minCanBarca, maxCanBarca + 1):
                canMalCurentNou = canMalCurent - canBarca
                misMalCurentNou = misMalCurent - misBarca
                canMalOpusNou = canMalOpus + canBarca
                misMalOpusNou = misMalOpus + misBarca

                if not conditie(misMalCurentNou, canMalCurentNou):
                    continue
                if not conditie(misMalOpusNou, canMalOpusNou):
                    continue
                if not conditie(misBarca, canBarca):
                    continue

                if nodCurent.informatie[2] == 1:
                    nodNou = Nod((canMalCurentNou, misMalCurentNou, 0), nodCurent)
                else:
                    nodNou = Nod((canMalOpusNou, misMalOpusNou, 1), nodCurent)

                if not nodNou.vizitat():
                    listaSuccesori.append(nodNou)

        return listaSuccesori


# problema 2
# Implementați tehnica de căutare Breadthfirst, folosind clasele Nod și
# Graf definite mai sus. Se va citi de la tastatură un număr NSOL de soluții.
# se vor afișa primele NSOL soluții.


def breadth_first(gr, nrSolutiiCautate=1):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [gr.start]

    while len(c) > 0:
        print("Coada actuala: " + str(c))
        #input()
        nodCurent = c.pop(0)

        if gr.scop(nodCurent.informatie):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.informatie) for n in drum]))
            print("\n----------------\n")
            #input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        c+=gr.succesori(nodCurent)


def depth_first(gr, nrSolutiiCautate=1):
    # vom simula o stiva prin relatia de parinte a nodului curent
    df(Nod(gr.start), nrSolutiiCautate)


def df(nodCurent, nrSolutiiCautate):
    if nrSolutiiCautate <= 0:  # testul acesta s-ar valida doar daca in apelul initial avem df(start,if nrSolutiiCautate=0)
        return nrSolutiiCautate
    #print("Stiva actuala: " + repr(nodCurent.drumRadacina()))
    #input()
    if gr.scop(nodCurent.informatie):
        print("Solutie: ", end="")
        drum = nodCurent.drumRadacina()
        print(("->").join([str(n.informatie) for n in drum]))
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


def df_nerecursiv(nrSolutiiCautate):
    stiva = [Nod(gr.start)]
    #consider varful stivei in dreapta
    while stiva: #cat timp stiva nevida
        nodCurent=stiva.pop() #sterg varful
        if gr.scop(nodCurent.informatie):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.informatie) for n in drum]))
            print("\n----------------\n")
            #input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        stiva+=gr.succesori(nodCurent)[::-1] #adaug in varf succesoii in ordine inversa deoarece vreau sa expandez primul succesor generat si trebuie sa il pun in varf


f = open("input.txt", "r")
continut = f.read().split()
n = int(continut[0])
m = int(continut[1])
start = (n, n, 1)
scopuri = [(0, 0, 0)]
gr = Graph(n, m, start, scopuri)
breadth_first(gr, nrSolutiiCautate=2)


