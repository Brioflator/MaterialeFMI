# 1
# Definiți o clasa Nod, care va reprezenta un nod dintr-un arbore de parcurgere,
# cu câmpurile: informatie, parinte (care e un obiect de tip Nod).
# In constructor, vom defini pentru parinte ca valoare implicită None.
class Nod:
    def __init__(self, inf, par = None):
        self.informatie = inf
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

    def vizitat(self, drumCurent):
        for nod in drumCurent:
            if self.informatie == nod.informatie:
                return False
        return True

    # funcția __repr__  care va returna un string continand informatia nodului,
    # urmata de un spatiu, urmat de o paranteză în care se află tot drumul
    # de la rădăcină până la acel nod). De exemplu "c (a->b->c)"
    # unde c e informația nodului curent și a,b,c sunt informațiile
    # nodurilor din drumul de la rădăcină(a) către el.

    def __repr__(self):
        deAfisat = self.informatie + " ("
        lista = self.drumRadacina()
        for nod in lista:
            deAfisat += nod.informatie
        return deAfisat

    # funcția __str__ care va returna un string doar cu informația nodului
    def __str__(self):
        return self.informatie


class Graf:
    # un constructor prin care se transmit informațiile grafului.
    def __init__(self, noduri, start, stop, listaAdj):
        self.listaNoduri = noduri
        self.nodStart = start
        self.nodStop = stop
        self.listaAdj = listaAdj
    # o metoda scop(informatieNod) care primește o informație de nod
    # și verifică dacă e nod scop
    def scop(self, informatieNod):
        listaInformatie = [nod.informatie for nod in self.noduri]
        if informatieNod in listaInformatie:
            return True
        else:
            return False

    # o metoda (care va fi folosită în algoritmi pentru generarea arborelui
    # de căutare), numită  succesori(nod) care primește un nod al arborelui
    # de parcurgere și parcurge nodurile adiacente din graf, returnand o
    # lista de obiecte de clasa Nod ce reprezinta sucesori direcți ai
    # nodului (care vor fi fii în arborele de căutare), care nu au fost
    # vizitati pe ramura curentă. Toți succesorii vor avea, evident,
    # parintele egal cu nod
    def succesori(self, nod):
        listaSuccesori = self.listaAdj[nod]
        return listaSuccesori

# problema 2
# Implementați tehnica de căutare Breadthfirst, folosind clasele Nod și
# Graf definite mai sus. Se va citi de la tastatură un număr NSOL de soluții.
# se vor afișa primele NSOL soluții.

graph = Graf(['1', '2', '3', '4', '5'], '1', ['5', '2'], {'1':['2', '3'], '2':['1', '3', '5'], '3':['1', '2', '4'], '4':['3', '5'], '5':['2', '4']})
visited = []
queue = []
solPartial = []

def bfs(visited, graph, node):
  visited.append(node)
  queue.append(node)

  while queue:
    m = queue.pop(0)
    solPartial.append(m)

    for neighbour in graph.succesori(m):
      if neighbour not in visited:
        if neighbour in graph.nodStop:
            print(solPartial)
        visited.append(neighbour)
        queue.append(neighbour)

print("BFS Search")
bfs(visited, graph, graph.nodStart)