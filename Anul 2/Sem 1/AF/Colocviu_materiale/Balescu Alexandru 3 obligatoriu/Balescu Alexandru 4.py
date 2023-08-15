import collections

# You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi].
# An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.

# Return any valid arrangement of pairs.

# Note: The inputs will be generated such that there exists a valid arrangement of pairs.

# Example 1:

# Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
# Output: [[11,9],[9,4],[4,5],[5,1]]


class Solution:
    # era List cu L mare
    def validArrangement(self, pairs: list[list[int]]) -> list[list[int]]:
        indegree = collections.defaultdict(int)
        outdegree = collections.defaultdict(int)
        edges = collections.defaultdict(
            lambda: collections.deque())  # eficientizare

        for x, y in pairs:
            # retinem in and out degrees ca sa determinam nodul de start
            indegree[x] += 0
            indegree[y] += 1

            outdegree[x] += 1
            outdegree[y] += 0

            edges[x].append(y)

        start, end = None, None
        # daca un nod are doar outdegree si nu indegree atunci il putem considera nod de start
        for x in indegree.keys():
            if indegree[x] + 1 == outdegree[x]:
                start = x
        path = []

        def find(u):
            while len(edges[u]) > 0:
                v = edges[u].popleft()
                find(v)
            path.append(u)

        if start is None:
            find(pairs[0][0])
        else:
            find(start)

        path = path[::-1]
        ans = []

        for x, y in zip(path, path[1:]):
            ans.append([x, y])
        return ans
