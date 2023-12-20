def main():
    text_file = open("input.txt", "r")
    matrix = [[int(y) for y in list(x)] for x in text_file.read().split('\n')]
    matrixZeroNine = [[0 if x!= 9 else x for x in matrixZeroNineRow] for matrixZeroNineRow in matrix]
    low_point_indices = []
    
    
    print(matrix)
    print(matrixZeroNine)

    for i in range(0, 100):
        for j in range(0, 100):
            if i == 0:
                if j == 0:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i+1][j]:
                        low_point_indices.append([i,j])
                elif j == 99:
                    if matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i+1][j]:
                        low_point_indices.append([i,j])
                else:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i+1][j]:
                        low_point_indices.append([i,j])
            elif i == 99:
                if j == 0:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i-1][j]:
                        low_point_indices.append([i,j])
                elif j == 99:
                    if matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i-1][j]:
                        low_point_indices.append([i,j])
                else:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i-1][j]:
                        low_point_indices.append([i,j])
            else:
                if j == 0:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i+1][j] and matrix[i][j] < matrix[i-1][j]:
                        low_point_indices.append([i,j])
                elif j == 99:
                    if matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i+1][j] and matrix[i][j] < matrix[i-1][j]:
                        low_point_indices.append([i,j])
                else:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i-1][j] and matrix[i][j] < matrix[i+1][j]:
                        low_point_indices.append([i,j])
    
    # for lowPoint in low_point_indices:
    #     for lowPoint2 in low_point_indices:
    #         if lowPoint != lowPoint2:
    #             directPath1 = True
    #             directPath2 = True
    #             directPath3 = True
    #             directPath4 = True
    #             for i in range(lowPoint2[0]+1, lowPoint[i]):
    #                 if matrixZeroNine[i][lowPoint2[1]] == 9:
    #                     directPath1 == False
    #             for i in range(lowPoint2[0]+1, lowPoint[i]):
    #                 if matrixZeroNine[i][lowPoint2[1]] == 9:
    #                     directPath2 == False
    #             for i in range(lowPoint2[0]+1, lowPoint[i]):
    #                 if matrixZeroNine[i][lowPoint2[1]] == 9:
    #                     directPath3 == False
    #             for i in range(lowPoint2[0]+1, lowPoint[i]):
    #                 if matrixZeroNine[i][lowPoint2[1]] == 9:
    #                     directPath4 == False
    
    basinsSizes = []
    for lowPoint in low_point_indices:
        size = 1
        i = lowPoint[0]
        j = lowPoint[1]
        for k in range(i, 100):
            for l in range(j, 100):
                if k == i and l == j: continue
                elif matrixZeroNine[k][l] == 0:
                    size +=1
                else:
                    break 
            for l in reversed(range(0, j)):
                if k == i and l == j: continue
                elif matrixZeroNine[k][l] == 0:
                    size +=1
                else:
                    break 
        for k in reversed(range(0, i)):
            for l in range(j, 100):
                if k == i and l == j: continue
                elif matrixZeroNine[k][l] == 0:
                    size +=1
                else:
                    break 
            for l in reversed(range(0, j)):
                if k == i and l == j: continue
                elif matrixZeroNine[k][l] == 0:
                    size +=1
                else:
                    break 
        basinsSizes.append(size)

    largest = 0
    secondLargest = 0
    thirdLargest = 0
    for basin in set(basinsSizes):
        if basin > largest:
            thirdLargest = secondLargest
            secondLargest = largest
            largest = basin
        elif basin > secondLargest:
            thirdLargest = secondLargest
            secondLargest = basin
        elif basin > thirdLargest:
            thirdLargest = basin
    print(basinsSizes)
    print(largest)
    print(secondLargest)
    print(thirdLargest)
    print(largest* secondLargest* thirdLargest)

    basinsSizes.sort()
    print(basinsSizes)

    total = 0
    for size in set(basinsSizes):
        total += size
    print(total)

    # print(matrix)
    # print(len(matrix))
    # print(len(matrix[0]))



if __name__ == "__main__":
    main()



    




    # for i in range(0, 100):
    #     for j in range(0, 100):
    #         if i == 0:
    #             if j == 0:
    #                 if matrix[i][j] <= matrix[i][j+1] and matrix[i][j] <= matrix[i+1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #             elif j == 99:
    #                 if matrix[i][j] <= matrix[i][j-1] and matrix[i][j] <= matrix[i+1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #             else:
    #                 if matrix[i][j] <= matrix[i][j+1] and matrix[i][j] <= matrix[i][j-1] and matrix[i][j] <= matrix[i+1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #         elif i == 99:
    #             if j == 0:
    #                 if matrix[i][j] <= matrix[i][j+1] and matrix[i][j] <= matrix[i-1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #             elif j == 99:
    #                 if matrix[i][j] <= matrix[i][j-1] and matrix[i][j] <= matrix[i-1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #             else:
    #                 if matrix[i][j] <= matrix[i][j+1] and matrix[i][j] <= matrix[i][j-1] and matrix[i][j] <= matrix[i-1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #         else:
    #             if j == 0:
    #                 if matrix[i][j] <= matrix[i][j+1] and matrix[i][j] <= matrix[i+1][j] and matrix[i][j] <= matrix[i-1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #             elif j == 99:
    #                 if matrix[i][j] <= matrix[i][j-1] and matrix[i][j] <= matrix[i+1][j] and matrix[i][j] <= matrix[i-1][j]:
    #                     low_points.append(matrix[i][j]+1)
    #             else:
    #                 if matrix[i][j] <= matrix[i][j+1] and matrix[i][j] <= matrix[i][j-1] and matrix[i][j] <= matrix[i-1][j] and matrix[i][j] <= matrix[i+1][j]:
    #                     low_points.append(matrix[i][j]+1)