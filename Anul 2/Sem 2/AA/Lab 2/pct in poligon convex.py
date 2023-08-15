# def TestOrientare(p1, p2, q1, q2, r1, r2):
#     determinant = q1*r2 + p1*q2 + r1*p2 - r1*q2 - p1*r2 - q1*p2
#     if determinant > 0:
#         return 1  # LEFT
#     elif determinant < 0:
#         return -1  # RIGHT
#     else:
#         return 0  # TOUCH


# def is_inside(x, y, point_list):
#     origin = (point_list[0][0], point_list[0][1])
#     ok = 0
#     for i in range(len(point_list)-1):
#         if (TestOrientare(origin[0], origin[1], point_list[i][0], point_list[i][1], x, y) == 1 or TestOrientare(origin[0], origin[1], point_list[i][0], point_list[i][1], x, y) == 0) and (TestOrientare(origin[0], origin[1], point_list[i+1][0], point_list[i+1][1], x, y) == -1 or TestOrientare(origin[0], origin[1], point_list[i+1][0], point_list[i+1][1], x, y) == 0):
#             ok = i
#             break
#     if ok == 0:
#         return "OUTSIDE"
#     else:
#         if(TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == 0):
#             return "BOUNDARY"
#         if(TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == 1):
#             return "INSIDE"
#         if(TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == -1):
#             return "OUTSIDE"


# if __name__ == "__main__":
#     # datele poligonului
#     number_of_points = int(input())
#     point_list = []
#     while number_of_points > 0:
#         x, y = map(int, input().split())
#         point_list.append((x, y))
#         number_of_points -= 1

#     # datele punctelor de test
#     number_of_test_points = int(input())
#     test_point_list = []
#     while number_of_test_points > 0:
#         x, y = map(int, input().split())
#         test_point_list.append((x, y))
#         number_of_test_points -= 1

#     for point in test_point_list:
#         print(is_inside(point[0], point[1], point_list))

def orient2d(p, q, r):
    return (q[0] - p[0]) * (r[1] - p[1]) - (r[0] - p[0]) * (q[1] - p[1])


def inside_polygon(poly, point):
    n = len(poly)
    wn = 0
    for i in range(n):
        j = (i + 1) % n
        if poly[i][1] <= point[1]:
            if poly[j][1] > point[1] and orient2d(poly[i], poly[j], point) > 0:
                wn += 1
        else:
            if poly[j][1] <= point[1] and orient2d(poly[i], poly[j], point) < 0:
                wn -= 1
    if wn == 0:
        return "BOUNDARY"
    elif wn % 2 == 1:
        return "INSIDE"
    else:
        return "OUTSIDE"


n = int(input())
poly = [tuple(map(int, input().split())) for _ in range(n)]
m = int(input())
for _ in range(m):
    point = tuple(map(int, input().split()))
    print(inside_polygon(poly, point))
