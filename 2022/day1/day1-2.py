def main():
    text_file = open("input.txt", "r")
    lines = [text_file.read().split('\n')]
    print(lines)
    elvesCalories = []
    sum_cal = 0
    for line in lines[0]:
        if line == "":
            elvesCalories.append(sum_cal)
            sum_cal = 0
        else:
            sum_cal = sum_cal + int(line)
    
    elvesCalories.sort(reverse=True)
    print(elvesCalories)
    print(elvesCalories[0] + elvesCalories[1] + elvesCalories[2])

if __name__ == "__main__":
    main()