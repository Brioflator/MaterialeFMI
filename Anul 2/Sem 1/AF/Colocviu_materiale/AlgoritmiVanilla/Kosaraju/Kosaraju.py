# Python implementation of Kosaraju's algorithm to print all SCCs

from collections import deque
from collections import defaultdict

# This class represents a directed graph using adjacency list representation


class Graph:

    def __init__(self, vertices):
        self.V = vertices  # No. of vertices
        self.graph = defaultdict(list)  # default dictionary to store graph

    # function to add an edge to graph
    def addEdge(self, u, v):
        self.graph[u].append(v)

    # A function used by DFS
    def DFSUtil(self, v, visited):
        # Mark the current node as visited and print it
        visited[v] = True
        print(v)
        # Recur for all the vertices adjacent to this vertex
        for i in self.graph[v]:
            if visited[i] == False:
                self.DFSUtil(i, visited)

    def fillOrder(self, v, visited, stack):
        # Mark the current node as visited
        visited[v] = True
        # Recur for all the vertices adjacent to this vertex
        for i in self.graph[v]:
            if visited[i] == False:
                self.fillOrder(i, visited, stack)
        stack = stack.append(v)

    # Function that returns reverse (or transpose) of this graph

    def getTranspose(self):
        g = Graph(self.V)

        # Recur for all the vertices adjacent to this vertex
        for i in self.graph:
            for j in self.graph[i]:
                g.addEdge(j, i)
        return g

    # The main function that finds and prints all strongly
    # connected components

    def printSCCs(self):

        stack = []
        # Mark all the vertices as not visited (For first DFS)
        visited = [False]*(self.V)
        # Fill vertices in stack according to their finishing
        # times
        for i in range(self.V):
            if visited[i] == False:
                self.fillOrder(i, visited, stack)

        # Create a reversed graph
        gr = self.getTranspose()

        # Mark all the vertices as not visited (For second DFS)
        visited = [False]*(self.V)

        # Now process all vertices in order defined by Stack
        while stack:
            i = stack.pop()
            if visited[i] == False:
                gr.DFSUtil(i, visited)
                print("")


# Create a graph given in the above diagram
g = Graph(5)
g.addEdge(1, 0)
g.addEdge(0, 2)
g.addEdge(2, 1)
g.addEdge(0, 3)
g.addEdge(3, 4)


print("Following are strongly connected components " +
      "in given graph")
g.printSCCs()
# This code is contributed by Neelam Yadav


##############################################################################################################

# Python3 program to check if a given directed graph
# is strongly connected or not with BFS use

# A recursive function to print DFS starting from v

def BFSUtil(adj, v, visited):

    # Create a queue for BFS
    queue = deque()

    # Mark the current node as visited
    # and enqueue it
    visited[v] = True
    queue.append(v)

    # 'i' will be used to get all adjacent
    # vertices of a vertex
    while (len(queue) > 0):

        # Dequeue a vertex from queue
        v = queue.popleft()
        # print(v)
        # queue.pop_front()

        # Get all adjacent vertices of the
        # dequeued vertex s. If a adjacent
        # has not been visited, then mark it
        # visited and enqueue it
        for i in adj[v]:
            if (visited[i] == False):
                visited[i] = True
                queue.append(i)

    return visited

# Function that returns reverse
# (or transpose) of this graph


def getTranspose(adj, V):

    g = [[] for i in range(V)]

    for v in range(V):

        # Recur for all the vertices adjacent to
        # this vertex
        # list<int>::iterator i
        for i in adj[v]:
            g[i].append(v)

    return g


def addEdge(adj, v, w):

    # Add w to v’s list.
    adj[v].append(w)
    return adj

# The main function that returns True if graph
# is strongly connected


def isSC(adj, V):

    # Step 1: Mark all the vertices as not
    # visited (For first BFS)
    visited = [False]*V

    # Step 2: Do BFS traversal starting
    # from first vertex.
    visited = BFSUtil(adj, 0, visited)
    # print(visited)

    # If BFS traversal doesn’t visit all
    # vertices, then return false.
    for i in range(V):
        if (visited[i] == False):
            return False

    # Step 3: Create a reversed graph
    adj = getTranspose(adj, V)

    # Step 4: Mark all the vertices as not
    # visited (For second BFS)
    for i in range(V):
        visited[i] = False

    # Step 5: Do BFS for reversed graph
    # starting from first vertex.
    # Starting Vertex must be same starting
    # point of first DFS
    visited = BFSUtil(adj, 0, visited)

    # If all vertices are not visited in
    # second DFS, then return false
    for i in range(V):
        if (visited[i] == False):
            return False

    return True


# Driver code
if __name__ == '__main__':

    # Create graphs given in the above diagrams
    g1 = [[] for i in range(5)]
    g1 = addEdge(g1, 0, 1)
    g1 = addEdge(g1, 1, 2)
    g1 = addEdge(g1, 2, 3)
    g1 = addEdge(g1, 3, 0)
    g1 = addEdge(g1, 2, 4)
    g1 = addEdge(g1, 4, 2)
    # print(g1)

    print("Yes" if isSC(g1, 5) else "No")

    g2 = [[] for i in range(4)]

    g2 = addEdge(g2, 0, 1)
    g2 = addEdge(g2, 1, 2)
    g2 = addEdge(g2, 2, 3)

    print("Yes" if isSC(g2, 4) else "No")

# This code is contributed by mohit kumar 29
