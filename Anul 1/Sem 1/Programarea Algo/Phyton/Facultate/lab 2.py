# # ex 1
# s = input()
# k = int(input())
# p = ""
# for i in range(len(s)):
#     if i != k:
#         p = p+s[i]
# print(p)


# # ex 3
# s = input()
# i = 1
# j = len(s)-1

# while i+1 < j:
#     print(s[i:j])
#     i = i+1
#     j = j-1

# # ex 7

# s = input()
# q = ""
# p = s.split(" ")
# for x in p:
#     q = q + x.capitalize() + " "

# print(q)

# # ex 8
# s = input()
# r = ""
# p = ""
# for x in range(len(s)):
#     if s[x].isalpha():
#         if p is not None:
#             r = r + s[x] * int(p)
#             p = ""
#     else:
#         p += s[x]
# print(r)
