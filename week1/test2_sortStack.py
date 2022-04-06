"""
B1: Khởi tạo một stack tạm thời
B2: Lặp đến khi stack input rỗng:
    - Lưu lại và xóa giá trị đỉnh stack input, gọi là temp.
    - Kiểm tra xem giá trị đỉnh của stack tạm, gọi là tempStack và giá trị đỉnh temp vừa lấy,
        nếu tempStack > temp thì chuyển tempStack sang stack input, lặp lại đến khi giá trị
        ở đỉnh temp tạm không lớn hơn temp nữa.

    - Chuyển giá trị temp vào đỉnh temp tạm.
"""
def sortStack(stack):
    # Khởi tạo một stack tạm
    tempStack = []
    while len(stack) > 0:
        # Lưu lại và xóa giá trị đỉnh stack input.
        temp = stack.pop()

        # Kiểm tra xem tempStack có lớn hơn temp không
        # Nếu có thì chuyển tempStack vào stack input, lặp lại đến khi không còn giá trị tempStack thỏa mãn
        while (len(tempStack) > 0) and (temp < tempStack[-1]):
            stack.append(tempStack.pop())

        # Chuyển temp vào stack tạm
        tempStack.append(temp)
    return tempStack



if __name__ == '__main__':
    stack = [78, 65, 98, 23, 17, 88]
    stack = sortStack(stack)
    print(stack)