def main():
    text_file = open("input.txt", "r")
    text_file2 = open("input.txt", "r")
    lines = [list(x) for x in text_file.read().split('\n')]
    lines2 = [list(x) for x in text_file2.read().split('\n')]
    
    loopLength = len(lines[0])
    for i in range(0, loopLength):
        countZero = 0
        countOne = 0
        for line in lines:
            if line[i] == '0':
                countZero +=1
            else:
                countOne += 1
        if countZero > countOne:
            lines = [line for line in lines if line[i]=='0']
        else:
            lines = [line for line in lines if line[i]=='1']

    for i in range(0, loopLength):
        countZero = 0
        countOne = 0
        for line in lines2:
            
            if line[i] == '0':
                countZero +=1
            else:
                countOne += 1
        
        if countOne >= countZero:
            lines2 = [line for line in lines2 if line[i]=='0']
        else:
            lines2 = [line for line in lines2 if line[i]=='1']

        if len(lines2) < 2:
            print(lines2)
            break
    
    print(int(''.join(lines2[0]), 2)*int(''.join(lines[0]),2))

if __name__ == "__main__":
    main()