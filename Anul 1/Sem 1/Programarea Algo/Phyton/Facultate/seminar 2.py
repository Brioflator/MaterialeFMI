# # ex 1

# a = int(input())
# b = int(input())

# for i in range(10, a):
#     if i % 5 == 0:
#         print(i, end=" ")

# for i in range(b+1, 100):
#     if i % 5 == 0:
#         print(i, end=" ")

# # ex 2

# n = int(input("n= "))
# a = int(input("a= "))
# b = int(input("b= "))
# if(a > b):
#     print(a, end=" ")

# for i in range(2, n):
#     i = int(input("i= "))
#     if a < b > i:
#         print(b, end=" ")
#     a, b = b, i
# if i > b:
#     print(i)

# # ex 3

# n = int(input("n= "))
# a = int(input())

# k = 1
# ck = 1

# for i in range(n):
#     i = int(input())
#     if i > a:
#         ck = ck+1
#     else:
#         ck = 1
#     if ck > k:
#         k = ck
# print(k)

# # ex 4

# n = int(input("sum= "))
# bancnote = [1, 5, 10, 25]
# bancnote = bancnote[::-1]
# for i in bancnote:
#     cn = n//i
#     if(cn != 0):
#         print(f"{cn} x bancnote de {i}")
#     n = n - cn*i
