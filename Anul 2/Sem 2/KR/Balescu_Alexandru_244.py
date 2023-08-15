import copy
import sys
from queue import PriorityQueue

class Nod:
    def __init__(self, info, g = 0, h = 0, parinte=None):
        self.info = info  # eticheta nodului
        self.parinte = parinte  # parintele din arborele de parcurgere
        self.g = g  # costul drumului de la radacina pana la nodul curent
        self.h = h  # costul estimat de la nodul curent pana la nodul scop
        self.f = self.g + self.h  # costul total (f = g + h)

    def __repr__(self):
        sir = ""
        sir += str(self.info) + "\n"
        return (sir)

    def __str__(self):
        sir=""
        for linie in self.info:
            sir+=" ".join([str(elem) for elem in linie])+"\n"
        sir+="\n"
        return sir

    def drumRadacina(self):
        l = []
        while self is not None:
            l.insert(0, self)
            self = self.parinte  # trec la parintele din arborele de parcurgere
        return l

    # returneaza si costul si lungimea drumului
    def afisDrum(self, afisCost=False, afisLung=False): #returneaza si lungimea drumului
        l=self.drumRadacina()
        for nod in l:
            print(str(nod))
        if afisCost:
            print("Cost: ", self.g)
        if afisLung:
            print("Lungime: ", len(l))
        #return len(l)
        return l


    # verifică dacă nodul a fost vizitat (informatia lui e in propriul istoric)
    def vizitat(self):
        nodDrum = self.parinte
        while nodDrum:
            if (self.info == nodDrum.info):
                return True
            nodDrum = nodDrum.parinte

        return False



class Graph:  # graful problemei

     def __init__(self, nume_fisier):
         #citire din fisier
         f = open (nume_fisier, "r")
         linii = f.read().strip().split("\n")
         self.start = []
         for linie in linii:
            self.start.append([int(x) for x in linie.strip().split(" ")])
         # starea finala cand toate piesele sunt pe pozitiile bune
         self.scopuri = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    # validare configuratie initiala
     def valideaza(self):
         frecv = [0, 0, 0, 0, 0, 0, 0, 0, 0]
         # verificam daca avem 3 linii
         if len(self.start) != 3:
             return False
         # verificam daca avem 3 elemente pe fiecare linie
         for linie in self.start:
             if len(linie) != 3:
                 return False
             for x in linie: # verificam daca avem elemente de la 0 la 8
                 frecv[x] = frecv[x] + 1
        # verificam daca avem fiecare element o singura data
         for i in range(0, 9):
             if frecv[i] != 1:
                 return False

         # verificam daca numarul de inversiuni este par
         # Numărul de inversiuni = numărul de perechi ( ni ,  nj ) nenule cu  ni>nj  și  i<j
         inversions = []
         inv = 0
         for linie in self.start:
             for x in linie:
                inversions.append(x)
         # matricea desfășurată ca un vector (concatenând liniile între ele)
         for i in range(0, 9):
             for j in range(i+1, 9):
                 if inversions[i] != 0 and inversions[j] != 0:
                     if inversions[i] > inversions[j]:
                         inv += 1
         if inv % 2 != 0:
             return False
         return True


     def succesori(self, nodCurent, tip_euristica="euristica banala"):

        # un succesor inseamna o mutare in care elementru 0 isi schimba pozitie
        # elementu 0 se interschimba deci cu un element care se afla la N, S, E, V de el
        # pentru configuratia data ca exemplu, am avea ca succesori urmatoarele configuratii
        # initial       succ1       succ2       succ3
        # 2 6 4     |   2 6 4   |   2 6 4   |   2 6 4
        # 7 8 1     |   7 8 1   |   7 8 1   |   7 0 1
        # 5 0 3     |   0 5 3   |   5 3 0   |   5 8 3

        listaSuccesori = []
        (i, j) = (-1, -1)   # pozitia pe care putem sa facem o mutare
        # cautam pozitia pe care se afla elementul 0
        for x in range(0, 3):
            for y in range(0, 3):
                if nodCurent.info[x][y] == 0:
                    (i, j) = (x, y)

        directions = [[i, j-1], [i, j+1], [i+1, j], [i-1, j]]    # N, S, E , V
        for (dirX, dirY) in directions:
            # verificam daca putem face o mutare in directia respectiva
            if 0 <= dirX < 3 and 0 <= dirY < 3:
                new_mat = copy.deepcopy(nodCurent.info) # copiem matricea
                new_mat[i][j], new_mat[dirX][dirY] = new_mat[dirX][dirY], new_mat[i][j] # interschimbam elementele

                if not nodCurent.vizitat(): # daca nu am mai vizitat configuratia
                    cost = 1 # costul unei mutari
                    listaSuccesori.append(Nod(new_mat,
                                              nodCurent.g + cost, # costul de la nodul de start la nodul curent + costul unei mutari
                                              self.estimeaza_h(new_mat, tip_euristica), # euristica in fct de care se estimeaza costul de la nodul curent la nodul succesor
                                              nodCurent))
        return listaSuccesori

     def scop(self, infoNod):
        return infoNod == self.scopuri

     def estimeaza_h(self, infoNod, tip_euristica="euristica banala"):

         #euristica banală: daca nu e stare scop, returnez 1, altfel 0
        if tip_euristica=="euristica banala":
            if infoNod not in self.scopuri:
                return 1 #se pune costul minim pe o mutare
            return 0

        elif tip_euristica == "euristica mutari":
            #calculez cate blocuri nu sunt la locul lor fata de fiecare dintre starile scop,
            #si apoi iau minimul dintre aceste valori
            euristici=[]
            for (iScop,scop) in enumerate(self.scopuri): #enumerate imi da si indicele elementului; iScop rep indicele scopului curent
                h=0
                for (iStiva, stiva) in enumerate(infoNod): #iStiva rep indicele stivei curente din infoNod (lista de liste)
                        for iElem, elem in enumerate(stiva): # iElem rep indicele elementului curent din stiva curenta
                            try:
                                #exista în stiva scop indicele iElem dar pe acea pozitie nu se afla blocul din infoNod
                                if elem!=scop[iStiva][iElem]:
                                    h+=1 #adun cu costul minim pe o mutare
                            except IndexError:
                                #nici macar nu exista pozitia iElem in stiva cu indicele iStiva din scop
                                h+=1
                euristici.append(h)
            return min(euristici)

        elif tip_euristica == "euristica mutari cost":

            euristici=[]
            for (iScop,scop) in enumerate(self.scopuri):
                h=0
                for (iStiva, stiva) in enumerate(infoNod):
                        for (iElem, elem) in enumerate(stiva):
                            try:
                                #exista în stiva scop indicele iElem dar pe acea pozitie nu se afla blocul din infoNod
                                if elem != scop[iStiva][iElem]:
                                    h += 1
                                else:  # elem==scop[iStiva][iElem]:
                                    if stiva[:iElem]!=scop[iStiva][:iElem]: # daca un rand nu are toate elementele la locul lor atunci costul creste
                                     h += 2
                            except IndexError:
                                #nici macar nu exista pozitia iElem in stiva cu indicele iStiva din scop
                                h += 1
                euristici.append(h)
            return min(euristici)

        elif tip_euristica == "euristica neadmisibila":
            euristici=[]
            # Supraestimez costurile mutarilor
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
    c = [Nod(gr.start)]

    while len(c) > 0:
        #print("Coada actuala: " + str(c))
        nodCurent = c.pop(0)

        if gr.scop(nodCurent.info):
            print("Solutie:")
            drum = nodCurent.drumRadacina()
            print(("        \/      \n").join([str(n.info)+"\n" for n in drum]))
            print("\n----------------\n")
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        c += gr.succesori(nodCurent)


gr = Graph("input.txt")
print(gr)
start = gr.start
print(gr.succesori(Nod(gr.start)), sep="\n")
print("\nSolutii obtinute cu BF\n")
breadth_first(gr)