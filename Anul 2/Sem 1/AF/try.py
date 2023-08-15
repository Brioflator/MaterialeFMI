visited = [[0 for j in range(1 << 4)] for i in range(4)]
visited[1][1 << 1] = 1
visited[2][1 << 2] = 1
visited[0][1 << 0] = 1
visited[3][1 << 3] = 1
print(visited)
