# Solution 1: O(n*m)
def countNegative_1(M):
	"""
	Lặp từng dòng kiểm tra từng phần tử mỗi hàng, nếu âm thì tăng biến count lên 1
	"""
	n = len(M) # số hàng
	m = len(M[0]) # số cột

	count = 0 # biến đếm
	for i in range(n):
		# Loop từng hàng
		for j in range(m):
			# Loop từng cột
			if M[i][j] < 0:
				# Nếu âm thì thỏa mãn
				count += 1
	return count



# Solution 2: O(n+m) Using Binary Search
"""
Vì tính chất của matrix là các giá trị được sort từ trái -> phải, từ trên -> dưới
Dùng Binary Search để tìm kiếm vị trí của số âm ở bên phải cùng (righmost) của từng hàng.
Thì suy ra các giá trị của bên trái của nó cũng đều là các giá trị âm.


"""
def getLastNegativeIndex(array, start, end, n):
	
	# Base case
	if (start == end):
		return start
		
	# Get the mid for binary search
	mid = start + (end - start) // 2
	
	# If current element is negative
	if (array[mid] < 0):
		
		# If it is the rightmost negative
		# element in the current row
		if (mid + 1 < n and array[mid + 1] >= 0):
			
			return mid
		
		# Check in the right half of the array
		return getLastNegativeIndex(array, mid + 1, end, n)
	
	else:
		
		# Check in the left half of the array
		return getLastNegativeIndex(array, start, mid - 1, n)


def countNegative_2(M):
    n = len(M) # số hàng
    m = len(M[0]) # số cột
    count = 0 # biến đếm

    for i in range(n):
        nextEnd = m - 1
        if M[i][0] >= 0:
            break

        nextEnd = getLastNegativeIndex(M[i], 0, nextEnd, m)
        count += (nextEnd + 1)

    return count

        
if __name__ == '__main__':
	M = [[-3, -2, 1], [-2,2,3],[-1,3,5]]
	print(countNegative_1(M))
	print(countNegative_2(M))
