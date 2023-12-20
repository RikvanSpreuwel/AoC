import numpy as np

def main():
    text_file = open("input.txt", "r")
    dumboGrid = [[int(y) for y in list(x)] for x in text_file.read().split('\n')]
    dumboGridHelper = np.zeros((len(dumboGrid), len(dumboGrid[0])))


    flashes = 0
    firstStep = 0
    for i in range(0,300):
        print(i)
        print(dumboGrid)
        for j in range(0, len(dumboGrid)):
            for k in range(0, len(dumboGrid[j])):
                dumboGrid[j][k] += 1

        previousFlashed = True
        while previousFlashed:
            # print(count)
            # print(dumboGridHelper)
            # print(dumboGrid)
            previousFlashed = False
            for j in range(0, len(dumboGrid)):
                for k in range(0, len(dumboGrid[j])):
                    if dumboGrid[j][k] > 9 and dumboGridHelper[j][k] == 0:
                        flashes +=1
                        dumboGridHelper[j][k] = 1
                        previousFlashed = True

                        if j != 0 and k != 0:                        
                            dumboGrid[j-1][k-1] += 1
                        if j != len(dumboGrid[0])-1 and k!= len(dumboGrid[0])-1:
                            dumboGrid[j+1][k+1] += 1
                        if j != 0:                        
                            dumboGrid[j-1][k] += 1
                            if k != len(dumboGrid[0])-1:
                                dumboGrid[j-1][k+1] += 1
                        if k != 0:
                            dumboGrid[j][k-1] += 1
                            if j != len(dumboGrid[0])-1:
                                dumboGrid[j+1][k-1] += 1
                        if j != len(dumboGrid[0])-1:
                            dumboGrid[j+1][k] += 1
                        if k != len(dumboGrid[0])-1:
                            dumboGrid[j][k+1] += 1
            
            
                        
                

        for j in range(0, len(dumboGrid)):
            for k in range(0, len(dumboGrid[0])):
                if dumboGrid[j][k] > 9:
                    dumboGrid[j][k] = 0
        allOnes = True
        for row in dumboGridHelper:
            for item in row:
                if item == 0:
                    allOnes = False
                    break

        if allOnes == True:
            firstStep = i
            break 
        dumboGridHelper = np.zeros((len(dumboGrid), len(dumboGrid[0])))
    print(dumboGrid)
    print(flashes)

    print(firstStep)



if __name__ == "__main__":
    main()