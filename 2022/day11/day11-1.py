import re
import math

text_file = open("input.txt", "r")
monkeys_input = text_file.read().split("\n\n")
monkeys = []

current_monkey = 0
for monkey in monkeys_input:
    monkeys.append({}) 
    monkeys[current_monkey]["items"] = []
    for item in re.findall(r'\d+', monkey.split("\n")[1]):
        monkeys[current_monkey]["items"].append(int(item))

    monkeys[current_monkey]["operation"] = monkey.split("\n")[2].split("= ")[1].split()
    monkeys[current_monkey]["test"] = int(re.findall(r'\d+', monkey.split("\n")[3])[0])
    monkeys[current_monkey]["test_true"] = int(re.findall(r'\d+', monkey.split("\n")[4])[0])
    monkeys[current_monkey]["test_false"] = int(re.findall(r'\d+', monkey.split("\n")[5])[0])
    monkeys[current_monkey]["number_of_inspections"] = 0

    current_monkey += 1

round = 0
while round < 20:
    round += 1
    for i in range(len(monkeys)):
        for j in range(len(monkeys[i]["items"])):
            item = monkeys[i]["items"][j]
            
            if monkeys[i]["operation"][1] == "*":
                if monkeys[i]["operation"][2] == "old":
                    item = item * item
                else: 
                    item = item * int(monkeys[i]["operation"][2])
            elif monkeys[i]["operation"][1] == "+":
                if monkeys[i]["operation"][2] == "old":
                    item = item + item
                else: 
                    item = item + int(monkeys[i]["operation"][2])
            monkeys[i]["number_of_inspections"] += 1

            #monkey gets bored
            item = math.floor(item/3)

            #monkey throws
            if item % monkeys[i]["test"] == 0:
                monkeys[monkeys[i]["test_true"]]["items"].append(item)
            else:
                monkeys[monkeys[i]["test_false"]]["items"].append(item)

        monkeys[i]["items"] = []

for monkey in monkeys:
    print(monkey)

inspections = [monkey["number_of_inspections"] for monkey in monkeys]
most = max(inspections)
inspections.remove(most)
second_most = max(inspections)

print(most)
print(second_most)
print(most*second_most)