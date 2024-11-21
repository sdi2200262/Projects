def complete_parentheses(expression):

    #we use a list ( left_parenthesis [] ) to save the left parenthesis every time we encounter a right one in the incomplete expressio
    #we also have a list ( char [] ) that saves the characters each iteration 
    #we will use this list to construct the final complete expression
    #which we will save in another list :') ( complete [] ) 
    left_parenthesis = []
    char = []
    complete = []

    #counts right parenthesis
    right_p = 0 
    left_p = 0

    #error handling
    if not expression:
        raise ValueError("The expression cannot be empty.")

    valid_characters = set('0123456789+-*/() ')

    #in this loop we add all the characters of the incomplete expression to the char list
    #for each right parenthesis we add a left one on the left_parenthesis list
    #we also have some error handling in here 
    for current in expression:
        if current not in valid_characters:
            raise ValueError(f"Invalid character found: '{current}'")

        if current == ')':
            left_parenthesis.append('(')
            char.append(current)
            right_p += 1
        else:
            char.append(current)
            
    #in this loop we construct the completed expression by "copying" the char list and for each right parenthesis we add a left one in the correct index
    for current in char:
        if char and left_p != right_p :
            if current == '*':        
                complete.insert(len(current) - 5, left_parenthesis.pop())
                left_p +=1
            if current == ')':
                complete.insert(len(current) - 4, left_parenthesis.pop())
                left_p +=1
            complete.append(current)
        else :
            complete.append(current)

    #we convert the final list to a string so the final print is readable
    result_string = ''.join(complete)

    return result_string 

if __name__ == '__main__':
    expression = ['1', '+', '2', ')', '*', '3', '-', '4', ')', '*', '5', '-', '6', ')', ')', ')']
    try:
        result = complete_parentheses(expression)
        print(result)
    except ValueError as eeeeerror:
        print(f"Error: {eeeeerror}")
    