# Solution 1: O(n*m)
def countNegative_1(M):
	"""
	Lặp từng hàng kiểm tra từng phần tử mỗi hàng, nếu âm thì tăng biến count lên 1
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
Dùng Binary Search để tìm kiếm vị trí của số âm ở bên phải cùng (righmost negative - phần tử sau nó sẽ không âm) của từng hàng.
Thì suy ra các giá trị của bên trái của nó cũng đều là các giá trị âm.
"""
def getLastNegativeIndex(array, start, end, m):
	
	# Trường hợp cơ cở
	if (start == end):
		return start
		
	# Lấy chỉ số giữa mảng
	mid = start + (end - start) // 2
	
	# Nếu phần tử đó âm
	if (array[mid] < 0):
		
		# Kiểm tra xem nó có phải phần tử âm phải cùng không (phần tử sau nó sẽ không âm).
		if (mid + 1 < m and array[mid + 1] >= 0):
			
			return mid
		
		# Nếu không thì tìm vị trí giá trị âm phải cùng bên phải số nằm giữa.
		return getLastNegativeIndex(array, mid + 1, end, m)
	
	else:
		
		# Nếu số giữa không âm thì tìm vị trí giá trị âm phải cùng bên trái của nó.
		return getLastNegativeIndex(array, start, mid - 1, m)


def countNegative_2(M):
	n = len(M) 
	m = len(M[0])
	count = 0

	lastNegIndex = m-1

	for i in range(n):
		# Nếu phần tử đầu hàng mà dương thì không cần tìm kiếm hàng đó nữa
		if M[i][0] > 0:
			break

		# Lấy vị trí phần tử âm phải cùng
		# Các hàng sau sẽ tìm trong khoảng (0, lastNegIndex) vì các giá trị bên phải của lastNegIndex đều dương,
		# nên các giá trị tương ứng bên dưới của nó cũng dương, tiết kiệm thời gian tìm kiếm.
		lastNegIndex = getLastNegativeIndex(M[i], 0, lastNegIndex, m)

		# Vì các giá trị bên trái của phần tử âm phải cùng đều âm nên ta lấy được số lượng các số âm mỗi hàng
		count += (lastNegIndex + 1)

	return count

        
if __name__ == '__main__':
	M = [[-3, -2, -1], [-2,2,3],[-1,3,5]]
	print(countNegative_1(M))
	print(countNegative_2(M))
