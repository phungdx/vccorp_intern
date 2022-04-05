
def sortStack(stack):
    # Khởi tạo một stack tạm thời
    tempStack = []
    while len(stack) > 0:
        # Lấy và xóa phần tử ở đỉnh stack input
        temp = stack.pop()

        # Kiểm tra nếu phần tử ở đỉnh stack tạm lớn hơn temp 
        # thì chuyển phần tử đó sang stack input
        while (len(tempStack) > 0) and (temp < tempStack[-1]):
            stack.append(tempStack.pop())

        # Thêm vào stack tạm phần tử temp
        tempStack.append(temp)
    return tempStack



if __name__ == '__main__':
    stack = [78, 65, 98, 23, 17, 88]
    stack = sortStack(stack)
    print(stack)