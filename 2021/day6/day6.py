import numpy as np

def main():
    inputLanternFish = [4,1,3,2,4,3,1,4,4,1,1,1,5,2,4,4,2,1,2,3,4,1,2,4,3,4,5,1,1,3,1,2,1,4,1,1,3,4,1,2,5,1,4,2,2,1,1,1,3,1,5,3,1,2,1,1,1,1,4,1,1,1,2,2,1,3,1,3,1,3,4,5,1,2,2,1,1,1,4,1,5,1,3,1,3,4,1,3,2,3,4,4,4,3,4,5,1,3,1,3,5,1,1,1,1,1,2,4,1,2,1,1,1,5,1,1,2,1,3,1,4,2,3,4,4,3,1,1,3,5,3,1,1,5,2,4,1,1,3,5,1,4,3,1,1,4,2,1,1,1,1,1,1,3,1,1,1,1,1,4,5,1,2,5,3,1,1,3,1,1,1,1,5,1,2,5,1,1,1,1,1,1,3,5,1,3,2,1,1,1,1,1,1,1,4,5,1,1,3,1,5,1,1,1,1,3,3,1,1,1,4,4,1,1,4,1,2,1,4,4,1,1,3,4,3,5,4,1,1,4,1,3,1,1,5,5,1,2,1,2,1,2,3,1,1,3,1,1,2,1,1,3,4,3,1,1,3,3,5,1,2,1,4,1,1,2,1,3,1,1,1,1,1,1,1,4,5,5,1,1,1,4,1,1,1,2,1,2,1,3,1,3,1,1,1,1,1,1,1,5]
    newLanternFish = [] # day, nrOf
    for i in range(0, 256):
        print("Iteration: ", i)
        nrOfNewLanternfish = 0
        for j in range(0, len(inputLanternFish)):
            if inputLanternFish[j] == 0:
                nrOfNewLanternfish += 1
                inputLanternFish[j] = 6
            else:
                inputLanternFish[j] -= 1

        for j in range(0, len(newLanternFish)):
            if newLanternFish[j][0] == 0:
                nrOfNewLanternfish += newLanternFish[j][1]
                newLanternFish[j][0] = 6
            else:
                newLanternFish[j][0] -= 1

        if nrOfNewLanternfish > 0:
            newLanternFish.append([8, nrOfNewLanternfish])
    
    print(newLanternFish)
    print(len(inputLanternFish))
    lenNew = 0
    for item in newLanternFish:
        lenNew += item[1]
    print(lenNew)
    print(len(inputLanternFish) + lenNew)
            


    
    # text_file = open("input.txt", "r")
    # zeros = np.zeros((999,999))
    # print(zeros)
    # for line in text_file:
    #     # print(line.strip())
    #     # print(line)
    #     startx = int(line.split('->')[0].split(',')[0].strip())
    #     starty = int(line.split('->')[0].split(',')[1].strip())
    #     endx = int(line.split('->')[1].split(',')[0].strip())
    #     endy = int(line.split('->')[1].split(',')[1].strip())
        

    #     if (startx == endx) or (starty == endy):
    #         for i in range((startx if startx <= endx else endx), (endx+1 if startx <= endx else startx+1)):
    #             # print("hereb2")
    #             for j in range((starty if starty <= endy else endy), (endy+1 if starty <= endy else starty+1)):
    #                 zeros[i][j] += 1
    #     print(startx)
    #     print(starty)
    #     print(endx)
    #     print(endy)
    #     print(startx >= endx)
    #     print(starty >= endy)
    #     # break
    # count = 0
    # for row in zeros:
    #     # print(row)
    #     for column in row:
            
    #         if column > 1:
    #             count += 1
    # # print(zeros[1])
    # # print(zeros[944])
    # print(count)


if __name__ == "__main__":
    main()


