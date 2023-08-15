import copy
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

    def obtineDrum(self):
        l=[self];
        nod=self
        while nod.parinte is not None:
            l.insert(0, nod.parinte)
            nod=nod.parinte
        return l

    def drumRadacina(self):
        l = []
        nod = self
        while nod:
            l.insert(0, nod)
            nod = nod.parinte
        return l

    def afisDrum(self, afisCost=False, afisLung=False): #returneaza si lungimea drumului
        l=self.obtineDrum()
        for nod in l:
            print(str(nod))
        if afisCost:
            print("Cost: ", self.g)
        if afisLung:
            print("Lungime: ", len(l))
        return len(l)


    def contineInDrum(self, infoNodNou):
        nodDrum=self
        while nodDrum is not None:
            if(infoNodNou==nodDrum.info):
                return True
            nodDrum=nodDrum.parinte

        return False

    def vizitat(self): #verifică dacă nodul a fost vizitat (informatia lui e in propriul istoric)
        nodDrum = self.parinte
        while nodDrum:
            if (self.info == nodDrum.info):
                return True
            nodDrum = nodDrum.parinte

        return False

    def __str__(self):
         """Afiseaza stivele aranjate vertical"""
         sir=""
         maxInalt=max([len(stiva) for stiva in self.info])
         for inalt in range(maxInalt, 0, -1):
             for stiva in self.info:
                 if len(stiva)< inalt:
                     sir += "  "
                 else:
                     sir+=stiva[inalt-1]+" "
             sir+="\n"
         sir+="-"*(2*len(self.info)-1)
         return sir

    def __repr__(self):
        sir=""
        sir+=str(self.info)
        return(sir)

    def __eq__(self, other):
        return self.g + self.h == other.g + other.h

    def __lt__(self, other):
        return (self.g + self.h < other.g + other.h) or ((self.g + self.h == other.g + other.h) and (self.g > other.g))

class Graph:  # graful problemei

     def __init__(self, nume_fisier):

        def obtineStive(sir):
            stiveSiruri=sir.strip().split("\n") #["a","c b","d"]
            listaStive=[sirStiva.strip().split() if sirStiva !="#" else [] for sirStiva in stiveSiruri]
            return listaStive


        f = open(nume_fisier, 'r')

        continutFisier=f.read() #citesc tot continutul fisierului
        siruriStari=continutFisier.strip().split("=========")
        self.start=obtineStive(siruriStari[0]) #[["a"], ["c","b"],["d"]]
        self.scopuri=[]
        siruriStariFinale=siruriStari[1].strip().split("---")
        for scop in siruriStariFinale:
            self.scopuri.append(obtineStive(scop))
        print("Stare Initiala:", self.start)
        print("Stari finale posibile:",self.scopuri)

     def valideaza(self):
         nrBlocuri_start = len(self.start[0])
         for listaStiva in self.scopuri:
             if len(listaStiva) != nrBlocuri_start:
                 return False
         return True

     def succesori(self, nodCurent, tip_euristica="euristica banala"):
        listaSuccesori=[]
        stive_c=nodCurent.info # stivele din nodul curent
        nr_stive=len(stive_c)
        for idx in range(nr_stive):#idx= indicele stivei de pe care iau bloc
            if len(stive_c[idx])==0 :
                continue
            copie_interm=copy.deepcopy(stive_c)
            bloc=copie_interm[idx].pop() #iau varful stivei
            for j in range(nr_stive): #j = indicele stivei pe care pun blocul
                if idx == j: # nu punem blocul de unde l-am luat
                    continue
                stive_n=copy.deepcopy(copie_interm)#lista noua de stive
                stive_n[j].append(bloc) # pun blocul
                costMutareBloc=1+ord(bloc)-ord("a")   # indexul pt bloc
                if not nodCurent.contineInDrum(stive_n):
                    nod_nou=NodParcurgere(info = stive_n,
                                          g=nodCurent.g+costMutareBloc,
                                          h= self.estimeaza_h(stive_n, tip_euristica),
                                          parinte=nodCurent)
                    listaSuccesori.append(nod_nou)
        return listaSuccesori

     def scop(self, infoNod):
        return infoNod in self.scopuri

     def estimeaza_h (self, infoNod, tip_euristica="euristica banala"):
         #euristica banală: daca nu e stare scop, returnez 1, altfel 0
        if tip_euristica=="euristica banala":
            if infoNod not in self.scopuri:
                return 1 #se pune costul minim pe o mutare
            return 0
        elif tip_euristica == "euristica mutari":
            #calculez cate blocuri nu sunt la locul fata de fiecare dintre starile scop,
            #si apoi iau minimul dintre aceste valori
            euristici=[]
            for (iScop,scop) in enumerate(self.scopuri):
                h=0
                for iStiva, stiva in enumerate(infoNod):
                        for iElem, elem in enumerate(stiva):
                            try:
                                #exista în stiva scop indicele iElem dar pe acea pozitie nu se afla blocul din infoNod
                                if elem!=scop[iStiva][iElem]:
                                    h+=1 #adun cu costul minim pe o mutare (adica costul lui a)
                            except IndexError:
                                #nici macar nu exista pozitia iElem in stiva cu indicele iStiva din scop
                                h+=1
                euristici.append(h)
            return min(euristici)
        elif tip_euristica == "euristica costuri":
            #calculez cate blocuri nu sunt la locul fata de fiecare dintre starile scop,
            #si apoi iau minimul dintre aceste valori
            euristici=[]
            for (iScop,scop) in enumerate(self.scopuri):
                h=0
                for iStiva, stiva in enumerate(infoNod):
                        for iElem, elem in enumerate(stiva):
                            try:
                                #exista în stiva scop indicele iElem dar pe acea pozitie nu se afla blocul din infoNod
                                if elem!=scop[iStiva][iElem]:
                                    h+=1
                                else: # elem==scop[iStiva][iElem]:
                                    if stiva[:iElem]!=scop[iStiva][:iElem]:
                                     h+=2
                            except IndexError:
                                #nici macar nu exista pozitia iElem in stiva cu indicele iStiva din scop
                                h+=1
                euristici.append(h)
            return min(euristici)
        elif tip_euristica == "euristica neadmisibila":
            euristici=[]
            # Supraestimez costurile
            for (iScop,scop) in enumerate(self.scopuri):
                h=0
                for iStiva, stiva in enumerate(infoNod):
                        for iElem, elem in enumerate(stiva):
                            try:
                                #exista în stiva scop indicele iElem dar pe acea pozitie nu se afla blocul din infoNod
                                if elem!=scop[iStiva][iElem]:
                                    h+=3
                                else: # elem==scop[iStiva][iElem]:
                                    if stiva[:iElem]!=scop[iStiva][:iElem]:
                                        h+=2
                            except IndexError:
                                #nici macar nu exista pozitia iElem in stiva cu indicele iStiva din scop
                                h+=3
                euristici.append(h)
            return max(euristici)
        else:
            return "caz de euristica netratat"

     def __repr__(self):
        sir=""
        for (k,v) in self.__dict__.items() :
            sir+="{} = {}\n".format(k,v)
        return(sir)




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
#gr = Graph(m, start, scopuri, h_part)


#### algoritm BF
# presupunem ca vrem mai multe solutii (un numar fix) prin urmare vom folosi o variabilă numită nrSolutiiCautate
# daca vrem doar o solutie, renuntam la variabila nrSolutiiCautate
# si doar oprim algoritmul la afisarea primei solutii

def breadth_first(gr, nrSolutiiCautate=1):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.start)]

    while len(c) > 0:
        #print("Coada actuala: " + str(c))
        nodCurent = c.pop(0)

        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("->").join([str(n.info) for n in drum]))
            print("\n----------------\n")
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

def aStarSolMultiple(gr, nrSolutiiCautate=1, tip_euristica = "euristica banala"):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [NodParcurgere(gr.start, 0, gr.estimeaza_h(gr.start), None)]

    while len(c) > 0:
        nodCurent = c.pop(0)

        if gr.scop(nodCurent.info):
            print("Solutie: ")
            nodCurent.afisDrum(afisCost=True, afisLung=True)
            print("\n----------------\n")
            input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        for succ in gr.succesori(nodCurent, tip_euristica):
            i=0
            gasit_loc=False
            for i in range(len(c)):
                if c[i].f>=succ.f:
                    gasit_loc = True
                    break
                if gasit_loc:
                    c.insert(i, succ)
                else:
                    c.append(succ)
    return c

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
#
# aStarSolMultiple(gr, nrSolutiiCautate=2)
# aStarSolMultiplePQ(gr, nrSolutiiCautate=2)
# cProfile.run("aStarSolMultiple(gr, nrSolutiiCautate=2)") # 183 function calls (164 primitive calls) in 0.001 seconds
# cProfile.run("aStarSolMultiplePQ(gr, nrSolutiiCautate=2)") # 353 function calls in 0.001 seconds
#
# time1 = time.time()
# aStarSolMultiple(gr, nrSolutiiCautate=2)
# print(time1)  # 1678448479.3920054
#
# time2 = time.time()
# aStarSolMultiplePQ(gr, nrSolutiiCautate=2)
# print(time2)  # 1678448479.3920054


###############################
gr = Graph("input_blocuri.txt")

print(gr)
print("Solutii obtinute cu breadth first:")
breadth_first(gr, nrSolutiiCautate=3)
print(gr.estimeaza_h(start, "euristica banala"))
