
def sortStack(stack):
    # Initialize a temporary stack
    tempStack = []
    while len(stack) > 0:
        # Get and Pop the top value in stack input
        temp = stack.pop()

        # whether or not the top value in temp stack greater than the top value in stack input
        # if yes then move it to the stack input
        while (len(tempStack) > 0) and (temp < tempStack[-1]):
            stack.append(tempStack.pop())

        # Push the top value in stack input to the temp stack
        tempStack.append(temp)
    return tempStack



if __name__ == '__main__':
    stack = [78, 65, 98, 23, 17, 88]
    stack = sortStack(stack)
    print(stack)