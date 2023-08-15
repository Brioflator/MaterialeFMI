# # ex1

# import functools


# def cif(n):
#     s = 0
#     while n:
#         s += 1
#         n //= 10
#     return s


# def comp(a, b):
#     if(cif(a) < cif(b)):
#         return -1
#     if(cif(a) > cif(b)):
#         return 1
#     if(cif(a) == cif(b)):
#         return 0


# n = int(input("n= "))
# l = []
# for i in range(n):
#     l.append(int(input()))

# l.sort(key=functools.cmp_to_key(comp))

# print(l)

# # ex 2


# import functools


# def cifp(n):
#     s = 0
#     while n:
#         if n % 10 % 2 == 0:
#             s += 1
#         n //= 10
#     return s


# def comp(a, b):
#     a = cifp(a)
#     b = cifp(b)
#     if a > b:
#         return -1
#     if a < b:
#         return 1
#     if a == b:
#         return 0


# n = int(input("n= "))

# l = []

# for i in range(n):
#     l.append(int(input()))

# l.sort(key=functools.cmp_to_key(comp))

# print(l)

# # ex 3
# n = int(input("n= "))

# l = []
# for i in range(n):
#     l.append(int(input()))

# l.sort(key=lambda a: a % 10)

# print(l)

# # ex 4

# import functools
# n = int(input('n= '))

# l = []

# for i in range(n):
#     l.append(tuple(input().split()))


# def compb(a, b):
#     if a[0] > b[0]:
#         return 1
#     if a[0] < b[0]:
#         return -1
#     if a[0] == b[0]:
#         if a[1] > b[1]:
#             return 1
#         if a[1] < b[1]:
#             return -1


# def compc(a, b):
#     if a[3] > b[3]:
#         return -1
#     if a[3] < b[3]:
#         return 1
#     if a[3] == b[3]:
#         if a[1] > b[1]:
#             return -1
#         if a[1] < b[1]:
#             return 1


# l1 = sorted(l, key=functools.cmp_to_key(compb))
# l2 = sorted(l, functools.cmp_to_key(compc))

# print(l1)
# print(l2)
