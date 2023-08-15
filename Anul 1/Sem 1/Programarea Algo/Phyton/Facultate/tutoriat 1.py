# # 1.Să se determine dacă 3 numere reale a, b, c (citite de la tastatură) pot fi lungimile laturilor unuitriunghi.

# a = int(input("a= "))
# b = int(input("b= "))
# c = int(input("c= "))

# if a < b:
#     a, b = b, a

# if a < c:
#     a, c = c, a

# if b < c:
#     b, c = c, b

# if c+b > a:
#     print("Este triunghi")
# else:
#     print("Nu e triunghi")

# # 2. Se citeste un număr de la tastatură. Să se afiseze dacă este sau nu cub perfect.

# n = int(input())

# for i in range(int(n**0.5)):
#     if i**3 == n:
#         print("Este cub")
#         break
# else:
#     if n == 0 or n == 1 or n == 8:
#         print("Este cub")
#     else:
#         print("Nu este cub")

# # 4. Să se determine primului număr prim din intervalul [a,b], cu a si b citite de la tastatură.(folosind clauza else).

# a = int(input())
# b = int(input())

# for i in range(a, b+1):
#     for j in range(2, i):
#         if i % j == 0:
#             break
#     else:
#         print(i)
#         break
# else:
#     print("Nu exista")


# # 6. Se citeste un sir format din n numere întregi ( n > 2). Să se afiseze cele mai mici două valori distincte din sir sau mesajul  „Nu se poate”, dacă acestea nu există.

# n = int(input("lungime sir= "))
# cn = n
# l = []
# while cn > 0:
#     l.append(int(input()))
#     cn = cn-1
# min1 = 1e10
# min2 = 1e10
# for i in l:
#     if i < min1:
#         min1 = i

# for i in l:
#     if i < min2 and min1 != i:
#         min2 = i
# if min2 != 1e10:
#     print(min1)
#     print(min2)
# else:
#     print("Nu exista")
