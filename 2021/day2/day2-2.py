def main():
    text_file = open("input.txt", "r")
    lines = [(x.split(' ')[0], int(x.split(' ')[1])) for x in text_file.read().split('\n')]
    horizontalPos = 0;
    depth = 0;
    aim = 0;
    for line in lines:
        if line[0] == 'forward':
            horizontalPos += line[1]
            depth += aim*line[1]
        elif line[0] == 'down':
            aim += line[1]
        elif line[0] == 'up':
            aim -= line[1]
    
    print("Horizontal position: ", horizontalPos)
    print("Depth: ", depth)
    print("Multiplicated: ", (horizontalPos*depth))

if __name__ == "__main__":
    main()