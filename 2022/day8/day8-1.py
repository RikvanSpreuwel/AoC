text_file = open("input.txt", "r")
lines = text_file.read().split("\n")
matrix = [[int(x) for x in [*line]] for line in lines]

visible = 0
for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        if i < 1 or i > len(matrix)-2:
            visible += 1
        elif j < 1 or j > len(matrix[0])-2:
            visible += 1
        else:
            visible_left = True
            visible_right = True
            visible_up = True
            visible_down = True
            for k in range(0, i):
                if matrix[k][j] >= matrix[i][j]: # a tree directly above is larger than current
                    visible_up = False
                    break
            for k in range(i+1, len(matrix)): 
                if matrix[k][j] >= matrix[i][j]: # a tree directly below is larger than current
                    visible_down = False
                    break
            for k in range(0,j):
                if matrix[i][k] >= matrix[i][j]: # a tree directly left is larger than current
                    visible_left = False
                    break
            for k in range(j+1, len(matrix[0])):
                if matrix[i][k] >= matrix[i][j]: # a tree diretly right is larger than current
                    visible_right = False
                    break
            
            if visible_up == True or visible_down == True or visible_left == True or visible_right == True:
                visible += 1
print(matrix)
print(visible)