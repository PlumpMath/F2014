# Main file for running searches given arbitrary graph info.
# Note: BFS and DFS don't care about weight - only uniform cost.

import sys
from collections import deque, defaultdict
from Queue import PriorityQueue
from pprint import pprint

errorString = """Wrong input. Use the form: 'python Search.py inputTextFile.txt Breadth startNodeName goalNodeName outputFile.txt'"""

def readGraphData(inputFile):

    # Creating a weighted adjacency matrix.
    wam = defaultdict(dict)

    with open(inputFile, 'r') as file:
        data = file.read()
        # List comprehension to get rid of empty line at end.
        nodes = [line for line in data.split("\n") if line.strip() != '']

        # Use default dict to create adjacency matrix.
        for line in nodes:
            chars = line.split(" ")
            wam[chars[0]][chars[1]] = int(chars[2])

    return wam

def outputPath(outputFile, path):
    with open(outputFile, 'w+') as file:
        # Path should be a list, so join it.
        path = ",".join(path)
        file.write(path + "\n")

# Breadth First Search. Uses a queue.
def bfs(wam, start, goal):
    # Create the queue using implementation from collections.
    queue = deque([start])
    vertices = set()

    while len(queue) > 0:
        path = queue.pop()
        node = path[-1]
        vertices.add(node)

        if (node == goal):
            return path
        
        # Get attached nodes
        for node in wam[node]:
            if not node in vertices:
                new_path = list(path)
                new_path.append(node)
                queue.append(new_path)

    return "Search failed."

# Depth First Search. Uses a stack.
def dfs(wam, start, goal):
    stack = [start]
    vertices = set()

    while len(stack) > 0:
        path = stack.pop()
        node = path[-1]
        vertices.add(node)

        if node == goal:
            return path

        # Get connected nodes.
        for node in wam[node]:
            if not node in vertices:
                new_path = list(path)
                new_path.append(node)
                stack.append(new_path)

    return "Search failed."

# Uniform Cost Search, aka Dijkstra's Algorithm. Uses a priority queue.
def ucs(wam, start, goal):
    pQueue = PriorityQueue()
    vertices = set()

    # Start node has a priority of 0
    pQueue.put((0, start))

    while pQueue.qsize() > 0:
        path = pQueue.get()
        node = path[-1][-1]
        vertices.add(node)

        if node == goal:
            path = str(path)
            path = [item for sublist in path for item in sublist if ord(item) >=\
                    65 and ord(item) <= 90]
            return path

        # Get connected nodes.
        for localNode in wam[node]:
            if not localNode in vertices:
                new_path = list(path)
                new_path.append(localNode)

                # Append node(s) with priority of final node.
                priority = wam[node][localNode]

                # Flatten the path.
                pQueue.put((priority, new_path))

    return "Search failed."

# Where the magic happens.
def main():
    # Count up those sweet command-line args.
    if (len(sys.argv) != 6):
        print errorString    
    else:
        # Read input file
        inputFile = sys.argv[1]
        wam = readGraphData(inputFile)

        # Get the search type.
        searchType = sys.argv[2]
        startNodeName = sys.argv[3]
        goalNodeName = sys.argv[4]

        # Python doesn't have switch statements. :-(
        # Run that search!
        try:
            path = { 'breadth' : bfs,
                     'depth' : dfs,
                     'uniform' : ucs
                   }[searchType.lower()](wam, startNodeName, goalNodeName)
        except KeyError:
            print "Invalid Search Type " + searchType
            sys.exit(1)

        # Output that sweet-ass path.
        outputFile = sys.argv[5]
        outputPath(outputFile, path)

        # Terminate.
        sys.exit()


if __name__ == "__main__":
    main()
