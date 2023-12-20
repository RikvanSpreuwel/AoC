text_file = open("input.txt", "r")
pairs = text_file.read().split("\n")
count = 0
for pair in pairs:
    print(pair)
    intervals = pair.split(",")
    interval1 = intervals[0].split("-")
    interval2 = intervals[1].split("-")
    if int(interval1[0]) <= int(interval2[0]) and int(interval1[1]) >= int(interval2[1]):
        count += 1
    elif int(interval1[0]) >= int(interval2[0]) and int(interval1[1]) <= int(interval2[1]):
        count += 1

    
    print(interval1)
    print(interval2)
print(count)