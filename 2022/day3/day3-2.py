def main():
    text_file = open("input.txt", "r")
    rugsack_list = text_file.read().split("\n")
    rugsack_list_grouped = [rugsack_list[x:x+3] for x in range(0, len(rugsack_list), 3)]
    # print(rugsack_list_grouped)
    # rugsack_list = [["vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", "PmmdzqPrVvPwwTWBwg"], ["wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", "ttgJtRGJQctTZtZT", "CrZsJsPPZsGzwwsLwLmpwMDw"]]
    total = 0

    for rugsack in rugsack_list_grouped:
        duplicate = find_duplicate(rugsack[0], rugsack[1], rugsack[2])
        print(duplicate)
        if duplicate.isupper():
            total += (ord(duplicate)-64)+26
            print(ord(duplicate)-64)
        else:
            total += ord(duplicate) -96
            print(ord(duplicate)-96)
    print(total)

def find_duplicate(l1, l2, l3):
    for item1 in l1:
        for item2 in l2:
            for item3 in l3:
                if item1 == item2 == item3:
                    return item1

if __name__ == "__main__":
    main()