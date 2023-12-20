def main():
    text_file = open("input.txt", "r")
    lines = [list(x) for x in text_file.read().split('\n')]
    gammaRate = ''
    epsilonRate = ''

    print(lines[0])
    print(lines[0][0]=='0')
    print(lines[0][0]=='1')
    print(lines[0][3]=='0')
    print(lines[0][3]=='1')


    for i in range(0,len((lines[0]))):
        countZero = 0
        countOne = 0
        for line in lines:
            if line[i] == '0':
                countZero +=1
            else:
                countOne += 1
        if countZero > countOne:
            gammaRate = gammaRate + '0'
            epsilonRate = epsilonRate + '1'
        else:
            gammaRate = gammaRate + '1'
            epsilonRate = epsilonRate + '0'
    # print(lines)
    print(int(gammaRate, 2))
    print(int(epsilonRate, 2))
    print(int(gammaRate, 2)*int(epsilonRate, 2))


if __name__ == "__main__":
    main()