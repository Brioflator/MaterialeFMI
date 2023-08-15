import copy
import sys
from queue import PriorityQueue

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
        while nod is not None:
            l.insert(0, nod)
            nod = nod.parinte
        return l

    def afisDrum(self, afisCost=False, afisLung=False): #returneaza si lungimea drumului
        l=self.drumRadacina()
        for nod in l:
            print(str(nod))
        if afisCost:
            print("Cost: ", self.g)
        if afisLung:
            print("Lungime: ", len(l))
        return l


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

    def __repr__(self):
        sir=""
        sir+=str(self.info)
        return sir

    def __str__(self):
        sir=""
        for linie in self.info:
            sir+=" ".join([str(elem) for elem in linie])+"\n"
        sir+="\n"
        return sir


class Graph:  # graful problemei

     def __init__(self, nume_fisier):
         f = open (nume_fisier, "r")
         linii = f.read().strip().split("\n")
         self.start = []
         for linie in linii:
            self.start.append([int(x) for x in linie.strip().split(" ")])
         self.scopuri = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

     def valideaza(self):
         frecv = [0, 0, 0, 0, 0, 0, 0, 0, 0]
         if len(self.start) != 3:
             return False
         for linie in self.start:
             if len(linie) != 3:
                 return False
             for x in linie:
                 frecv[x] = frecv[x] + 1
         for i in range(0, 9):
             if frecv[i] != 1:
                 return False
         inversions = []
         inv = 0
         for linie in self.start:
             for x in linie:
                inversions.append(x)
         for i in range(0, 9):
             for j in range(i+1, 9):
                 if inversions[i] != 0 and inversions[j] != 0:
                     if inversions[i] > inversions[j]:
                         inv += 1
         if inv % 2 != 0:
             return False
         return True


     def succesori(self, nodCurent, tip_euristica="euristica banala"):
        listaSuccesori=[]
        # un succesor inseamna o mutare in care elementru 0 isi schimba pozitie
        # elementu 0 se interschimba deci cu un element care se afla la N, S, E, V de el
        # pentru configuratia data ca exemplu, am avea ca succesori urmatoarele configuratii
        # initial       succ1       succ2       succ3
        # 2 6 4     |   2 6 4   |   2 6 4   |   2 6 4
        # 7 8 1     |   7 8 1   |   7 8 1   |   7 0 1
        # 5 0 3     |   0 5 3   |   5 3 0   |   5 8 3
        (i, j) = (-1, -1)   # pozitia pe care putem sa facem o mutare
        for x in range(0, 3):
            for y in range(0, 3):
                if self.start[x][y] == 0:
                    (i, j) = (x, y)
        directions = [[i, j-1], [i, j+1], [i+1, j], [i-1, j]]    # N, S, E , V
        for dirX, dirY in directions:
            if 0 <= dirX < 3 and 0 <= dirY < 3:
                new_mat = copy.deepcopy(nodCurent.info)
                new_mat[i][j] = new_mat[dirX][dirY]
                new_mat[dirX][dirY] = 0
                if not nodCurent.vizitat():
                    cost = 1
                    listaSuccesori.append(NodParcurgere(new_mat,
                                          nodCurent.g + cost,
                                          self.estimeaza_h(new_mat, tip_euristica),
                                          nodCurent))
        return listaSuccesori

     def scop(self, infoNod):
        return infoNod == self.scopuri

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
        elif tip_euristica == "euristica mutari cost":
            euristici=[]
            for (iScop,scop) in enumerate(self.scopuri):
                h=0
                for iStiva, stiva in enumerate(infoNod):
                        for iElem, elem in enumerate(stiva):
                            try:
                                #exista în stiva scop indicele iElem dar pe acea pozitie nu se afla blocul din infoNod
                                if elem != scop[iStiva][iElem]:
                                    h += 1
                                else:  # elem==scop[iStiva][iElem]:
                                    if stiva[:iElem]!=scop[iStiva][:iElem]:
                                     h += 2
                            except IndexError:
                                #nici macar nu exista pozitia iElem in stiva cu indicele iStiva din scop
                                h += 1
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
        c += gr.succesori(nodCurent)


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

def expandeaza(gr, nodCurent, g, limita, path):
    f = g + gr.estimeaza_h(nodCurent.info)
    if f > limita:
        return f
    if gr.scop(nodCurent):
        return "FOUND"
    min = sys.maxsize * 2 + 1
    LS = gr.succesori(nodCurent)
    for succ in LS:
        if succ not in path:
            path.append(succ)
            t = expandeaza(gr, succ, g + 1, limita, path)
            if t == "FOUND":
                return "FOUND"
            if t < min:
                min = t
            path.pop()
    return min



def IDA (gr,  nrSolutiiCautate = 3):
    limita = gr.estimeaza_h(gr.start)
    path = [NodParcurgere(gr.start)]
    while True:
        t = expandeaza(gr, path[len(path)-1], 0, limita, path)
        if t == "FOUND":
            return (path, limita)
        if t == sys.maxsize * 2 + 1:
            return "NOT FOUND"
        limita = t


gr = Graph("input.txt")
print(gr)
start = gr.start
print(gr.succesori(NodParcurgere(gr.start)), sep="\n")
print("\nSolutii obtinute cu BF\n")
breadth_first(gr, nrSolutiiCautate=3)

print("\nSolutii obtinute cu DF\n")
depth_first(gr, nrSolutiiCautate=3)
IDA(gr)