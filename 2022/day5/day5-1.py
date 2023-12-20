import re

text_file = open("input.txt", "r")
input_split = text_file.read().split("\n\n")
stacks_bulk_lines = input_split[0].split("\n") # every 4 characters represents one stack's letters, starting from 2. so 2/6/10/14....
print(stacks_bulk_lines)
nr_of_stacks = int(stacks_bulk_lines[-1].split(" ")[-2])
print("nr of stacks: " + str(nr_of_stacks))
stacks_bulk_lines.pop()

stacks = [ [] for _ in range(nr_of_stacks)]
print(stacks)
for row in reversed(stacks_bulk_lines):
    row_split = [*row]
    # print(row_split)
    for i in range(0, nr_of_stacks): #2 + 4*i
        # print(i)
        if row_split[2+i*4] != " ":
            print(row_split[1+i*4])
            stacks[i].append(row_split[1+i*4])

print(stacks)

procedure_list = input_split[1].split("\n")

for procedure in procedure_list:
    print(procedure)
    # print(re.findall(r'\d+', procedure))
    nr_to_move = int(re.findall(r'\d+', procedure)[0])
    move_from = int(re.findall(r'\d+', procedure)[1])
    move_to = int(re.findall(r'\d+', procedure)[2])
    print(nr_to_move)
    print(move_from)
    print(move_to)
    for _ in range(nr_to_move):
        stacks[move_to-1].append(stacks[move_from-1][-1])
        stacks[move_from-1].pop()

print(stacks)