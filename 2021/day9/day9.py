def main():
    text_file = open("input.txt", "r")
    matrix = [[int(y) for y in list(x)] for x in text_file.read().split('\n')]

    low_points = []
    
    

    for i in range(0, 100):
        for j in range(0, 100):
            if i == 0:
                if j == 0:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i+1][j]:
                        low_points.append(matrix[i][j]+1)
                elif j == 99:
                    if matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i+1][j]:
                        low_points.append(matrix[i][j]+1)
                else:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i+1][j]:
                        low_points.append(matrix[i][j]+1)
            elif i == 99:
                if j == 0:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i-1][j]:
                        low_points.append(matrix[i][j]+1)
                elif j == 99:
                    if matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i-1][j]:
                        low_points.append(matrix[i][j]+1)
                else:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i-1][j]:
                        low_points.append(matrix[i][j]+1)
            else:
                if j == 0:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i+1][j] and matrix[i][j] < matrix[i-1][j]:
                        low_points.append(matrix[i][j]+1)
                elif j == 99:
                    if matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i+1][j] and matrix[i][j] < matrix[i-1][j]:
                        low_points.append(matrix[i][j]+1)
                else:
                    if matrix[i][j] < matrix[i][j+1] and matrix[i][j] < matrix[i][j-1] and matrix[i][j] < matrix[i-1][j] and matrix[i][j] < matrix[i+1][j]:
                        low_points.append(matrix[i][j]+1)
    

    count = 0
    for number in low_points:
        count += int(number)
    print(count)


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