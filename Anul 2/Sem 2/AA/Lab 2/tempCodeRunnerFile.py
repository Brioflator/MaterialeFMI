    elif ok == len(point_list)-1:
        if (TestOrientare(point_list[ok+1][0], point_list[ok+1][1], origin[0], origin[1], x, y) == 0 or TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == 0):
            return "BOUNDARY"
        if(TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == 1):
            return "OUTSIDE"
    elif ok == 1:
        if (TestOrientare(origin[0], origin[1], point_list[ok][0], point_list[ok][1], x, y) == 0 or TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == 0):
            return "BOUNDARY"
        if(TestOrientare(point_list[ok][0], point_list[ok][1], point_list[ok+1][0], point_list[ok+1][1], x, y) == 1):
            return "OUTSIDE"