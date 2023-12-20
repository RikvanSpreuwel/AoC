import numpy as np

text_file = open("input.txt", "r")
lines = text_file.read().split("\n")
matrix = [[int(x) for x in [*line]] for line in lines]
matrix_view_scores = np.zeros((len(matrix),len(matrix)))

visible = 0
for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        visible_left = 0
        visible_right = 0
        visible_up = 0
        visible_down = 0
        
        for k in reversed(range(0,i)):
            visible_up += 1
            if matrix[k][j] >= matrix[i][j]: # a tree directly above is larger than current
                break
        for k in range(i+1, len(matrix)): 
            visible_down += 1
            if matrix[k][j] >= matrix[i][j]: # a tree directly below is larger than current
                break
        for k in reversed(range(0,j)):
            visible_left += 1
            if matrix[i][k] >= matrix[i][j]: # a tree directly left is larger than current
                break
        for k in range(j+1, len(matrix[0])):
            visible_right += 1
            if matrix[i][k] >= matrix[i][j]: # a tree diretly right is larger than current
                break
        
        matrix_view_scores[i][j] = visible_left * visible_right * visible_up * visible_down
        
print(matrix_view_scores.max())