# class Solution:
#     def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
#         int mat = input()
#         int k = input()
#         for i in range(len(mat[0])):


mat = [[1,1,0,0,0],
        [1,1,1,1,0],
        [1,0,0,0,0],
        [1,1,0,0,0],
        [1,1,1,1,1]]
k = 3

for i in range(5):
    counter = 0
    for j in range(5):
        if mat[i][j] == 1:
            counter += 1
        else:
            continue
