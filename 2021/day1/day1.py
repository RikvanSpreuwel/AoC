def main():
    text_file = open("input.txt", "r")
    lines = [(x.split(' ')[0], x.split(' ')[1]) for x in text_file.read().split('\n')]
    print(lines)
    count = 0
    previous = -1
    for line in lines:
        if previous != -1 and line > previous:
            previous = line
            count+= 1
        else:
            previous = line
    print(lines)
    print(count)

if __name__ == "__main__":
    main()