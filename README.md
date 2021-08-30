# 8-puzzle-solver
C++ Program that solves an 8 puzzle using different search trees
Input consists of two strings:
 - One representing the initial state
 - and the second represents the goal state
The code will take these strings and convert them to node states and perform a Breadth First Search and a Uniform Cost Search. The cost of the shortest path taken is then returned as output. You can track the traversals of the node states and display them by calling node->parent within a while loop until the root is reached> 
