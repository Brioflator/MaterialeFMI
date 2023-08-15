def birthday(s, d, m):
    k = 0
    for i in range(len(s)):
        Sum = sum(s[i:i+m])
        if Sum == d:
            k += 1
    return k


n = 1
s = [4]
d = 4
m = 1

print(birthday(s, d, m))
