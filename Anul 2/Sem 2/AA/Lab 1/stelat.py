def TestOrientare(p1, p2, q1, q2, r1, r2):
    determinant = q1*r2 + p1*q2 + r1*p2 - r1*q2 - p1*r2 - q1*p2
    if determinant > 0:
        return 1  # LEFT
    elif determinant < 0:
        return -1  # RIGHT
    else:
        return 0  # TOUCH


if __name__ == "__main__":
    # GRAHAM SCAN ALGORITHM FOR CONVEX HULL - UNSUCCESSFUL
    # nr_pct_initial = int(input())
    # nr_pct_final = nr_pct_initial
    # puncte_initiale = []
    # puncte_finale = []
    # while nr_pct_initial > 0:
    #     x, y = map(int, input().split())
    #     puncte_initiale.append((x, y))
    #     nr_pct_initial -= 1

    # if nr_pct_final < 2:
    #     print('Convex hull is empty')

    # else:
    #     stack = []
    #     stack_size = 0
    #     stack.append(puncte_initiale[0])
    #     stack.append(puncte_initiale[1])
    #     stack.append(puncte_initiale[2])
    #     stack_size = 3
    #     for i in range(3, nr_pct_final):
    #         while(len(stack) > 1) and (TestOrientare(stack[-2][0], stack[-2][1], stack[-1][0], stack[-1][1], puncte_initiale[i][0], puncte_initiale[i][1]) <= 0):
    #             stack.pop()
    #             stack_size -= 1
    #         stack.append((puncte_initiale[i][0], puncte_initiale[i][1]))
    #         stack_size += 1

    #     print("\n")
    #     print(stack_size)
    #     for point in stack:
    #         print(point[0], point[1])

    nr_pct_initial = int(input())
    puncte_initiale = []

    while nr_pct_initial > 0:
        x, y = map(int, input().split())
        puncte_initiale.append((x, y))
        nr_pct_initial -= 1

    left_most = min(puncte_initiale, key=lambda x: x[0])
    index = puncte_initiale.index(left_most)

    l = index
    puncte_finale = []
    puncte_finale.append(left_most)
    while(True):
        q = (l+1) % len(puncte_initiale)
        for i in range(len(puncte_initiale)):
            if i == l:
                continue
            orientation = TestOrientare(puncte_initiale[l][0], puncte_initiale[l][1], puncte_initiale[i]
                                        [0], puncte_initiale[i][1], puncte_initiale[q][0], puncte_initiale[q][1])
            if orientation > 0 or (orientation == 0 and ((puncte_initiale[i][0] - puncte_initiale[l][0]) ** 2 + (puncte_initiale[i][1] - puncte_initiale[l][1]) ** 2) ** 0.5 > ((puncte_initiale[q][0] - puncte_initiale[l][0]) ** 2 + (puncte_initiale[q][1] - puncte_initiale[l][1]) ** 2) ** 0.5):
                q = i
        l = q
        if l == index:
            break
        puncte_finale.append(puncte_initiale[q])

    print(len(puncte_finale))
    for point in puncte_finale:
        print(point[0], point[1])
