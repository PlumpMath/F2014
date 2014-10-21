import proj1

def main():
    wins = { "p1": 0, "p2": 0 }
    for i in xrange(200):
        winner = proj1.main(False)
        if winner == 1:
            wins["p1"] += 1
        else:
            wins["p2"] += 1

    total_games = wins["p1"] + wins["p2"]

    print "Player 1 won " + str(wins["p1"]) + " / " + str(total_games) + " games."
    print "Player 2 won " + str(wins["p2"]) + " / " + str(total_games) + " games."

if __name__ == "__main__":
    main()
