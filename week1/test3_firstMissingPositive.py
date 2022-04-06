"""
Tính chất: Ta thấy giá trị dương nhỏ nhất bị thiếu sẽ nằm trong đoạn [1, N+1] với N: số phần tử mảng input

B1: Tạo một mảng để đánh dấu arr, độ dài mảng arr bằng mảng đầu vào, với các giá trị khởi tạo đều là 0, mảng này sẽ đánh dấu
    xem có tồn tại các số từ [1->N] không. Dựa vào tính chất nêu ra ở trên, 
    giá trị phần tử mảng đầu vào sẽ chỉ được nằm trong đoạn [1, N]

             VD : mảng input: [1, 10, 4, 3, 6, 5, 7, 8] --> các giá trị thỏa mãn sẽ nằm trong đoạn [1, 8]
    sau cùng ta sẽ có   arr = [1 , 0, 1, 1, 1, 1, 1, 1]
    Vì giá trị tại phần tử thứ 2 bằng 0 nên số dương nhỏ nhất còn thiếu là 2.

B2: Loop qua từng phần tử mảng đầu vào:
    - Nếu phần tử đó nằm trong đoạn [1, N] thì sẽ tăng giá trị tương ứng trong mảng arr lên 1

B3: Loop qua từng phân tử mảng arr:
    - Nếu phần tử nào có giá trị bằng 0 thì chính là phần tử đang bị thiếu
    - Nếu không có phần tử nào bằng 0 thì chứng tỏ mảng input đã có đủ các phần tử trong khoảng [1, N] --> phần tử bị thiếu là N+1

"""


def firstMissingPositive(nums):
    N = len(nums)

    # Khởi tạo mảng đánh dấu
    arr = [0 for _ in range(N)]

    for i in range(N):
        # Loop qua từng phần tử và kiểm tra giá trị có thỏa mã dương và trong đoạn [1, N]
        if 0 < nums[i] <= N:
            arr[nums[i] - 1] += 1
            
    for i in range(N):
        if arr[i] == 0:
            return i + 1
    return N+1

if __name__ == '__main__':
    nums1 = [1, 10, 4, 3, 6, 5, 7, 8]
    nums2 = [2, 3, -7, 6, 8, 1, -10, 15]
    nums3 = [1, 1, 0, -1, -2]
    nums4 = [3,4,-1,1]
    nums5 = [-1, -3, -4]
    print(firstMissingPositive(nums1))