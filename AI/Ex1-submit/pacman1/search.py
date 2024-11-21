# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

from util import*
from game import Directions
from typing import List

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()




def tinyMazeSearch(problem: SearchProblem) -> List[Directions]:
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem: SearchProblem) -> List[Directions]:
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    path = []           
    state =  problem.getStartState()


    frontier = Stack()                 #using a stack (LIFO) to implement DFS     
    frontier.push( (state, path) )     #add the starting state to the frontier
    visited = set()
    
    #DFS searching deepest nodes first
    while not frontier.isEmpty():

        state, path = frontier.pop()    #pop the top node from the frontier stack to check if it is the goal state
        
        if problem.isGoalState(state):  #check if we have reached a goal state
            return path                 
        
        visited.add(state)              #if not add it to visited 

        #DFS starts here
        for s in problem.getSuccessors(state):  #check every successor of the current state
            if s[0] not in visited:             #if the current successor is not already visited then
                frontier.push( (s[0], path + [s[1]]) )  #add the successor and the updated path to the frontier stack
    util.raiseNotDefined()



def breadthFirstSearch(problem: SearchProblem) -> List[Directions]:
    """Search the shallowest nodes in the search tree first."""
    
    path = []           
    state =  problem.getStartState()   


    frontier = Queue()                #using a queue (FIFO) to implement BFS
    frontier.push( (state, path) )    #add the starting state to the frontier
    visited = set()
    
    #BFS searching shallowest nodes first
    while not frontier.isEmpty():
        
        state, path = frontier.pop()    #pop the top node from the frontier queue to check if it is the goal state
        
        
        if problem.isGoalState(state):  #check if we have reached a goal state
            return path
        
        visited.add(state)              #if not add it to visited 

        #BFS starts here 
        frontier_list = [ t[0] for t in frontier.list ]     #turn the frontier queue into a stack for checking later

        for s in problem.getSuccessors(state):              #check every successor of the current state
            if s[0] not in visited and s[0] not in frontier_list:   #if the successor is not already visited
                                                                    #and if the successor is not already in the frontier 
                frontier.push( (s[0], path + [s[1]]) )      # add the successor and the updated path to the frontier queue
    util.raiseNotDefined()

def uniformCostSearch(problem: SearchProblem) -> List[Directions]:
    """Search the node of least total cost first."""
    
    path = []          
    state = problem.getStartState()    
    
    
    frontier = PriorityQueue()          #using priority queue to implement UCS
    frontier.push((state, path), 0)     #add the starting state to the frontier
    visited = set()

    #USC searching the cheapest node first
    while not frontier.isEmpty():

        state, path = frontier.pop()    #pop the top node from the frontier priority queue to check if it is the goal state
        
        if problem.isGoalState(state):  #check if we have reached a goal state
            return path

        visited.add(state)              #if not add it to visited

        #UCS starts hear
        frontier_heap = [ i[2][0] for i in frontier.heap ]     # frontier.heap[i][2] is the state tuple: (position, path)
        
        for s in problem.getSuccessors(state):
            
            s_path = path + [s[1]]        #successor path
            
            if s[0] not in visited and s[0] not in frontier_heap:   #if the successor is not already visited
                                                                    #and if the successor is not already in the frontier
                frontier.push( (s[0], s_path), problem.getCostOfActions(s_path) )
            
            else:
                for i in range(0, len(frontier_heap)):
                    if s[0] == frontier_heap[i]:
                        # The stored path and the new path costs have to be compared
                        updatedCost = problem.getCostOfActions(s_path)
                        storedCost = frontier.heap[i][0]    # frontier.heap[i] is a tuple: (cost, counter, (node, path))
                        if storedCost > updatedCost:    # we have to update the frontier heap with the new cost and the new path
                            #however tuples are immutable so we have to do it step by step
                            
                            frontier.heap[i] = (storedCost, frontier.heap[i][1] , (s[0], s_path) )  #first update the path of the successor
                
                            frontier.update( (s[0], s_path), updatedCost )   #then we update the cost
    util.raiseNotDefined()



def nullHeuristic(state, problem=None) -> float:
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"

    path = []
    state = problem.getStartState()

    frontier = PriorityQueue()          #using priority queue to implement A
    frontier.push((state, path, 0), 0)  #add the starting state to the frontier
    visited ={}
    
    #A* searching the cheapest node while using heuristic function 
    while not frontier.isEmpty():

        state, path, cost = frontier.pop()  #pop the top node from the frontier priority queue to check if it is the goal state

        if problem.isGoalState(state):      #check if we have reached a goal state
            return path


        if (state not in visited) or (cost < visited[state]):   #if the current node is not already visited or the current cost is less than the cost of the visited state

            visited[state] = cost   #update cost
            
            #for every successor calculate the cost + heuristic value and add it in the frontier
            for s, s_path, s_cost in problem.getSuccessors(state):

                newpath = path + [s_path]   #calculate new path
                newCost = cost + s_cost     #calculate new cost
                newNode = (s, newpath, newCost)     #create a new node with new path and new cost

                frontier.push(newNode, newCost+heuristic(s, problem))
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
