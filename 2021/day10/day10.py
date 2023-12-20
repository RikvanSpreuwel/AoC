import math

def main():
    text_file = open("input.txt", "r")
    lines = text_file.read().split('\n')
    linesCopy = [line for line in lines]

    illegalTypeOneCount = 0
    illegalTypeTwoCount = 0
    illegalTypeThreeCount = 0
    illegalTypeFourCount = 0
    scores = []
    for i in range(0, len(lines)):
        removed = False
        openBrackets = []
        for character in list(lines[i]):
            if character == '(':
                openBrackets.append('(')
            elif character == '[':
                openBrackets.append('[')
            elif character == '{':
                openBrackets.append('{')
            elif character == '<':
                openBrackets.append('<')

            if character == ')':
                if openBrackets[-1] == '(':
                    openBrackets.pop()
                else:
                    illegalTypeOneCount += 1
                    linesCopy.remove(lines[i])
                    removed = True
                    break
            elif character == ']':
                if openBrackets[-1] == '[':
                    openBrackets.pop()
                else:
                    illegalTypeTwoCount += 1
                    linesCopy.remove(lines[i])
                    removed = True
                    break
            elif character == '}':
                if openBrackets[-1] == '{':
                    openBrackets.pop()
                else:
                    illegalTypeThreeCount += 1
                    linesCopy.remove(lines[i])
                    removed = True
                    break
            elif character == '>':
                if openBrackets[-1] == '<':
                    openBrackets.pop()
                else:
                    illegalTypeFourCount += 1
                    linesCopy.remove(lines[i])
                    removed = True
                    break   
        if removed == False:
            score = 0
            for bracket in reversed(openBrackets):
                print(bracket)
                score = score * 5
                if bracket == '(':
                    score += 1
                elif bracket == '[':
                    score += 2
                elif bracket == '{':
                    score +=3
                elif bracket == '<':
                    score +=4
            scores.append(score)


    # print(illegalTypeOneCount*3 + illegalTypeTwoCount*57 + illegalTypeThreeCount*1197 + illegalTypeFourCount*25137)

    # print(len(lines))
    print(len(linesCopy))
    print(len(scores))


    scores.sort()
    print(scores)
    print(scores[math.floor(len(scores)/2)])
    # mappingPerDigitsLine = [x.split('|')[0] for x in lines]
    # mappingDigits = [digits.split() for digits in mappingPerDigitsLine]
    # easyDigitsPerLine = [x.split('|')[1] for x in lines]
    # easyDigits = [digit.split() for digit in easyDigitsPerLine]    

    

if __name__ == "__main__":
    main()