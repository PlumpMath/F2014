# Connect Four program for Project 1

from ConnectFour import ConnectFour
import random

# Minimax stuff.
def minimax(board, depth):
    if isinstance(board, ConnectFour):
        global states_explored
        states_explored = 0
        moves = xrange(0, 7)
        best_move = moves[0]
        best_score = float("-inf")
        for move in moves:
            states_explored += 1
            clone = board.copy()
            clone.move(move)
            score = min_value(clone, depth - 1)
            if score > best_score:
                best_move = move
                best_score = score
        #print "States explored: " + str(states_explored)
        return best_move

def min_value(state, depth):
    if state.isOver() or depth == 0: return linearComboHeuristic(state)
    best_score = float("inf")
    moves = xrange(0, 7)
    for move in moves:
        clone = state.copy()
        if clone.move(move):
            states_explored += 1
            score = max_value(clone, depth - 1)
            if score < best_score:
                best_move = move
                best_score = score
    return best_score

def max_value(state, depth):
    if state.isOver() or depth == 0: return linearComboHeuristic(state)
    best_score = -float("inf")
    moves = xrange(0, 7)
    for move in moves:
        clone = state.copy()
        if clone.move(move): 
            states_explored += 1
            score = min_value(clone, depth - 1)
            if score > best_score:
                best_move = move
                best_score = score
    return best_score

# Alpha beta junk.
def alphaBetaSearch(board, depth):
    if isinstance(board, ConnectFour):
        global states_explored
        states_explored = 0
        max_val = float("-inf")
        moves = xrange(0, 7)
        best_move = moves[0]
        for move in moves:
            clone = board.copy()
            if clone.move(move):
                states_explored += 1
                alpha = ab_max_value(clone, float("-inf"), float("inf"), depth - 1)

                if alpha > max_val:
                    max_val = alpha
                    best_move = move
        #print "States explored: " + str(states_explored)
        return best_move


def ab_max_value(state, alpha, beta, depth):
    if state.isOver() or depth == 0: return linearComboHeuristic(state)
    score = -float("inf")
    moves = xrange(0, 7)
    for move in moves:
        clone = state.copy()
        if clone.move(move):
            global states_explored
            states_explored += 1
            score = max(score, ab_min_value(clone, alpha, beta, depth - 1))
            if score >= beta: return score
            alpha = max(alpha, score)
    return score

def ab_min_value(state, alpha, beta, depth):
    if state.isOver() or depth == 0: return linearComboHeuristic(state)
    score = float("inf")
    moves = xrange(0, 7)
    for move in moves:
        clone = state.copy()
        if clone.move(move):
            global states_explored
            states_explored += 1
            score = min(score, ab_max_value(clone, alpha, beta, depth - 1))
            if score <= alpha: return score
            beta = min(beta, score)
    return score

# Heuristic Algorithms:
def simpleHeuristic(board):
    if isinstance(board, ConnectFour):
        return sum(x.count(board.turn) for x in board.getBoard())

def linearComboHeuristic(board):
    """A linear combination of winning rows and columns to determine the utility of some board
    state. Inspired by this paper: http://www.ics.uci.edu/~jlam2/connectk.pdf"""
    weights = [1, -1, 1, -1, 1, -1]
    
    # Calculate winning rows for both players.
    if isinstance(board, ConnectFour):
        boardArray = board.getBoard()
        # First, check if the player wins.
        if board.won() == board.turn:
            return board.turn * float("inf")

        # Rows that contain at least one owned piece and no opposing pieces.
        own_winning_rows = 0
        # Inverse of above.
        own_winning_cols = 0
        # Columns instead.
        opp_winning_rows = 0
        # This should make sense.
        opp_winning_cols = 0

        own_three_seq = 0

        opp_three_seq = 0

        for i in boardArray:
            if i.count(1) >= 1 and i.count(-1) == 0:
                own_winning_rows += 1
            if i.count(-1) >= 1 and i.count(1) == 0:
                opp_winning_rows += 1

        for i in zip(*boardArray[::-1]):
            if i.count(1) >= 1 and i.count(-1) == 0:
                own_winning_cols += 1
            if i.count(-1) >= 1 and i.count(1) == 0:
                opp_winning_cols += 1

        utility = weights[0] * own_winning_rows + weights[1] * opp_winning_rows\
        + weights[2] * own_winning_cols + weights[3] * opp_winning_cols

        return utility

'''
This function picks a move to make on a connect four board.

connectFourBoard: exactly what it sounds like.
depthLimit: an int dictating what depth the minimax algorithm can search to.
alphaBetaPruningOn: a boolean denoting whether or not alpha-beta pruning is
active.
heuristicFunction: a function pointer that calculates a heuristic value for
nodes.
'''
def move(connectFourBoard, depthLimit, alphaBetaPruningOn,
        heuristicFunction=linearComboHeuristic):
    if isinstance(connectFourBoard, ConnectFour):
        if alphaBetaPruningOn:
            # Do alpha-beta pruning stuff.
            column = alphaBetaSearch(connectFourBoard, depthLimit)
            connectFourBoard.move(column)
        else:
            # No pruning. This is gonna hurt.
            column = minimax(connectFourBoard, depthLimit)
            connectFourBoard.move(column)
           
'''
This function makes a random move on a connect four board. Note: this should be
easily outperformed by the previous algorithm.
'''
def moveRandomly(connectFourBoard):
    # Pick a random column.
    column = random.randrange(0, 6)
    connectFourBoard.move(column)

# Magic happens here.
def main(debug=True):
    board = ConnectFour()
    while board.won() == 0:
        if board.turn == 1:
            move(board, 5, True)
            if debug:
                board.out()
                print ""
        else:
            moveRandomly(board)
            if debug:
                board.out()
                print ""

    if debug: print board.won()
    return board.won()

if __name__ == "__main__":
    main()
