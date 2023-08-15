Q = [0, 1, 2, 3]
A = ['a', 'b', 'c']
T = [(0, 1, 'a'), (0, 2, 'b'), (0, 3, 'c'), (0, 3, 'b'), (1, 3, 'a'), (2, 0, 'a'),
     (2, 1, 'a'), (2, 2, 'b'), (2, 3, 'c'), (3, 3, 'a'), (3, 3, 'b')]
S = 0
F = []
cuv = 'caaa'

# Q = [0, 1, 2, 3, 4, 5]
# A = ['a', 'b', 'c']
# T = [(0, 1, 'a'), (0, 2, 'b'), (0, 3, 'c'), (1, 2, 'b'), (1, 4, 'c'),
#      (2, 3, 'a'), (2, 4, 'b'), (3, 4, 'a'), (4, 5, 'a'), (5, 4, 'a')]
# S = 0
# F = [4]
# cuv = 'caaa'

D = [[[] for _ in range(len(Q))] for _ in range(len(Q))]

for i in T:
    D[i[0]][i[1]].append(i[2])

s = S
ch = 0
aux = len(cuv)
poz = 0
State = [s]
l_dex = []
dex = {x: []for x in A}


def recurs(a):
    for i in range(len(D[a])):
        if len(D[a][i]) != 0:
            for j in D[a][i]:
                print(j)
                dex[j].append(i)
    return


recurs(s)
l_dex.append(dex)

for i in dex:
    print(dex[i])
    # for j in dex[i]:
    #     print(j)
    #     recurs(j)
    #     State.append(dex[i])
    print("----------------")

print(dex)
