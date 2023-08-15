# # 1. Se dau două liste l1 si l2 de lungime n. Să se înlocuiască elementele de pe poziții pare din l1 cu cele de pe pozitia corespunzătoare din l2 folosind feliere (slice)

# n = int(input("n= "))

# l1 = [int(x) for x in input().split()]
# l2 = [int(x) for x in input().split()]

# l1[::2] = l2[::2]

# print(l1)

# # 2. Se dă o listă de numere naturale. Să se  steargă din listă subsecventa delimitată de primele două zerouri din listă (inclusiv zerourile)

# n = int(input("n= "))

# l1 = [int(x) for x in input().split()]

# p = l1.index(0)
# q = l1[(p+1):].index(0)

# q += (p+1)

# del(l1[p:(q+1)])

# print(l1)

# # 4. Se dă o listă de numere naturale si un număr natural k. Să se elimine din listă subsecventa a de lungime k de sumă minimă

# def suma(lista):
#     s = 0
#     for i in lista:
#         s = s+i
#     return s


# k = int(input("k= "))

# l1 = [int(x) for x in input().split()]


# m = 99999

# for i in range(len(l1)-k):
#     if m >= suma(l1[i:(i+k)]):
#         m = suma(l1[i:(i+k)])
#         p = i

# del(l1[p:(p+k)])

# print(l1)

# # Se dă o listă de numere reale (toate elementele sale se vor da pe o linie separate prin spa iu). Să se insereze câte un 0 după fiecare element negativ

# l1 = [int(x) for x in input().split()]

# i = 0
# while i < len(l1)-1:
#     i = i+1
#     l1.insert(i, 0)
#     i = i+1

# print(l1)

# # Se cite te o propozi ie cu cuvintele separate prin spatii (unul sau mai multe). Să se creeze oșțlistă cu cuvintele care încep cu o vocală (folosind  si comprehensiune)

# l1 = [x for x in input().split() if x[0] == 'a' or x[0] == 'e' or x[0]
#       == 'i' or x[0] == 'o' or x[0] == 'u']

# print(l1)

# # Se cite te o propozi ie cu cuvintele separate prin spa iu. Să se creeze o listă cu cuvintele șțțcare con in minim 3 vocale (folosind  i comprehensiune).

# def voc(x):
#     k = 0
#     for i in range(len(x)):
#         if x[i] == 'a' or x[i] == 'e' or x[i] == 'i' or x[i] == 'o' or x[i] == 'u':
#             k = k+1
#     return k


# l1 = [x for x in input().split() if voc(x) >= 3]

# print(l1)

# # Se dă o propozi ie care con ine cuvinte separate prin separatorii uzuali ( ,.;:). O parte din cuvinte reprezintă numere naturale.
# # Să se determine media aritmetică a cuvintelor din  ir careșsunt numere

# import re
# string = input()
# l1 = [i for i in filter(None, re.split('[ ;,.:]', string))]
# s = 0
# n = 0
# for i in l1:
#     if i[0] == '0' or i[0] == '1' or i[0] == '2' or i[0] == '3' or i[0] == '4' or i[0] == '5' or i[0] == '6' or i[0] == '7' or i[0] == '8' or i[0] == '9':
#         s = s+int(i)
#         n = n+1
# print(round(s/n, 2))

# # Se citesc doua cuvinte formate doar din litere mici. Să se verifice dacă sunt anagrame

# str1 = input()
# str2 = input()
# l1 = []
# l2 = []

# for i in str1:
#     l1.append(i)

# for i in str2:
#     l2.append(i)

# l1 = sorted(l1)
# l2 = sorted(l2)

# if(l1 == l2):
#     print("anagrama")
# else:
#     print("nu anagrama")

# # Se citesc n, m  i o matrice cu n linii si m coloane (numerele sunt date câte unul pe linie).
# # Să se ordoneze crescător elementele de pe prima coloana prin interschimbari de linii.

# matrice = []
# ls = [i for i in input().split()]
# n = int(ls[0])
# m = int(ls[1])

# for i in range(n):
#     ls = [int(i) for i in input().split()]
#     matrice.append(ls)

# for i in range(len(matrice)):
#     for j in range(i, len(matrice)):
#         if (matrice[i][0] > matrice[j][0]):
#             matrice[i], matrice[j] = matrice[j], matrice[i]

# for i in matrice:
#     for j in i:
#         print(f"{j:4}", end="")
#     print()
