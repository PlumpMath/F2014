

class ConnectFour:
    def __init__(self):
        self.board = []
        for i in range(0, 6):
            self.board.append([0] * 7)
        self.turn = 1
        self.win = 0

    # Makes a move in the given column.  If a move cannot be made in that column, 
    # returns false, otherwise returns true.
    def move(self, col):
        if(self.won() != 0):
            return False
        for i in range(0, len(self.board)):
            if self.board[i][col] == 0:
                self.board[i][col] = self.turn
                self._checkWin(i, col)
                self.turn = -self.turn
                return True
        return False

    # Prints the connect four board for debugging purposes.

    def out(self):
        for i in range(len(self.board)-1, -1, -1):
            for j in range(len(self.board[i])):
                if (self.board[i][j] == 1):
                    print 'x',
                if (self.board[i][j] == -1):
                    print 'o',
                if (self.board[i][j] == 0):
                    print '-',
            print "\n"

    # Returns a copy of the board for heuristic purposes.  Player one's moves are represented as
    # ones, player two's moves are represented as -1s, and empty spaces are zeros.

    def getBoard(self):
        temp = []
        for i in self.board:
            temp.append([])
            for j in i:
                temp[-1].append(j)
        return temp


    def _checkWin(self, row, col):
        temp = []
        for i in range(max(col - 3, 0), min(col + 4, 7)):
            temp.append(self.board[row][i])

        if self._longestSubsequence(temp) >= 4:
            self.win = self.turn
        temp = []
        for i in range(max(row - 3, 0), min(row + 4, 6)):
            temp.append(self.board[i][col])

        if self._longestSubsequence(temp) >= 4:
            self.win = self.turn
        temp = []

        for i in self._getRange(row, col):
            temp.append(self.board[i[0]][i[1]])
        if self._longestSubsequence(temp) >= 4:
            self.win = self.turn

        temp = []

        for i in self._getRange2(row, col):
            temp.append(self.board[i[0]][i[1]])
        if self._longestSubsequence(temp) >= 4:
            self.win = self.turn
        
    def _getRange(self, row, col):
        a = range(col - 3, col + 4)
        b = range(row - 3, row + 4)

        result = []
        for i in range(0, len(a)):
            c = a[i]
            r = b[i]
            if r >= 0 and c >= 0 and c < 7 and r < 6:
                result.append([r, c])
        return result

    def _getRange2(self, row, col):
        a = range(col - 3, col + 4)
        b = range(row - 3, row + 4)
        result = []
        b.reverse()
        for i in range(0, len(a)):
            c = a[i]
            r = b[i]
            if r >= 0 and c >= 0 and c < 7 and r < 6:
                result.append([r, c])
        return result


    def _longestSubsequence(self, myList):
        currentCounter = 0
        longestSeq = 0

        for i in range(0, len(myList)):
            if(myList[i] == self.turn):
                currentCounter = currentCounter + 1
                if(currentCounter > longestSeq):
                    longestSeq = currentCounter
            else:
                currentCounter = 0
        return longestSeq

    # Returns 1 if player one won, -1 if player 2, and 0 if the game is still in progress

    def won(self):
        return self.win

    # Returns if the game is over or not.

    def isOver(self):
        for i in range(0, len(self.board)):
            for j in range(0, len(self.board[0])):
                if self.board[i][j] == 0:
                    return self.won() != 0
        return True

    # Returns a copy of this connect four board.

    def copy(self):
        c = ConnectFour()
        for i in range(0, len(self.board)):
            for j in range(0, len(self.board[0])):
                c.board[i][j] = self.board[i][j]
        c.turn = self.turn
        return c

    # Returns all successor states for this board.

    def expand(self):
        listOBoards = []
        print len(self.board[0])
        for i in range(0, len(self.board[0])):
            newBoard = self.copy()
            print i
            if newBoard.move(i):
                listOBoards.append(newBoard)
        return listOBoards

