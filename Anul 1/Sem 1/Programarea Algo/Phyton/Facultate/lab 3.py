# # ex 4

# s = input("s= ")
# voc = "aeiou"
# for i in voc:
#     s = s.replace(i, f"{i}p{i}")
# print(s)

# # ex 1

# def crit(x):
#     return (-len(x))


# s = input("s= ")

# prop_a = " ".join(sorted([x for x in s.split() if len(x) >= 2], reverse=True))
# prop_b = " ".join(sorted([x for x in s.split()], key=crit))
# print(prop_a)
# print(prop_b)

# ex 2

n = int(input("n= "))

cod = int(input("cod= "))
nume = input("nume= ")
prenume = input("prenume= ")
age = int(input("age= "))

l = [(cod, nume, prenume, age)]
for i in range(1, n):
    cod = int(input("cod= "))
    nume = input("nume= ")
    prenume = input("prenume= ")
    age = int(input("age= "))
    l = l.append((cod, nume, prenume, age))
print(l)
