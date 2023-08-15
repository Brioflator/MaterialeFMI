def TestOrientare(p1,p2,q1,q2,r1,r2):
    determinant = q1*r2 + p1*q2 + r1*p2 - r1*q2 - p1*r2 - q1*p2
    if determinant > 0:
        return 1 # LEFT
    elif determinant < 0:
        return -1 # RIGHT
    else:
        return 0 # TOUCH
        
if __name__ == "__main__":
    t=int(input())
    result = []
    while(t>0):
        p1,p2,q1,q2,r1,r2=map(int,input().split())
        
        if TestOrientare(p1,p2,q1,q2,r1,r2) >0:
            result.append("LEFT")
        elif TestOrientare(p1,p2,q1,q2,r1,r2) < 0:
            result.append("RIGHT")
        else:
            result.append("TOUCH")
        t=t-1
    for i in result:
        print(i)