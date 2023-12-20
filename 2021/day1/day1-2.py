def main():
    text_file = open("input.txt", "r")
    lines = [int(x) for x in text_file.read().split('\n')]

    countItems = 0
    countIncrements = 0
    for line in lines:
        if countItems > 2:             
            A = lines[countItems-3] + lines[countItems-2] + lines[countItems-1]
            B = lines[countItems-2] + lines[countItems-1] + lines[countItems]
            # print(A)
            # print(B)
            if B > A:
                countIncrements += 1
        countItems += 1


    print(countIncrements)

if __name__ == "__main__":
    main()