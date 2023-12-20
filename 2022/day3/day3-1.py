def main():
    text_file = open("input.txt", "r")
    # rugsack_list = [text_file.read().split("\n")]
    rugsack_list = ["vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", "PmmdzqPrVvPwwTWBwg", "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", "ttgJtRGJQctTZtZT", "CrZsJsPPZsGzwwsLwLmpwMDw"]
    total = 0
    for rugsack in rugsack_list[0]:
        first_compartment = [*rugsack][0:int(len(rugsack)/2)]
        second_compartment = [*rugsack][int(len(rugsack)/2):len(rugsack)]
        duplicate = find_duplicate(first_compartment, second_compartment)
        print(duplicate)
        if duplicate.isupper():
            total += (ord(duplicate)-64)+26
            print(ord(duplicate)-64)
        else:
            total += ord(duplicate) -96
            print(ord(duplicate)-96)
    print(total)

def find_duplicate(l1, l2):
    for item1 in l1:
        for item2 in l2:
            if item1 == item2:
                return item1

if __name__ == "__main__":
    main()