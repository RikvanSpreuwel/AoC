import numpy as np

def main():
    text_file = open("input.txt", "r")
    zeros = np.zeros((999,999))
    print(zeros)
    for line in text_file:
        # print(line.strip())
        # print(line)
        startx = int(line.split('->')[0].split(',')[0].strip())
        starty = int(line.split('->')[0].split(',')[1].strip())
        endx = int(line.split('->')[1].split(',')[0].strip())
        endy = int(line.split('->')[1].split(',')[1].strip())
        

        if (startx == endx) or (starty == endy):
            for i in range((startx if startx <= endx else endx), (endx+1 if startx <= endx else startx+1)):
                # print("hereb2")
                for j in range((starty if starty <= endy else endy), (endy+1 if starty <= endy else starty+1)):
                    zeros[i][j] += 1
        else:
            if startx <= endx:
                print("here1")
                diff = endx - startx
                if starty <= endy:
                    print("here2")
                    for i in range(0, diff+1):
                        zeros[startx+i][starty+i] += 1
                else:
                    print("here3")
                    for i in range(0, diff+1):
                        zeros[startx+i][starty-i] += 1
            else:
                diff = startx-endx
                if starty <= endy:
                    for i in range(0, diff+1):
                        zeros[startx-i][starty+i] += 1
                else:
                    for i in range(0, diff+1):
                        zeros[startx-i][starty-i] += 1

        # print(startx)
        # print(starty)
        # print(endx)
        # print(endy)
        # print(startx >= endx)
        # print(starty >= endy)
        # # break
    count = 0
    for row in zeros:
        # print(row)
        for column in row:
            
            if column > 1:
                count += 1
    # print(zeros[1])
    # print(zeros[944])
    print(count)


if __name__ == "__main__":
    main()