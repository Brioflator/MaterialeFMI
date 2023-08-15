def TestOrientare(p1,p2,q1,q2,r1,r2):
    determinant = q1*r2 + p1*q2 + r1*p2 - r1*q2 - p1*r2 - q1*p2
    if determinant > 0:
        return 1 # LEFT
    elif determinant < 0:
        return -1 # RIGHT
    else:
        return 0 # TOUCH
    
if __name__ == "__main__":
    nr_pct=int(input())
    puncte = []
    while nr_pct>0:
        x,y=map(int,input().split())
        puncte.append((x,y))
        nr_pct-=1

L=R=T=0
        
for i in range(1,len(puncte)-1):
    if TestOrientare(puncte[i-1][0],puncte[i-1][1],puncte[i][0],puncte[i][1],puncte[i+1][0],puncte[i+1][1]) > 0:
        L+=1
    elif TestOrientare(puncte[i-1][0],puncte[i-1][1],puncte[i][0],puncte[i][1],puncte[i+1][0],puncte[i+1][1]) < 0:
        R+=1
    else:
        T+=1
        
if TestOrientare(puncte[len(puncte)-2][0],puncte[len(puncte)-2][1],puncte[len(puncte)-1][0],puncte[len(puncte)-1][1],puncte[0][0],puncte[0][1]) > 0:
        L+=1
elif TestOrientare(puncte[len(puncte)-2][0],puncte[len(puncte)-2][1],puncte[len(puncte)-1][0],puncte[len(puncte)-1][1],puncte[0][0],puncte[0][1]) < 0:
        R+=1
else:
        T+=1

print ( L,R,T )