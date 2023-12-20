def main():
    text_file = open("input.txt", "r")
    lines = text_file.read().split('\n')
    mappingPerDigitsLine = [x.split('|')[0] for x in lines]
    mappingDigits = [digits.split() for digits in mappingPerDigitsLine]
    easyDigitsPerLine = [x.split('|')[1] for x in lines]
    easyDigits = [digit.split() for digit in easyDigitsPerLine]    

    count = 0
    for i in range(0, len(easyDigits)):
        mapping = computeMapping(mappingDigits[i])
        fourDigitNumber = ''
        for digit in easyDigits[i]:
            if set(digit) == set(map(lambda x: mapping[x], {'a', 'b', 'c', 'e', 'f', 'g'})):
                fourDigitNumber += '0'
            elif len(digit) == 2:
                fourDigitNumber += '1'
            elif set(digit) == set(map(lambda x: mapping[x], {'a', 'c', 'd', 'e', 'g'})):
                fourDigitNumber += '2'
            elif set(digit) == set(map(lambda x: mapping[x], {'a', 'c', 'd', 'f', 'g'})): 
                fourDigitNumber += '3'
            elif len(digit) == 4:
                fourDigitNumber += '4'
            elif set(digit) == set(map(lambda x: mapping[x], {'a', 'b', 'd', 'f', 'g'})): 
                fourDigitNumber += '5'
            elif set(digit) == set(map(lambda x: mapping[x], {'a', 'b', 'd', 'e', 'f', 'g'})): 
                fourDigitNumber += '6'
            elif len(digit) == 3:
                fourDigitNumber += '7'
            elif len(digit) == 7:
                fourDigitNumber += '8'
            elif set(digit) == set(map(lambda x: mapping[x], {'a', 'b', 'c', 'd', 'f', 'g'})):
                fourDigitNumber += '9'
                
        count += int(fourDigitNumber)

    print(count)
    
def computeMapping(mappingDigits):
    mapping = {
        'a':'',
        'b':'',
        'c':'',
        'd':'',
        'e':'',
        'f':'',
        'g':''
    }

    one =  set(next(filter(lambda x: len(x)==2, mappingDigits)))
    seven =  set(next(filter(lambda x: len(x)==3, mappingDigits)))
    four =  set(next(filter(lambda x: len(x)==4, mappingDigits)))
    eight =  set(next(filter(lambda x: len(x)==7, mappingDigits)))

    twoThreeFive = [set(x) for x in filter(lambda x: len(x) == 5, mappingDigits)]
    zeroSixNine = [set(x) for x in filter(lambda x: len(x) == 6, mappingDigits)]

    nine = set(next(filter(lambda x: four.issubset(x), zeroSixNine)))
    two = set(next(filter(lambda x: x.issubset(nine) == False, twoThreeFive)))
    three = set(next(filter(lambda x: x.issubset(nine) and one.issubset(x), twoThreeFive)))
    five = set(next(filter(lambda x: x.issubset(nine) and one.issubset(x) == False, twoThreeFive)))
    zero = set(next(filter(lambda x: five.issubset(x) == False and x.issubset(nine) == False, zeroSixNine)))
    six = set(next(filter(lambda x: five.issubset(x) and x.issubset(nine) == False, zeroSixNine)))

    mapping['a'] = ''.join((seven - one))
    mapping['b'] = ''.join((nine - three))
    mapping['c'] = ''.join((eight - six))
    mapping['d'] = ''.join((eight - zero))
    mapping['e'] = ''.join((eight - nine))
    mapping['f'] = ''.join((three - two))
    mapping['g'] = ''.join((three - four - seven))

    return mapping

if __name__ == "__main__":
    main()