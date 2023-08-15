# #ex1

# n = int(input("n= "))
# x = int(input("x= "))

# l = []

# for i in range(n):
#     y = int(input())
#     if y != x:
#         l.append(y)

# print(l)

# # ex 2

# l = [1, 2, [3, [4, 5, [6, 7], 11], 12], 13, 14]
# l1 = [8, 9, 10]
# l[2][1][2].extend(l1)
# print(l)

# # ex 3
# # a
# l = [x for x in range(2, 25) if x % 2 == 0]
# print(l)

# # b
# l1 = [x if x % 2 == 0 else -x for x in range(1, 20)]
# print(l1)

# # c
# l2 = []
# for i in range(6):
#     z = int(input())
#     l2.append(z)

# l2 = [l2[x] for x in range(0, 6, 2)]
# print(l2)

# # d
# l3 = [5, 9, 12, 2, 9, 7, -5, 9]
# l3 = [l3[x] for x in range(8)if x % 2 != l3[x] % 2]
# print(l3)

# # ex4

# n = int(input("n= "))
# l = []
# p = []

# for i in range(n):
#     s = 0
#     y = int(input())
#     l.append(y)
#     while y:
#         s += y % 10
#         y //= 10
#     if(s % 2 == 0):
#         p.append(0)
#     else:
#         p.append(1)

# for i in range(len(l)-1):
#     for j in range(i+1, len(l)):
#         if(p[i] == 0 and p[j] == 0 and l[i] < l[j]
#            or p[i] == 1 and p[j] == 1 and l[i] > l[j]
#            or p[i] == 0 and p[j] == 1):
#             aux = l[i]
#             l[i] = l[j]
#             l[j] = aux
#             aux = p[i]
#             p[i] = p[j]
#             p[j] = aux
# print(l)


# # ex5

# m = int(input())
# n = int(input())
# x = int(input())

# a = []
# a = [[0 for i in range(n)] for j in range(m)]

# for i in range(m):
#     for j in range(n):
#         if i % 2 == 0:
#             a[i][j] = j*5+n*i*5
#         else:
#             a[i][m-j] = j*5+n*i*5


# for linie in a:
#     for x in linie:
#         print(f"{x:4}", end=" ")
#     print()
