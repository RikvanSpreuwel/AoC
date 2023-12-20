def main():
    text_file = open("input.txt", "r")

    motions = text_file.read().split("\n")
    coordinates_visited_by_tail = {(0,0)}
    snake_positions = [[0,0] for i in range(10)] # x,y - first in list is head, last in list is tail
    print(snake_positions)

    print(motions)
    for motion in motions:
        direction = motion.split(" ")[0]
        number_of_steps = int(motion.split(" ")[1])

        while number_of_steps > 0:
            number_of_steps -= 1

            if direction == "U":
                snake_positions[0][1] += 1
            elif direction == "D":
                snake_positions[0][1] -= 1
            elif direction == "R":
                snake_positions[0][0] += 1
            elif direction == "L":
                snake_positions[0][0] -= 1

            snake_positions = update_snake_trail(snake_positions, 0)
            coordinates_visited_by_tail.add((snake_positions[9][0], snake_positions[9][1]))           
            
    
    print(coordinates_visited_by_tail)
    print(len(coordinates_visited_by_tail))

def update_snake_trail(snake_positions, current_snake_head_index): # the current snake_head is the one we compare with the previous
    if current_snake_head_index < 9:
        if absolute_difference_larger_than_2(snake_positions[current_snake_head_index], snake_positions[current_snake_head_index+1]):
            snake_positions[current_snake_head_index+1] = find_new_tail_position_diagonal(snake_positions[current_snake_head_index], snake_positions[current_snake_head_index+1])
            snake_positions = update_snake_trail(snake_positions, current_snake_head_index+1)
        elif one_coordinates_difference_larger_than_2(snake_positions[current_snake_head_index], snake_positions[current_snake_head_index+1]):
            snake_positions[current_snake_head_index+1] = find_new_tail_position_horizontal(snake_positions[current_snake_head_index], snake_positions[current_snake_head_index+1])
            snake_positions = update_snake_trail(snake_positions, current_snake_head_index+1)
    
    return snake_positions

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
