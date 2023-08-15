# # ex 1

# n = int(input("n= "))
# keys = [x for x in input().split()]
# values = [x for x in input().split()]

# dict1 = {}

# for i in range(n):
#     dict1.update({keys[i]: values[i]})

# print(dict1)


# # ex2
# dict1 = {"nume": "Ana", "varsta": 30,
#          "salariu": 10000, "oras": "Cluj", "ore": 45}
# lista = ["nume", "salariu", "ore"]

# dict2 = {x: dict1[x] for x in lista}

# print(dict2)

# ex 3
l = []
n = int(input("n= "))
for i in range(n):
    p = input().split(" ", 1)
    p = int(p[0]), p[1], i+1
    l.append(p)

print(l)

pct = [p[0] for p in l]

top = max(pct)

nota = []

f = [0 for i in range(101)]

for j in pct:
    f[int(j)] = 1
for i in range(100):
    if f[i] == 1:
        nota.append(i)

print(nota)

catalog = {}

for i in nota:
    catalog[i] = [p[1:] for p in l if p[0] == i]

print(catalog)

print(catalog[top][0])
