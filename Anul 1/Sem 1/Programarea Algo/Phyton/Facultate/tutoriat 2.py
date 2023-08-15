# #ex 1

# s1 = input("s1= ")
# s2 = input("s2= ")
# s1 = s1[::]
# s2 = s2[::-1]
# s3 = ""
# lenght = max(len(s1), len(s2))
# for i in range(lenght):
#     if i < len(s1):
#         s3 = s3+s1[i]
#     if i < len(s2):
#         s3 = s3+s2[i]

# print(s3)


# # ex 2

# s1 = input("s1= ")
# s2 = input("s2= ")

# s1 = s1.lower()
# s2 = s2.lower()

# print(s1.count(s2))


# # ex3

# s1 = input("s1= ")
# s = 0
# p = 1
# c = 0

# for i in s1:
#     if i.isdigit():
#         s = s+int(i)
#         c = c+1
#         p = p*int(i)
# print(s)
# print(p)
# print(s/c)


# # ex 4
# import string

# s1 = input("s1= ")

# aux = string.punctuation

# for i in aux:
#     s1 = s1.replace(i, '*')

# print(s1)

# # ex 5
# sir = "Care"
# s = "lculatoa"
# mij = int(len(sir)//2)
# sir = sir[:mij] + s + sir[mij:]
# print(sir)

# # ex 6

# s1 = input("s1= ")
# s2 = ""
# for i in range(len(s1)):
#     if s1[i].isupper() and s1[i].isalpha():
#         s2 = s2+s1[i].lower()
#     else:
#         s2 = s2+s1[i]

# print(s2)

# # ex 7

# s1 = input("s1= ")
# s2 = ""
# for i in range(0, len(s1), 2):
#     s2 = s2+s1[i]

# print(s2)

# # ex8
# x = 3.1415926
# y = 12.9999
# print(x)
# print("{:.2f}".format(x))
# print(y)
# print("{:.2f}".format(y))

# #  ex 10

# s1 = input("s1= ")
# s2 = input("s2= ")
# s = ""

# if s1[-1] == s2[0]:
#     s = s[0:len(s1)-1]+s2
# elif s1[1] == s2[-2]:
#     s = s1+s2
# print(s)
