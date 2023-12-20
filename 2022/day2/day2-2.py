scores_per_shape = {
    "X" : 0,
    "Y" : 3,
    "Z" : 6,
    "A" : 1,
    "B" : 2,
    "C" : 3
}

dict_victory = { # opponent | response
    "A" : "B",
    "B" : "C",
    "C" : "A"
}

def calculate_response(opponent, outcome):
    if (outcome == "X"): #lose
        return dict_victory[dict_victory[opponent]]
    elif (outcome == "Y"): #draw
        return opponent
    elif (outcome == "Z"): #win
        return dict_victory[opponent]

def main():
    text_file = open("input.txt", "r")
    strategy_guide = [text_file.read().split("\n")]
    total_score = 0
    for game in strategy_guide[0]:
        game_score = 0
        game_score += scores_per_shape[game.split()[1]]
        print(game)
        game_score += scores_per_shape[calculate_response(game.split()[0], game.split()[1])]
        print(game_score)
        total_score += game_score
    print(total_score)

if __name__ == main():
    main()