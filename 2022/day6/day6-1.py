text_file = open("input.txt", "r")

# stream = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"
stream = text_file.read()
print(stream)

position = 0
last_four = []
for character in [*stream]:
    position += 1
    print(character)
    if len(last_four) < 14:
        last_four.append(character)
    else:
        last_four.pop(0)
        last_four.append(character)

    print(last_four)
    if len(set(last_four)) == 14:
        break

print(position)

# command to measure how long it takes to run: Measure-Command { start-process python day6-1.py -wait }
