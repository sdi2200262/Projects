# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from pacman import GameState

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood().asList() #use the function asList to get the food available in a list 
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"

        min_distance = float("inf") #set food distance to infinity
        closest_food = None 

        #find the closest food
        #if ghost are near the closest food, go to the next-best food option
        for food in newFood:

            #find every food distance ( we use the manhattan distance ) from the current position
            food_distance = manhattanDistance(newPos, food)
            
            #check if the current food distance is smaller than the current minimum distance
            if food_distance < min_distance:

                #check if the food is safe
                food_safe = True

                #check if there is any ghost near the closest food
                for ghost in successorGameState.getGhostPositions():

                    #if there is a ghost near the closest foood, its not safe
                    if(manhattanDistance(ghost, food) < 2):
                        food_safe = False
                        break #dont check for other ghosts
                
                #if closest food is safe
                if food_safe:
                    min_distance = food_distance #set new minimum distance
                    closest_food = food #set new closest food position  

        #if ghost are near pacman, dont go
        for ghost in successorGameState.getGhostPositions():
            if (manhattanDistance(newPos, ghost) < 2):
                return -float('inf')
        

        #return the evalutaion score
        return successorGameState.getScore() + 1.0/min_distance
        

def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        
        #initialize depth
        depth = 0

        #the max_vlalue function returns a tuple ( evalScore, action )
        #the [1] after the call of the function indicates that we want to return the second element of the tuple
        #which is the action that leads to the game state that maximizes the the score
        return self.max_value(gameState, depth)[1]
        
    
    #we will introduce some helper function to solve this question
    #we must use two functions that calculate the max and the min value of the agent

    #max value function 
    #agent input value always set on 0 because MAX agent is ALWAYS pacmannnnnnnn
    def max_value(self, gameState, depth, agent = 0):

        #get all the legal actions of the current state that agent ==  0 (pacman) can take
        legal_actions = gameState.getLegalActions(agent)

        #if there are no legal actions or if the current game state is a goal state OR if the search depth is greater than the maximum depth to search for
        if not legal_actions or gameState.isWin() or depth >= self.depth:
            return self.evaluationFunction(gameState), Directions.STOP #return the evalScore and STOPPPppp

        #initialize successor state evalScore and corresponding action
        successor_evalScore = float('-inf') #set to minus infinity
        successor_action = Directions.STOP #set to STOPPP
        
        #for every action eligible to take
        for action in legal_actions:
            successorGameState = gameState.generateSuccessor(agent, action) #get the successor state of agent == 0 (pacmannn)
            evalScore = self.min_value(successorGameState, depth, agent + 1)[0] #get the evalScore of the min value function called from agent == agent + 1
            
            #if the evalScore of the current state is greater than the previous one 
            if evalScore > successor_evalScore:

                #update both the successor_evalScore and corresponding action
                successor_evalScore = evalScore
                successor_action = action
        
        #return the tuple of best evalScore and corresponding action for the MAX agent
        return successor_evalScore, successor_action
       

    #min value function
    #almost exactly the same as the max value function but with oppoosite comparison
    def min_value(self, gameState, depth, agent):

        #get all the legal actions of the current state that agent ==  0 (pacman) can take
        legal_actions = gameState.getLegalActions(agent)

        #if there are no legal actions or if the current game state is a goal state OR if the search depth is greater than the maximum depth to search for
        if not legal_actions or gameState.isWin() or depth >= self.depth:
            return self.evaluationFunction(gameState), Directions.STOP #return the evalScore and STOPPPppp
        
        #initialize successor state evalScore and corresponding action
        successor_evalScore = float('inf') #set to infinity this time 
        successor_action = Directions.STOP #set to STOPPP
        
        #for every action eligible to take
        for action in legal_actions:
            successorGameState = gameState.generateSuccessor(agent, action) #get the successor state of agent ( not pacman this time - probably a ghost )
            evalScore = 0 #set eval score to 0
        
            #check whose turn it is
            #if gameState.getNumAgents() -1 returns the agent value of the current agent
            #then it is the last ghost's turn so right after that it is pacman's turn 
            #therefore we call the max_value function 
            if agent == gameState.getNumAgents() - 1: 
                evalScore = self.max_value(successorGameState, depth + 1)[0] #get the evalScore of pacman's turn
            
            #if its not the last ghost's turn then there are more ghosts to take action
            #so call the min_value for the rest of the ghosts
            else:
                evalScore = self.min_value(successorGameState, depth, agent + 1)[0] #get the evalScore of the next ghost's turn
            
            #if the eval score of the current state is mikrotero (couldnt remember the word in english) than the previous one
            if evalScore < successor_evalScore:

                #update both the successor_evalScore and the correspodning action    
                successor_evalScore = evalScore
                successor_action = action

        #return the tuple of best evalScore and corresponding action for the MIN agent
        return successor_evalScore , successor_action
        



class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        #initialize depth
        depth = 0

        #initialize alpha and beta to minus infinity and infinity 
        alpha = float('-inf') #for pacman
        beta = float('inf') #for ghosts

        #same as q2 the max value returns the same tuple
        return self.max_value(gameState, alpha, beta, depth)[1]


    #we will create two similar helper functions for the AlphaBetaAgent 
    #we copy-pasted the functions from q2 and added the required code
    #that is why some comments are identical


    #max value function for beta pruining
    def max_value(self, gameState, alpha, beta, depth, agent = 0):

        #get all the legal actions of the current state that agent ==  0 (pacman) can take
        legal_actions = gameState.getLegalActions(agent)

        #if there are no legal actions or if the current game state is a goal state OR if the search depth is greater than the maximum depth to search for
        if not legal_actions or gameState.isWin() or depth >= self.depth:
            return self.evaluationFunction(gameState), Directions.STOP #return the evalScore and STOPPPppp

        #initialize successor state evalScore and corresponding action
        successor_evalScore = float('-inf') #set to minus infinity
        successor_action = Directions.STOP #set to STOPPP
        
        #for every action eligible to take
        for action in legal_actions:
            successorGameState = gameState.generateSuccessor(agent, action) #get the successor state of agent == 0 (pacmannn)
            evalScore = self.min_value(successorGameState, alpha, beta, depth, agent + 1)[0] #get the evalScore of the min value function called from agent == agent + 1
            
            #if the evalScore of the current state is greater than the previous one 
            if evalScore > successor_evalScore:

                #update both the successor_evalScore and corresponding action
                successor_evalScore = evalScore
                successor_action = action
            
            #prune the branch because pacman has already better score than what the ghosts can achieve
            if successor_evalScore > beta:
                return successor_evalScore , successor_action #return tuple

            #update alpha value
            alpha = max(alpha, successor_evalScore)

        
        #return the tuple of best evalScore and corresponding action for the MAX agent
        return successor_evalScore, successor_action

    #min value function for alpha pruining 
    def min_value(self, gameState, alpha, beta, depth, agent):

        #get all the legal actions of the current state that agent ==  0 (pacman) can take
        legal_actions = gameState.getLegalActions(agent)

        #if there are no legal actions or if the current game state is a goal state OR if the search depth is greater than the maximum depth to search for
        if not legal_actions or gameState.isWin() or depth >= self.depth:
            return self.evaluationFunction(gameState), Directions.STOP #return the evalScore and STOPPPppp
        
        #initialize successor state evalScore and corresponding action
        successor_evalScore = float('inf') #set to infinity this time 
        successor_action = Directions.STOP #set to STOPPP
        
        #for every action eligible to take
        for action in legal_actions:
            successorGameState = gameState.generateSuccessor(agent, action) #get the successor state of agent ( not pacman this time - probably a ghost )
            evalScore = 0 #set eval score to 0
        
            #check whose turn it is
            #if gameState.getNumAgents() -1 returns the agent value of the current agent
            #then it is the last ghost's turn so right after that it is pacman's turn 
            #therefore we call the max_value function 
            if agent == gameState.getNumAgents() - 1: 
                evalScore = self.max_value(successorGameState, alpha, beta, depth + 1)[0] #get the evalScore of pacman's turn
            
            #if its not the last ghost's turn then there are more ghosts to take action
            #so call the min_value for the rest of the ghosts
            else:
                evalScore = self.min_value(successorGameState, alpha, beta, depth, agent + 1)[0] #get the evalScore of the next ghost's turn
            
            #if the eval score of the current state is mikrotero (couldnt remember the word in english) than the previous one
            if evalScore < successor_evalScore:

                #update both the successor_evalScore and the correspodning action    
                successor_evalScore = evalScore
                successor_action = action

            #prune the branch because pacman worst case scenario is alpha value 
            if successor_evalScore < alpha:
                return successor_evalScore , successor_action #return tuple

            #update beta
            beta = min(beta, successor_evalScore)

        #return the tuple of best evalScore and corresponding action for the MIN agent
        return successor_evalScore , successor_action

        
        

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        #initialize depth
        depth = 0

        #same as q2 and q3
        return self.max_value(gameState, depth)[1]

        
    #two more similar helper functions for the ExpectimaxAgent 
    #we copy-pasted the functions from q2 and added the required code
    #that is why some comments are identical


    #max value function
    #pacman plays depending on expected utility of the ghosts' moves
    def max_value(self, gameState, depth, agent = 0):

        #get all the legal actions of the current state that agent ==  0 (pacman) can take
        legal_actions = gameState.getLegalActions(agent)

        #if there are no legal actions or if the current game state is a goal state OR if the search depth is greater than the maximum depth to search for
        if not legal_actions or gameState.isWin() or depth >= self.depth:
            return self.evaluationFunction(gameState), Directions.STOP #return the evalScore and STOPPPppp

        #initialize successor state evalScore and corresponding action
        successor_evalScore = float('-inf') #set to minus infinity
        successor_action = Directions.STOP #set to STOPPP
        
        #for every action eligible to take
        for action in legal_actions:
            successorGameState = gameState.generateSuccessor(agent, action) #get the successor state of agent == 0 (pacmannn)
            evalScore = self.min_value(successorGameState, depth, agent + 1)[0] #get the average evalScore of the min value function called from agent == agent + 1
            
            #if the evalScore of the current state is greater than the previous one 
            if evalScore > successor_evalScore:

                #update both the successor_evalScore and corresponding action
                successor_evalScore = evalScore
                successor_action = action
        
        #return the tuple of best evalScore and corresponding action for the MAX agent
        return successor_evalScore, successor_action
       

    #min value function
    #all ghost moves are random so we calculate the expected utility value by dividing the sum of all the possible utility values by their quantity
    def min_value(self, gameState, depth, agent):

        #get all the legal actions of the current state that agent ==  0 (pacman) can take
        legal_actions = gameState.getLegalActions(agent)

        #if there are no legal actions or if the current game state is a goal state OR if the search depth is greater than the maximum depth to search for
        if not legal_actions or gameState.isWin() or depth >= self.depth:
            return self.evaluationFunction(gameState), None 
        
        successor_evalScore = [] ##initialize successor state evalScore as an empty list
        
        #for every action eligible to take
        for action in legal_actions:
            successorGameState = gameState.generateSuccessor(agent, action) #get the successor state of agent ( not pacman this time - probably a ghost )
            evalScore = 0 #set eval score to 0
        
            #check whose turn it is
            #if gameState.getNumAgents() -1 returns the agent value of the current agent
            #then it is the last ghost's turn so right after that it is pacman's turn 
            #therefore we call the max_value function 
            if agent == gameState.getNumAgents() - 1: 
                evalScore = self.max_value(successorGameState, depth + 1)[0] #get the evalScore of pacman's turn
            
            #if its not the last ghost's turn then there are more ghosts to take action
            #so call the min_value for the rest of the ghosts
            else:
                evalScore = self.min_value(successorGameState, depth, agent + 1)[0]
            
            #add all the evalScores of all possible successor states to the list
            successor_evalScore.append(evalScore)

        #return the average evalScore
        return sum(successor_evalScore) / float(len(successor_evalScore)) , None
    
    

def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>

    something
    
    "*** YOUR CODE HERE ***"
    
    lets just try our first evaluation function and maybe add something to it
    """
    
    newPos = currentGameState.getPacmanPosition()
    newFood = currentGameState.getFood().asList() #use the function asList to get the food available in a list 
    newGhostStates = currentGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    
    #food criteria
    min_distance = float("inf") #set food distance to infinity
    closest_food = None 

    #ghost criteria
    ghost_score = 0

    #find the closest food
    #if ghost are near the closest food, go to the next-best food option
    for food in newFood:

        #find every food distance ( we use the manhattan distance ) from the current position
        food_distance = manhattanDistance(newPos, food)
        
        #check if the current food distance is smaller than the current minimum distance
        if food_distance < min_distance:

            #check if the food is safe
            food_safe = True

            #check if there is any ghost near the closest food
            for ghost in currentGameState.getGhostPositions():

                #if there is a ghost near the closest foood, its not safe
                if(manhattanDistance(ghost, food) < 2):
                    food_safe = False
                    break #dont check for other ghosts
            
            #if closest food is safe
            if food_safe:
                min_distance = food_distance #set new minimum distance
                closest_food = food #set new closest food position  

    #if ghost are near pacman, check if they are scared of mighty pacman or not and then take action accordingly
    for i , ghost in enumerate(currentGameState.getGhostPositions()):
        #check only if they are close enough
        if (manhattanDistance(newPos, ghost) < 2):
            
            #if ghosts are scared
            if newScaredTimes[i]>0:
                ghost_score += 50.0/(manhattanDistance(newPos, ghost)+1) #reward pacman for eating ghost
            else:
                ghost_score -=100.0/(manhattanDistance(newPos, ghost)+1) #penalize him for being near not scared ghosts
        
        #if they are far away award pacman for being away from deadly ghosts
        else:
            ghost_score += 1.0 / (manhattanDistance(newPos, ghost) + 1)
        
    

    #return the evalutaion score
    return currentGameState.getScore() + 1.0/min_distance + ghost_score


# Abbreviation
better = betterEvaluationFunction
