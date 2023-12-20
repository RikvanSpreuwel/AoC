root = {}
total_sum = 0

def main():
    global total_sum
    text_file = open("input.txt", "r")
    terminal_lines = text_file.read().split("\n")
    total_sum = 0

    current_directory = ""
    total_current_directory = ['/']
    for output_line in terminal_lines:
        if output_line.startswith("$"):
            if output_line == "$ cd /":
                print("Root opened")
            elif output_line.startswith("$ cd "):
                cd_command = output_line.split("$ cd ")[1]
                if cd_command == "..":
                    total_current_directory.pop()
                    current_directory = total_current_directory[-1]
                else:
                    current_directory = cd_command
                    total_current_directory.append(cd_command)
                current_directory = output_line.split("$ cd ")[1]
        else: #listing files inside current directory
            if output_line.startswith("dir"):
                add_dir_to_current_directory(total_current_directory, output_line.split("dir ")[1], root)
            else:
                add_file_to_dir(total_current_directory, output_line.split(" ")[1], output_line.split(" ")[0], root)

    print("Start size calculations")
    print_sizes(root, "/")
    print("total_sum: " + str(total_sum))

def print_sizes(tree, dir_name):
    global total_sum
    print(tree)
    total_size = 0
    for key, value in tree.items():
        if isinstance(value, int):
            total_size += value
        else:
            total_size += print_sizes(tree[key], key)

    print(dir_name + ": " + str(total_size))
    if total_size <= 100000:
        print("TESSSSSSSSSSSSSSSSST")
        total_sum += total_size
    return total_size

def add_dir_to_current_directory(total_current_directory, directory_name, tree):
    if len(total_current_directory) == 1:
        if total_current_directory[0] == "/":
            tree[directory_name] = {}
        else:
            tree[total_current_directory[0]][directory_name] = {}
    else:
        if total_current_directory[0] == "/":
            add_dir_to_current_directory(total_current_directory[1::], directory_name, tree)
        else:
            next_tree = tree[total_current_directory[0]]
            add_dir_to_current_directory(total_current_directory[1::], directory_name, next_tree)

def add_file_to_dir(total_current_directory, file_name, file_size, tree):
    if len(total_current_directory) == 1:
        if total_current_directory[0] == "/":
            tree[file_name] = int(file_size) 
        else:
            tree[total_current_directory[0]][file_name] = int(file_size)
    else:
        if total_current_directory[0] == "/":
            add_file_to_dir(total_current_directory[1::], file_name, file_size, tree)
        else:
            next_tree = tree[total_current_directory[0]]
            add_file_to_dir(total_current_directory[1::], file_name, file_size, next_tree)

if __name__ == "__main__":
    main()