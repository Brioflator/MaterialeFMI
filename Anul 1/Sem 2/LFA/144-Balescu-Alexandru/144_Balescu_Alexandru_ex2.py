# Membrii Echipa: Paun Andrei, Balescu Alexandru, Narcis Fanica-Alexandru

# Se va realiza un program care sa valideze o Masina Turing cu un cap si doua benzi,
# conform descrierii formale si a regulilor de computare din exercitiul 1 al lui Paun Andrei.
# In plus, se va crea o functie de simulare a unei Masini Turing bazata pe config file-ul folosit


# CONFIG FILE-ul FOLOSIT ESTE CEL CREAT PENTRU EXERCITIUL 4


# PRECIZARE

# In definitia formala/explicarea computarii masinii turing cu 2 tape-uri corespunzatoare exercitiului 1,
# se precizeaza ca al doilea tape se poate modifica pe parcurs,
# dar pentru a respecta cerinta exercitiului, in cadrul acestui cod al doilea tape nu se modifica

from msilib.schema import AppSearch
import re

from pip import main
file = open("144_Balescu_Alexandru_ex4.txt", 'r')
sigma = set()
tapeal = set()
qA = 0        #
qAprim = 0  # Starile de accept/reject pentru automatul de pe main tape, respectiv second tape
qR = 0
qRprim = 0    #


states1 = []  # Starile automatului de pe main tape
states2 = []  # Starile automatului de pe second tape

transitions1 = []  # Tranzitiile automatului de pe main tape
transitions2 = []  # Tranzitiile automatului de pe second tape


start1 = -1  # Starea de start a automatului de pe main tape
start2 = -1  # Starea de start a automatului de pe second tape
app_s1 = 0
app_s2 = 0

Dir = ["R", "L"]

mainTape = []
secondTape = []

for line in file:
    if "Sigma" in line:
        line = file.readline()
        while "End" not in line and "Sigma" not in line:  # Adaugam litere in alfabetul sigma
            line = line[:-1]
            sigma.add(line)
            line = file.readline()
    if "TapeAl" in line:
        line = file.readline()
        while "End" not in line and "TapeAl" not in line:  # Adaugam litere in alfabetul sigma
            line = line[:-1]
            tapeal.add(line)
            line = file.readline()
    if "Maintape" in line:
        line = file.readline()
        while "End" not in line and "Maintape" not in line:
            line = line[:-1]
            mainTape.append(line)
            line = file.readline()
    if "Secondtape" in line:
        line = file.readline()
        while "End" not in line and "Secondtape" not in line:
            line = line[:-1]
            secondTape.append(line)
            line = file.readline()
    if "States1" in line:  # Adaugam stari in starile automatului de pe main tape.
        line = file.readline()
        while "End" not in line and "States1" not in line:
            line = line[:-1]
            split = list(filter(None, re.split(r'(\s|,)', line.strip())))
            states1.append(split[0])
            for x in split:
                if x != " " and x != ",":
                    if x == "S":
                        start1 = split[0]  # Identificam starea de start
                        app_s1 += 1
                    elif x == "A":
                        qA = split[0]  # Identificam starea de accept
                    elif x == "R":
                        qR = split[0]  # Identificam starea de reject
                    else:
                        pass

            line = file.readline()

    if "States2" in line:
        line = file.readline()
        while "End" not in line and "States2" not in line:
            line = line[:-1]
            split = list(filter(None, re.split(r'(\s|,)', line.strip())))
            states2.append(split[0])
            for x in split:
                if x != " " and x != ",":
                    if x == "S":
                        start2 = split[0]  # Identificam starea de start
                        app_s2 += 1
                    elif x == "A":
                        qAprim = split[0]  # Identificam starea de accept
                    elif x == "R":
                        qRprim = split[0]  # Identificam starea de reject
                    else:
                        pass

            line = file.readline()

    # Adaugam tranzitii in tranzitiile automatului de pe main tape.
    if "Transitions1" in line:
        line = file.readline()
        while "End" not in line and "Transitions1" not in line:
            line = line[:-1]
            split = list(filter(None, re.split(r'(\s|,)', line.strip())))
            tup = []
            for x in split:
                if x != " " and x != ",":
                    tup.append(x)
            transitions1.append(tup)

            line = file.readline()

    # Adaugam tranzitii in tranzitiile automatului de pe second tape.
    if "Transitions2" in line:
        line = file.readline()
        while "End" not in line and "Transitions2" not in line:
            line = line[:-1]
            split = list(filter(None, re.split(r'(\s|,)', line.strip())))
            tup = []
            for x in split:
                if x != " " and x != ",":
                    tup.append(x)
            transitions2.append(tup)

            line = file.readline()

valid = 0

if app_s1 != 1 or app_s2 != 1:
    print("INVALID Double taped TM")
else:
    valid += 1
    ok = 1
    for transition in transitions1:
        # verificam ca starile gasite in tranzitie sa apare in multimea starilor 1, simbolurile sa apara in alfabetul benzii, si directia de miscare a benzii sa fie valida
        if transition[0] not in states1 or transition[2] not in states1 or transition[1] not in tapeal or transition[3] not in tapeal or transition[4] not in Dir:
            ok = 0
            # print(transition)

    for transition in transitions2:
        # verificam ca starile gasite in tranzitie sa apare in multimea starilor 1, simbolurile sa apara in alfabetul benzii, si directia de miscare a benzii sa fie valida
        if transition[0] not in states2 or transition[2] not in states2 or transition[1] not in tapeal or transition[3] not in tapeal or transition[4] not in Dir:
            ok = 0
            # print(transition)
    if ok == 1:
        valid += 1

    # daca cele 2 conditii anterioare au fost indeplinite, TM-ul este valid
    if valid == 2:
        print("VALID Double Taped TM")
    else:
        print("INVALID Double Taped TM")


def validate_word():  # o functie pentru validarea unui cuvant dat
    act1 = states1[states1.index(start1)]
    head1 = 0
    # The start state
    cop = mainTape.copy()
    for i in range(len(cop)):
        mainTape.append("_")
    for i in range(len(cop)):
        secondTape.append("_")
    while True:
        for tr1 in transitions1:
            # Tranzitia potrivita state-ului si simbolului curent
            if tr1[0] == act1 and tr1[1] == mainTape[head1]:
                break
        if tr1[0] != act1 or tr1[1] != mainTape[head1]:
            print("Word rejected")
            return
        if qR in tr1:
            # Daca am gasit un accept/reject state -> functia se opreste
            print("Word rejected")
            return
        elif qA in tr1:
            print("Word accepted")
            return
        if tr1[3] != "*":
            # Modificam simbolul de pe pozitia curenta (exceptand daca acesta este  "*", caz in care nu se modifica)
            mainTape[head1] = tr1[3]
        act1 = states1[states1.index(tr1[2])]  # Modificam state-ul curent
        if tr1[4] == "R":
            head1 += 1  # Deplasam head-ul in functie de directia indicata de tranzitie, asigurandu-ne ca daca am ajuns la limita din stanga, nu o depasim
        elif head1 != 0 and tr1[4] == "L":
            head1 -= 1


if(valid == 2):
    validate_word()
    # afisam cele 2 benzi dupa validarea cuvantului
    print(mainTape, secondTape, sep='\n')
