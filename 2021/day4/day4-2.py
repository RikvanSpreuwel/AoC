def main():
    text_file = open("input.txt", "r")
    bingoNumbers = [int(x) for x in text_file.readline().strip().split(',')]
    emptyline= text_file.readline()
    print(bingoNumbers)

    matricesStrings = text_file.read().split('\n\n')
    matrices = [[list(map(int, y.split())) for y in x.split('\n')] for x in matricesStrings]
    matricesZeros = []
    for matrix in matrices:
        zeroMatrix = [[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]
        matricesZeros.append(zeroMatrix)

    print(doBingo(bingoNumbers, matrices, matricesZeros))
    
def doBingo(bingoNumbers, matrices, matricesZeros):
    countRemoved = 0
    for number in bingoNumbers:
        for i in range(0, len(matrices)):
            for j in range(0, 5):
                for k in range(0,5):
                    if matrices[i][j][k] == number:
                        if matricesZeros[i] != []:
                            matricesZeros[i][j][k] = 1
                            if (matricesZeros[i][j][0] == 1 and matricesZeros[i][j][1] == 1 and matricesZeros[i][j][2] == 1 and matricesZeros[i][j][3] == 1 and matricesZeros[i][j][4] == 1) or (matricesZeros[i][0][k] == 1 and matricesZeros[i][1][k] == 1 and matricesZeros[i][2][k] == 1 and matricesZeros[i][3][k] == 1 and matricesZeros[i][4][k] == 1):
                                if countRemoved == len(matricesZeros)-1:
                                    print(matricesZeros)
                                    sum = 0
                                    for s in range(0,5):
                                        for t in range(0,5):
                                            if matricesZeros[i][s][t] == 0:
                                                sum += matrices[i][s][t]
                                    return sum*number
                                else:
                                    matricesZeros[i] = []
                                    countRemoved +=1


                                

if __name__ == "__main__":
    main()