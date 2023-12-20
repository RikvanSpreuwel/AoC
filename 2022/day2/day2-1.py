scores_per_shape = {
    "X" : 1,
    "Y" : 2,
    "Z" : 3,
    "A" : 1,
    "B" : 2,
    "C" : 3
}
def round_outcome(opponent, response):
    if scores_per_shape[opponent] == scores_per_shape[response]:
        return 3
    elif scores_per_shape[opponent] == 3 and scores_per_shape[response] == 1:
        return 6
    elif scores_per_shape[opponent] == 1 and scores_per_shape[response] == 3:
        return 0
    elif scores_per_shape[opponent] > scores_per_shape[response]:
        return 0
    elif scores_per_shape[opponent] < scores_per_shape[response]:
        return 6

def main():
    text_file = open("input.txt", "r")
    strategy_guide = [text_file.read().split("\n")]
    total_score = 0
    for game in strategy_guide[0]:
        game_score = 0
        game_score += scores_per_shape[game.split()[1]]
        game_score += round_outcome(game.split()[0], game.split()[1])
        total_score += game_score
    print(total_score)

if __name__ == main():
    main()