
def citire(fisier):
    mat = []
    l2 = []
    text = fisier.read().split('\n')
    for i in range(len(text)):
        mat.append([int(i) for i in text[i].split()])

    ok = len(mat[i])
    for i in mat:
        if ok != len(i):
            return None

    return mat


def conditie(a):
    q = a % 10
    while a >= 10:
        a = a//10
    if q == a:
        return 1
    else:
        return 0


def multimi(matrice, *indici):
    l1 = [0]*len(matrice)
    l2 = [0]*len(matrice)
    for i in range(len(matrice)):
        if i in indici:
            l3 = []
            l4 = []
            m1 = set()
            m2 = set()
            for j in range(len(matrice[i])):
                if matrice[i][j] < 0:
                    m1.add(matrice[i][j])
                if conditie(matrice[i][j]) and matrice[i][j] >= 0:
                    m2.add(matrice[i][j])
            l1[i] = m1
            l2[i] = m2
    f1 = set()
    f2 = set()

    for i in l2:
        if type(i) != int:
            if f2 == set():
                f2.update(i)
            f2.update(f2.union(i))

    for i in l1:
        if type(i) == set:
            if f1 == set():
                f1.update(i)
            f1 = f1.intersection(i)

    return f1, f2


f = open('in.txt', 'r')
mat = citire(f)

l = len(mat)

n, p = multimi(mat, l-3, l-2, l-1)
print(p)

n, p = multimi(mat, 0, l-1)
print(len(n))

f.close()
