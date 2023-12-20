
import ast
import functools

def compare(left, right):
    for i in range(len(left)):
            if i > len(right)-1: #right is empty, left is not
                return -1
            elif isinstance(left[i], list):
                if isinstance(right[i], list):
                    result = compare(left[i], right[i])
                    if result != 0:
                        return result
                else:
                    result = compare(left[i], [right[i]])
                    if result != 0:
                        return result
            elif isinstance(right[i], list): # we know by previous if, that left is not list
                result = compare([left[i]], right[i])
                if result != 0:
                    return result
            else: # then both items should be integers
                if int(left[i]) == int(right[i]):
                    continue
                else:
                    return 1 if int(left[i]) < int(right[i]) else -1
    
    if len(left) < len(right):
        return 1
    return 0

def is_sorted(input_list, compare_function):
    for i in range(len(input_list)):
        if compare_function(input_list[i], input_list[i+1]) == -1:
            return False

text_file = open("input.txt", "r")
pairs = [ast.literal_eval(line) for line in text_file.read().split("\n") if line != '']

# Append divider packages
pairs.append([[2]])
pairs.append([[6]])
print(pairs)

pairs.sort(reverse=True,key=functools.cmp_to_key(compare))
for item in pairs:
    print(item)

index_first = pairs.index([[2]]) + 1
index_second = pairs.index([[6]]) + 1

print(index_first)
print(index_second)
print(index_first * index_second)