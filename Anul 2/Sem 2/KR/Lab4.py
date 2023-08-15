import copy


class Nod:
    def __init__(self, info, parinte=None, g=0, h=0):
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
        # afisez stivele aranjate vertical
        sir = ""
        maxInalt = max([len(stiva) for stiva in self.info]) # inaltimea maxima a unei stive
        for inalt in range(maxInalt, 0, -1):
            for stiva in self.info:
                if len(stiva) < inalt:
                    sir += "  "
                else:
                    sir += stiva[inalt - 1] + " "
            sir += "\n"
        sir += "-" * (2 * len(self.info) - 1)
        return sir

    # va returna o listă cu toate nodurile ca obiecte de la rădăcină până la nodul curent
    def drumRadacina(self):
        l = []
        while self is not None:
            l.insert(0, self)
            self = self.parinte  # trec la parintele din arborele de parcurgere
        return l

    # returneaza si costul si lungimea drumului
    def afisDrum(self, afisCost=False, afisLung=False):
        l = self.drumRadacina()
        for nod in l:
            print(str(nod))
        if afisCost:
            print("Cost: ", self.g)
        if afisLung:
            print("Lungime: ", len(l))
        return len(l)

    def contineInDrum(self, infoNodNou):
        nodDrum = self
        while nodDrum is not None:
            if infoNodNou == nodDrum.info:
                return True
            nodDrum = nodDrum.parinte
        return False


class Graf:
    def __init__(self, fis):

        # folosesc strip ca sa scap de spatii, daca exista
        def obtineStive(sir):
            stiveSiruri = sir.strip().split("\n")
            return [sirStiva.strip().split() if sirStiva != "." else [] for sirStiva in stiveSiruri]

        # transforma stivele din lista de siruri de caractere in lista de liste de caractere
        def transf(stiva):
            s = ""
            for x in stiva:
                for y in x:
                    s += y
            return s

        # verifica daca stivele au aceleasi blocuri
        def validare2(stiva1, stiva2):
            s1 = set(transf(stiva1))
            s2 = set(transf(stiva2))
            if s1 == s2:
                return True
            return False

        # verifica daca stivele au aceeasi lungime
        def validare(stari):
            ok = 1
            l = len(obtineStive(stari[0]))
            for s in stari:
                if len(obtineStive(s)) != l:
                    ok = 0
            return ok

        # citirea
        f = open(fis, 'r')
        continutFis = f.read()
        stari = continutFis.strip().split("---")
        if validare(stari) == 1:
            self.start = obtineStive(stari[0])
            print("Stare Initiala:", self.start)
            self.scopuri = []
            k = 1
            ok = 1
            while k < len(stari):
                self.scopuri.append(obtineStive(stari[k]))
                if validare2(self.start, obtineStive(stari[k])) == False:
                    ok = 0
                k += 1
            if ok == 1:
                print("Stari finale posibile:", self.scopuri)
            else:
                print("Fisier invalid")
        else:
            print("Fisier invalid")

    def __repr__(self):
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return (sir)

    def testeaza_scop(self, nodCurent, euristica="default"):
        if euristica == "default":
            return nodCurent.info in self.scopuri

    def calculeaza_h_banal(self, infoNod):
        if infoNod not in self.scopuri:
            return 1
        return 0

    # va genera succesorii sub forma de noduri in arborele de parcurgere

    def Succesori(self, nodCurent, tip_euristica="euristica banala"):
        lSuccesori = []
        stive_c = nodCurent.info  # stivele din nodul curent
        nr_stive = len(stive_c)
        for i in range(nr_stive):  # indicele stivei de pe care iau bloc
            if len(stive_c[i]) == 0:
                continue
            copie_intermediara = copy.deepcopy(stive_c)
            bloc = copie_intermediara[i].pop()  # iau varful stivei
            for j in range(nr_stive):  # indiciele unde vreau sa pun blocul
                if i == j:  # verific sa nu pun blocul de unde l-am luat
                    continue
                stive_n = copy.deepcopy(copie_intermediara)  # lista noua de stive
                stive_n[j].append(bloc)  # pun blocul
                costMutareBloc = 1 + ord(bloc) - ord("a")  # indexul pt bloc
                if not nodCurent.contineInDrum(stive_n):
                    nod_nou = Nod(stive_n, nodCurent, g=nodCurent.g + costMutareBloc,
                                  h=self.calculeaza_h_banal(stive_n))
                    lSuccesori.append(nod_nou)
        return lSuccesori


def bfs(g, nrSolutiiCautate=1):
    # in coada vom avea doar noduri de tip Nod (nodurile din arborele de parcurgere)
    q = [Nod(g.start, None)]

    while len(q) > 0:
        nodCurent = q.pop(0)

        if g.testeaza_scop(nodCurent):
            print("Solutie:")
            nodCurent.afisDrum(afisCost=True, afisLung=True)
            print("----------------\n")
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return
        lSuccesori = g.Succesori(nodCurent)
        q+=lSuccesori

g = Graf("input.txt")

bfs(g)