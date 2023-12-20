import numpy as np

def main():
    text_file = open("input.txt", "r")
    dumboGrid = [[int(y) for y in list(x)] for x in text_file.read().split('\n')]
    dumboGridHelper = np.zeros(len(dumboGrid), len(dumboGrid[0]))

    for i in range(0,100):
        for j in range(0, len(dumboGrid)):
            for k in range(0, len(dumboGrid[j])):
                dumboGrid[j][k] += 1
        while previousFlashed:
            for j in range(0, len(dumboGrid)):
                for k in range(0, len(dumboGrid[j])):
                    if dumboGrid[j][k] == 9 and dumboGridHelper[j][k] == 0:
                        if j == 0 and k == 0:
                            incrementCase1()
                        elif j ==0:
                            increment

        dumboGridHelper = np.zeros(len(dumboGrid), len(dumboGrid[0]))
    print(dumboGrid)

if __name__ == "__main__":
    main()