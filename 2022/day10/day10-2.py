text_file = open("input.txt", "r")
commands = text_file.read().split("\n")

cycle_values = []
cycle_values.append(1)
crt_screen = [["." for i in range(40)] for i in range(6)]

for command in commands:
    if command.startswith("noop"):
        cycle_values.append(cycle_values[-1])
    elif command.startswith("addx"):
        cycle_values.append(cycle_values[-1])
        amount = command.split(" ")[1]
        if amount.startswith("-"):
            cycle_values.append(cycle_values[-1]-int(amount.split("-")[1]))
        else:
            cycle_values.append(cycle_values[-1]+int(amount))

for idx, x in enumerate(cycle_values):
    if ((idx % 40) -1) == x or (idx % 40) == x or ((idx % 40) +1) == x:
        crt_screen[int(idx/40)][idx%40] = "#"

print(cycle_values)
print(cycle_values[19]*20+cycle_values[59]*60+cycle_values[99]*100+cycle_values[139]*140+cycle_values[179]*180+cycle_values[219]*220)
print(crt_screen[0])
print(crt_screen[1])
print(crt_screen[2])
print(crt_screen[3])
print(crt_screen[4])
print(crt_screen[5])