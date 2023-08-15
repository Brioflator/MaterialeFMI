def sterge_carte(d, x):
    ok = 0
    for i in d:
        for j in d[i]:
            if i != -1:
                if j[0] == x:
                    for q in d[-1]:
                        if q[0] == i:
                            k = q[1] + " " + q[2]
                            ok = 1
                            p = i
                    if ok == 1:
                        del d[i][j][0]
    if ok == 1:
        return k, d
    else:
        return None, d


bibli = {}
f = open("in.txt", "r")
txt = f.read().split("\n")
m = int(txt[0][0])
n = int(txt[0][2])
autori = []
bibli = {}
for i in range(1, m + 1):
    autori.append(txt[i].split())
for i in autori:
    i[0] = int(i[0])

for i in range(m + 1, n + m + 1):
    txt[i] = txt[i].split()

for i in range(m + 1, n + m + 1):
    txt[i][0] = int(txt[i][0])
    txt[i][1] = int(txt[i][1])
    txt[i][2] = int(txt[i][2])
    txt[i][3] = int(txt[i][3])

del txt[-1]
bibli.update({-1: autori})

for j in range(len(autori)):
    ls = []
    for i in range(m + 1, n + m + 1):
        if autori[j][0] == txt[i][0]:
            ls.append(txt[i][1:])
    if autori[j][0] not in bibli:
        bibli.update({autori[j][0]: ls})

bibli1 = {}
bibli1 = bibli

print(sterge_carte(bibli, 131))

f.close()
