
import ast

def check_contents(left, right):
    for i in range(len(left)):
            if i > len(right)-1: #right is empty, left is not
                return False
            elif isinstance(left[i], list):
                if isinstance(right[i], list):
                    if isinstance(check_contents(left[i], right[i]), bool):
                        return check_contents(left[i], right[i])
                else:
                    if isinstance(check_contents(left[i], [right[i]]), bool):
                        return check_contents(left[i], [right[i]])
            elif isinstance(right[i], list): # we know by previous if, that left is not list
                if isinstance(check_contents([left[i]], right[i]), bool):
                    return check_contents([left[i]], right[i])
            else: # then both items should be integers
                if int(left[i]) == int(right[i]):
                    continue
                else:
                    return int(left[i]) < int(right[i])
    
    if len(left) < len(right):
        return True
    return "neither"


text_file = open("input.txt", "r")
pairs = text_file.read().split("\n\n")
print(pairs)

total_sum = 0
for i in range(len(pairs)):
    left, right = pairs[i].split("\n")
    left = ast.literal_eval(left)
    right = ast.literal_eval(right)

    print(check_contents(left,right))
    if check_contents(left,right) == True: # if correct
        total_sum += i+1

print(total_sum)