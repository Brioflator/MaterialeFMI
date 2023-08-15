class NodArbore:
    def __init__(self, info, parinte=None):
        self.info = info
        self.parinte = parinte

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

    def afisSolFisier(self, graf, f):
        NM, NC = graf.NM, graf.NC
        l = self.drumRadacina()

        if(l[0].info[2] == 1):
            f.write("(Stanga:<barca>) {} canibali {} misionari  ......  (Dreapta) {} canibali  {} misionari\n\n".format(l[0].info[1], l[0].info[0],
                                                                                                              NC - l[0].info[1], NM - l[0].info[0]))
        else:
            f.write("(Stanga) {} canibali {} misionari  ......  (Dreapta:<barca>) {} canibali  {} misionari\n\n".format(
                l[0].info[1], l[0].info[0],
                NC - l[0].info[1], NM - l[0].info[0]))

        for i in range(1, len(l)):
            difMis, difCan = abs(l[i].info[0] - l[i - 1].info[0]), abs(l[i].info[1] - l[i - 1].info[1])
            if (l[i].info[2] == 1):
                f.write(">>> Barca s-a deplasat de la malul drept la malul stang cu {} canibali si {} misionari.\n".format(difCan, difMis))
                f.write("(Stanga:<barca>) {} canibali {} misionari  ......  (Dreapta) {} canibali  {} misionari\n\n".format(
                    l[i].info[1], l[i].info[0],
                    NC - l[i].info[1], NM - l[i].info[0]))
            else:
                f.write(">>> Barca s-a deplasat de la malul stang la malul drept cu {} canibali si {} misionari.\n".format(
                    difCan, difMis))
                f.write("(Stanga) {} canibali {} misionari  ......  (Dreapta:<barca>) {} canibali  {} misionari\n\n".format(
                    l[i].info[1], l[i].info[0],
                    NC - l[i].info[1], NM - l[i].info[0]))

    def __str__(self):
        return str(self.info)

    def __repr__(self):
        return "({}, ({}))".format(self.info, "->".join([str(x) for x in self.drumRadacina()]))


class Graf:
    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def scop(self, infoNod):
        return infoNod in self.scopuri

    def succesori(self, nod):

        def test(m, c):
            return m == 0 or m >= c

        l = []
        if nod.info[2] == 1: #malul initial = malul cu barca (curent)
            misMalCurent = nod.info[0]
            canMalCurent = nod.info[1]
            misMalOpus = Graf.NM - nod.info[0]
            canMalOpus = Graf.NC - nod.info[1]
        else:
            misMalCurent = Graf.NM - nod.info[0]
            canMalCurent = Graf.NC - nod.info[1]
            misMalOpus = nod.info[0]
            canMalOpus = nod.info[1]

        minMisBarca = 1
        maxMisBarca = min(misMalCurent, Graf.M)
        for mb in range(1, maxMisBarca + 1):
            minCanBarca = 0
            maxCanBarca = min(canMalCurent, Graf.M - mb, mb)

            for cb in range(minCanBarca, maxCanBarca + 1):
                misMalCurentNou = misMalCurent - mb
                canMalCurentNou = canMalCurent - cb
                misMalOpusNou = misMalOpus + mb
                canMalOpusNou = canMalOpus + cb

                if nod.info[2] == 1 and not test(misMalOpusNou, canMalOpusNou):
                    continue
                if nod.info[2] == 0 and not test(misMalCurentNou, canMalCurentNou):
                    continue

                if nod.info[2] == 1:
                    infoNod = (misMalCurentNou, canMalCurentNou, 0)
                else:
                    infoNod = (misMalOpusNou, canMalOpusNou, 1)

                nodNou = NodArbore(infoNod, nod)
                if not nodNou.vizitat():
                    l.append(nodNou)
        return l


def breadth_first(gr, nsol):
    c = [NodArbore(gr.start)]
    while c:
        nodCurent = c.pop(0)
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))
            f = open("output2.txt", "w")
            nodCurent.afisSolFisier(gr, f)
            nsol -= 1
            if nsol == 0:
                return
        lSuccesori = gr.succesori(nodCurent)
        print(lSuccesori)
        c += lSuccesori


f = open("input2.txt", "r")
continut = f.read().strip().split()
# Graf.N = int(continut[0])
# Graf.M = int(continut[1])
Graf.NM = int(continut[0])
Graf.NC = int(continut[1])
Graf.M = int(continut[2])

#start = (Graf.N, Graf.N, 1)
#scopuri = [(0, 0, 0)]

start = (Graf.NM, 0, 1)
scopuri = [(0, Graf.NC, 0)]

gr = Graf(start, scopuri)
breadth_first(gr, 1)

# 3) Creați o metodă, afisSolFisier() în clasa Nod, care afișează într-un fișier dat ca parametru
# (parametrul va fi o variabilă de tip fișier și nu o cale) soluțiile în formatul în care a fost
# afișat drumul de mai jos. Pentru a afișa câți canibali și misionari s-au deplasat cu barca între
# stări, ne putem folosi de informația din nodul părinte (făcând diferența).