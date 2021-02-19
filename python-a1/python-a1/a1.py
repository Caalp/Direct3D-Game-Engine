from search import *
import random
import time


def make_rand_8puzzle():
    
    """
        Function for creating random 8puzzle object.

        Return: returns EightPuzzle object
            
    """
    # given an initial state
    state = [1,2,3,4,5,6,7,8,0]
    # shuffle the list randomly
    random.shuffle(state)

    # If it is not solveable then shuffle again otherwise return to the 8puzzle
    while EightPuzzle.check_solvability(None,state) != True:
        random.shuffle(state)
    return EightPuzzle(tuple(state))


def display(state):
    """
        Function that displays puzzle as 3x3 grid and uses * for blank tile.

        Keyword arguments:
            state -- 8puzzle state passed as tuple
    """
    for i in range(0,len(state),3):
          print_str = str(state[i])+" "+str(state[i+1])+" "+str(state[i+2])
          print_str = print_str.replace("0","*")
          print(print_str)

def astar_with_statistics(puzzle,heuristic=None):
    """
        Function that takes puzzle and heuristic function as an argument and
        runs astar_search function which is defined in search.py and prints statistics
        such as time taken to complete search, paths expanded and length of the solution.

        Keyword arguments:
            puzzle -- EightPuzzle object which has the puzzle
            heuristic -- type of heuristic function (default None)
    """
    
    ### print the instance
    if heuristic != None:
        print("Using {} heuristic:" .format(heuristic.__name__))
    else:
        print("Using misplace-tiles(default) heuristic:")


    ## start the timer
    start_time = time.time()

    ## do something here

    result = astar_search(puzzle,heuristic,True)
    #b = getattr(arg,"nodes_expanded")

    
    ## time passed
    elapsed_time = time.time() - start_time


    print("Total running time for search algorithm: {0}".format(elapsed_time))
    print("The length (i.e. number of tiles moved) of the solution: {0}\n".format(result.path_cost))
    


def manhattan(n):
    """
        Heuristic function calculates sum of distances of the tiles to from goal state.

        Keyword arguments:
        n->[Node] -- Node object 

        Return:
        r->[int] -- sum of the distances of all tiles from their goal state

    """
    goal_state = [1,2,3,4,5,6,7,8,0]
    # range 1-9 that will exclude the blank tile since it has actually the range [1,8] 
    r = sum(abs(n.state.index(i)//3 - goal_state.index(i)//3) +(abs(n.state.index(i)%3 - goal_state.index(i)%3)) for i in range(1,9))
    return r



def gaschnig(n):
    """
        This heuristic function takes Node object as an argument and calculates swaps needed
        from given state to the goal state.

        Keyword arguments:
        n->[Node] -- Node object 

        Return:
        total_num_swaps->[int] -- total number of swaps needed to reach goal state 
    """
    temp = list(n.state)
    goal_state = [1,2,3,4,5,6,7,8,0]

    total_num_swaps = 0
    while temp != goal_state:
        
     
        # Check whether nor not blank tile is in goal position
        if temp.index(0) == goal_state.index(0):
            # since blank tile is in goal position select any tile
            
            elem = random.choice(temp)
            # if that tile ends up being its goal position then try until you get one not in goal position
            while goal_state.index(elem) == temp.index(elem):
                elem = random.choice(temp)
                if  goal_state.index(elem) != temp.index(elem):
                     break

            blank_index = temp.index(0)
            elem_index = temp.index(elem) # target tile to swap with blank
        else:
            # Get index of blank tile
            blank_index = temp.index(0)
            # Get tile which suppose to be blank tile's current position
            elem_index = temp.index(goal_state[blank_index])
        # Do swapping
        temp[elem_index] , temp[blank_index] = temp[blank_index],temp[elem_index]
        total_num_swaps +=1

    return total_num_swaps


if __name__ == "__main__":

    ## top level code to handle if any arg exist or create random 8puzzle
    if len(sys.argv) > 1:
        # here convert arguments to int and store in arg variable
        arg = [int(x) for x in sys.argv[1:]]
        if (len(arg) != 9):
            print("Given arguments don't form an 8puzzle!")
            exit()
        #print(tuple(arg))
        puzzle = EightPuzzle(tuple(arg))
    else:
        #puzzle = make_rand_8puzzle()
         puzzle = EightPuzzle(tuple([7,3,6,8,1,5,2,4,0]))

    ## print out created puzzle to the terminal
    display(puzzle.initial)


    astar_with_statistics(puzzle)
    astar_with_statistics(puzzle,manhattan)
    astar_with_statistics(puzzle,gaschnig)

    ## Code commented out and used for question 5 for creation of test puzzles
    #puzzle_set = []
    #for i in range(0,15):
    #    puzzle_set.append(make_rand_8puzzle())
    #for e in puzzle_set:
    #    display(e.initial)
    #    astar_with_statistics(e)
    #    astar_with_statistics(e,manhattan)
    #    astar_with_statistics(e,gaschnig)



  