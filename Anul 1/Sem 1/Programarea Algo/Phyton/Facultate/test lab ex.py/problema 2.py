def modifica_prefix(x, y, prop):
    i = 0
    k = prop.count(f" {x}")

    m = prop[-len(x) :]
    i = prop[: len(x)]
    if i == x:
        k = k + 1
    if prop[: len(x)] == x:
        prop = prop.strip(x)
        prop = y + prop + m

    return prop.replace(f" {x}", f" {y}"), k


def poz_max(lista):
    l = max(lista)
    mod = []
    for i in range(len(lista)):
        if lista[i] == l:
            mod.append(i)
    return mod


ls = input().split()
a = ls[0]
b = ls[1]

f = open("in.txt", "r")
mat = f.read().split("\n")
mod = [0] * len(mat)
maxi = [0] * len(mat)
f.close()

for i in range(len(mat)):
    mod[i], maxi[i] = modifica_prefix(a, b, mat[i])

for i in poz_max(maxi):
    print(i + 1, end=" ")

f = open("out.txt", "w")
for i in mod:
    f.write(i)
    f.write("\n")
f.close()
