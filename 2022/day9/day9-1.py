def main():
    text_file = open("input.txt", "r")

    motions = text_file.read().split("\n")
    coordinates_visited_by_tail = {(0,0)}
    head_position = [0,0] # x , y
    tail_position = [0,0] # x , y
    
    print(motions)
    for motion in motions:
        direction = motion.split(" ")[0]
        number_of_steps = int(motion.split(" ")[1])

        while number_of_steps > 0:
            number_of_steps -= 1

            if direction == "U":
                head_position[1] += 1
            elif direction == "D":
                head_position[1] -= 1
            elif direction == "R":
                head_position[0] += 1
            elif direction == "L":
                head_position[0] -= 1

            if absolute_difference_larger_than_2(head_position, tail_position):
                tail_position = find_new_tail_position_diagonal(head_position, tail_position)
                coordinates_visited_by_tail.add((tail_position[0], tail_position[1]))
            elif one_coordinates_difference_larger_than_2(head_position, tail_position):
                tail_position = find_new_tail_position_horizontal(head_position, tail_position)
                coordinates_visited_by_tail.add((tail_position[0], tail_position[1]))

            print("positions")
            print(head_position)
            print(tail_position)                
            
    
    print(coordinates_visited_by_tail)
    print(len(coordinates_visited_by_tail))

def absolute_difference_larger_than_2(head_position, tail_position):
    return (abs(head_position[0] - tail_position[0]) + abs(head_position[1]-tail_position[1])) > 2

def one_coordinates_difference_larger_than_2(head_position, tail_position):
    return (abs(head_position[0] - tail_position[0]) > 1) or (abs(head_position[1] - tail_position[1]) > 1)

def find_new_tail_position_diagonal(head_position, tail_position): # only called when aboslute difference is 3, and hence tail needs to move diagonally
    if head_position[0] > tail_position[0]:
        tail_position[0] += 1
    else:
        tail_position[0] -= 1
    if head_position[1] > tail_position[1]:
        tail_position[1] += 1
    else:
        tail_position[1] -= 1

    return tail_position
    
def find_new_tail_position_horizontal(head_position, tail_position):
    if head_position[1]-tail_position[1] == 2:
        tail_position[1] += 1
    elif head_position[1]-tail_position[1] == -2:
        tail_position[1] -= 1
    elif head_position[0]-tail_position[0] == 2:
        tail_position[0] += 1
    elif head_position[0] - tail_position[0] == -2:
        tail_position[0] -= 1

    return tail_position

if __name__ == "__main__":
    main()
