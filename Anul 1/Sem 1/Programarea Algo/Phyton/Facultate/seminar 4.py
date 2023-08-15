# # ex 1
# f = open('in.txt', 'r')

# l1 = []
# l2 = []

# l1 = f.read().split('\n')

# for i in range(len(l1)):
#     l2.append([int(i) for i in l1[i].split()])
# l3 = []

# for i in l2:
#     l3.append(set(i))

# inter = l3[0]

# for i in l3:
#     inter = inter.intersection(i)

# print(inter)
# f.close()

# # ex 2

# def fun(fisier):
#     d = {}
#     text = fisier.read()

#     for ch in text:
#         if ch != " " and ch != "\n":
#             if ch not in d:
#                 d.update({ch: 1})
#             else:
#                 d[ch] += 1
#     return d


# f = open('in.txt', 'r')

# # fun(f)

# print(fun(f))

# f.close()
