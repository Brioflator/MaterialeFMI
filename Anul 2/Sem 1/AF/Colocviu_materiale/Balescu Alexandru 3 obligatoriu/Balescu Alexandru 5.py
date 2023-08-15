import collections


# You have an undirected, connected graph of n nodes labeled from 0 to n - 1.
# You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.

# Return the length of the shortest path that visits every node.
# You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.


class Solution:
    def shortestPathLength(self, graph: list[list[int]]) -> int:
        N = len(graph)
        que = collections.deque()
        step = 0
        goal = (1 << N) - 1  # bitmask pentru un ciclu hamiltonian
        visited = [[0 for j in range(1 << N)] for i in range(N)]
        for i in range(N):
            que.append((i, 1 << i))
        while que:
            s = len(que)
            for i in range(s):
                node, state = que.popleft()
                if state == goal:
                    return step
                if visited[node][state] == 1:
                    continue
                visited[node][state] = 1
                for nextNode in graph[node]:
                    que.append((nextNode, state | (1 << nextNode)))
            step += 1
        return step

# ne folosim de bitmask ca sa nu depasim limita de memorie. Stim ca maximul pe care l poate avea un graf e 12
# putem sa ne folosim de valoarea unui bit ca sa marcam daca nodul corespunzator a fost vizitat
# Every time take the first element in the queue, if the path( mask) matches the goal( visited all nodes), then return the number of steps ( dist)
