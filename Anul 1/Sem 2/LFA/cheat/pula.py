# f = open(str(sys.argv[1] + '.in'), 'r')

f = open("cfg_config_file.in", 'r')
file_lines = f.readlines()

file_lines = [x.split('\n') for x in file_lines]

V = []
E = []
R = {}

i = 0
while i < len(file_lines):
    if 'Variables' in file_lines[i][0]:
        i += 1
        while 'End' not in file_lines[i]:
            V.append(file_lines[i][0])
            i += 1
    if 'Start state' in file_lines[i][0]:
        i += 1
        S = file_lines[i][0][0]
    if 'Terminals' in file_lines[i][0]:
        i += 1
        while 'End' not in file_lines[i]:
            E.append(file_lines[i][0])
            i += 1
    if 'Rules' in file_lines[i][0]:
        i += 1
        while 'End' not in file_lines[i]:
            auxList = file_lines[i][0].split(" -> ")
            state = auxList[0]
            ruleList = auxList[1].split("|")
            if state not in R.keys():
                R[state] = ruleList
            else:
                for rule in ruleList:
                    R[state].append(rule)
            i += 1
    i += 1

print(R)


def UselessProduction():
    # eliminare ciclare infinita
    for i in V:
        k = 0
        for j in R[i]:
            if i in j:
                k += 1
        if k == len(R[i]):
            del(R[i])

    # eliminare key nefolosit

    for i in V:
        l = 0
        for j in R:
            for k in R[j]:
                if(i in k):
                    l = 1
        if l == 0:
            if(i != S):
                del(R[i])


l = []
freq = {x: 0 for x in V}


def Last_rec():
    for i in R:
        for j in R[i]:
            if j in V:
                l.append((i, j, len(R[i])))
    for i in l:
        freq[i[0]] += 1
        freq[i[1]] += 1
    for i in freq:
        if(freq[i] == 1):
            sem = 1
            for j in R[i]:

                if j in V:
                    sem = 0

            if(sem == 1):
                inpt = i
                return inpt
    return 0


def replacey(inp, R, ip):

    for i in l:
        if(i[1] == inp):
            for j in R[i[0]]:
                if(j == inp):
                    R[i[0]].extend(ip)
                    for u in R[i[0]]:
                        if(j == u):
                            R[i[0]].remove(u)
                    return replacey(i[0], R, ip)


def UnitProduction():
    lec = Last_rec()
    if lec != 0:
        ip = R[lec]
        replacey(lec, R, ip)
        UselessProduction()


UnitProduction()

print(l)
print(freq)
print(R)
